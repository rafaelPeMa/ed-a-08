#include "broadcaster.h"

using namespace std;

int Broadcaster::isPosValid(string sentence) {
    string str;
    cout << endl << "Ingrese el numero de la posicion a la que quiere " << sentence << " ( 1 - " << songs->getSize() <<" ): ";
    getline(cin,str);

    int pos = -1;
    try {
        pos = stoi(str);
        }
    catch ( invalid_argument& ex ) {
        cout << endl << "Posicion invalida" << endl;
        enterToContinue();
        return -1;
        }

    if (pos < 1 || pos > songs->getSize()) {
        cout << endl << "La posicion a " << sentence << " esta fuera de rango" << endl;
        enterToContinue();
        return -1;
        }

    return pos;
    }

void Broadcaster::showMenu() {
    string in;
    char opc;

    while (true) {
        cout << "Discogradia de la rafiodifusora" << endl;

        if ( !songs->isEmpty() ) {
            cout << "Lista de canciones" << endl;
            for (int i(0); i < songs->getSize(); i++) {
                cout << i+1 << ".- " << songs->retrieve(i)->toString() << endl;
                }
            }
        else {
            cout << "Por el momento no poseemos ninguna cancion" << endl;
            }

        cout << endl << "Acciones" << endl;
        if ( !songs->isFull() ) {
            cout << "[A]gregar cancion" << endl;
            }

        if ( !songs->isEmpty() ) {
            cout << "[M]odificar cancion" << endl;
            cout << "[B]uscar cancion" << endl;
            cout << "[O]rdenar canciones" << endl;
            cout << "[E]liminar cancion" << endl;
            }

        cout << "[S]alir" << endl;
        cout << "Seleccione una opcion (A, M, B, O, E, S): ";
        getline(cin,in);

        if (in.length() != 1) {
            cout<<endl<<"Opcion invalida"<<endl;
            enterToContinue();
            continue;
            }

        opc = toupper(in[0]);

        switch (opc) {
            case 'A': {
                if (songs->isFull()) {
                    cout << endl << "La lista de canciones ya esta llena" << endl;
                    enterToContinue();
                    continue;
                    }
                addSong();
                }
            break;
            case 'E': {
                if (songs->isEmpty()) {
                    cout << endl << "La lista de canciones no contiene ningun elemento" << endl;
                    enterToContinue();
                    continue;
                    }
                deleteSong();
                }
            break;
            case 'M': {
                if (songs->isEmpty()) {
                    cout << endl << "La lista de canciones no contiene ningun elemento" << endl;
                    enterToContinue();
                    continue;
                    }
                editSong();
                }
            break;
            case 'O': {
                if (songs->isEmpty()) {
                    cout << endl << "La lista de canciones no contiene ningun elemento" << endl;
                    enterToContinue();
                    continue;
                    }
                orderData();
                }
            break;
            case 'B': {
                if (songs->isEmpty()) {
                    cout << endl << "La lista de canciones no contiene ningun elemento" << endl;
                    enterToContinue();
                    continue;
                    }
                searchSong();
                }
            break;
            case 'S': {
                return;
                }
            break;
            default : {
                cout<<"Opcion invalida"<<endl;
                enterToContinue();
                }
            }
        }
    }

void Broadcaster::addSong() {
    system("cls");
    Song s;
    string str;
    cout<<"*** Agregando cancion ***"<<endl;

    cout<< endl <<"Ingrese el nombre de la cancion: ";
    getline(cin, str);
    s.setName(str);

    cout<< endl <<"Ingrese el nombre del autor: ";
    getline(cin, str);
    s.setAuthor(str);

    cout<< endl <<"Ingrese el nombre del interprete: ";
    getline(cin, str);
    s.setInterpreter(str);

    cout<< endl <<"Ingrese el ranking: ";
    getline(cin, str);
    try {
        s.setRanking(stoi(str));
        }
    catch ( invalid_argument& ex ) {
        cout << endl << "Ranking invalido" << endl;
        enterToContinue();
        return;
        }

    cout << endl << "Ingrese el nombre del archivo MP3: ";
    getline(cin,str);
    s.setSourceMP3(str);

    int pos = songs->getLastPos();

    if (!songs->isEmpty()) {
        cout << endl <<"Ingrese la posicion al cual quiere insertar ( 1 - " << songs->getSize() + 1 <<" ): ";
        getline(cin, str);
        try {
            pos = stoi(str);
            }
        catch ( invalid_argument& ex ) {
            cout << endl << "Posicion invalida" << endl;
            enterToContinue();
            return;
            }
        if (pos < 1 || pos > songs->getSize() + 1) {
            cout << endl << "La posicion excede los limites" << endl;
            enterToContinue();
            return;
            }
        pos -= 2;
        }


    try {
        songs->insertData(s, pos);
        cout << endl << "Cancion agrega con exito" << endl;
        }
    catch (ListException ex) {
        cout << endl << "Error no se pudo agregar la cancion" << endl;
        }

    orderByAuthor = false;
    orderByName = false;
    enterToContinue();
    }

void Broadcaster::editSong() {

    int pos = isPosValid("modificar");

    if (pos == -1) {
        return;
        }

    system("cls");
    cout<<"*** Modificando cancion ***"<<endl;
    cout<<"OJO: Si el campo se deja vacio, este no se vera modificado" << endl;

    Song* s;
    string str;
    try {
        s = songs->retrieve(pos - 1);
        }
    catch (ListException ex) {
        cout << endl << "Ha ocurrido un error al modificar la cancion, intenlo mas tarde" << endl;
        enterToContinue();
        return;
        }

    cout << endl << s->toString() << endl;

    cout<< endl <<"Ingrese el nuevo nombre la cancion: ";
    getline(cin, str);
    if (str.length() > 0) {
        s->setName(str);
        }

    cout<< endl <<"Ingrese el nuevo nombre del autor: ";
    getline(cin, str);
    if (str.length() > 0) {
        s->setAuthor(str);
        }

    cout<< endl <<"Ingrese el nuevo nombre del interprete: ";
    getline(cin, str);
    if (str.length() > 0) {
        s->setInterpreter(str);
        }

    cout<< endl <<"Ingrese el ranking: ";
    getline(cin, str);
    if (str.length() > 0) {
        try {
            s->setRanking(stoi(str));
            }
        catch ( invalid_argument& ex ) {
            cout << endl << "Ranking invalido" << endl;
            enterToContinue();
            return;
            }
        }

    cout<< endl <<"Ingrese el nuevo nombre del archivo MP3: ";
    getline(cin, str);
    if (str.length() > 0) {
        s->setSourceMP3(str);
        }

    cout << endl <<"Cancion modificada" << endl;
    enterToContinue();
    }

void Broadcaster::deleteSong() {

    int pos = isPosValid("eliminar");

    if (pos == -1) {
        return;
        }

    try {
        songs->deleteData(pos-1);
        cout << endl << "Cancion removida con exito" << endl;
        }
    catch (ListException ex) {
        cout << endl << "Ha ocurrido un error al eliminar la cancion, intenlo mas tarde" << endl;
        }

    enterToContinue();
    }

void Broadcaster::enterToContinue() {
    cout<<"Presione <Enter> para continuar...."<<endl;
    getchar();
    system("cls");
    }

void Broadcaster::orderData() {
    system("cls");

    Song s;
    string str;
    char opc, order;

    cout << "*** Ordenando canciones ***" << endl;

    cout << endl << "Como desear ordenar?" << endl;
    cout << "[A] Por nombre de la cancion" << endl;
    cout << "[B] Por nombre del autor" << endl;
    cout << "Ingrese una opcion ( A, B ): ";
    getline(cin,str);

    if (str.length() != 1) {
        cout<<endl<<"Opcion invalida"<<endl;
        enterToContinue();
        return;
        }

    opc = toupper(str[0]);

    if ( opc != 'A' && opc != 'B' ) {
        cout<<endl<<"Opcion invalida"<<endl;
        enterToContinue();
        return;
        }

    if ( opc == 'A' ) {
        Song::setCompare(Song::COMPARE_BY_NAME);
        }
    else {
        Song::setCompare(Song::COMPARE_BY_AUTHOR);
        }

    cout << endl << "Seleccione el metodo a ordenar" << endl;
    cout << "[A] Burbuja mejorada" << endl;
    cout << "[B] Seleccion" << endl;
    cout << "[C] Inserccion" << endl;
    cout << "[D] Shell" << endl;
    cout << "Seleccione una opcion (A, B, C, D): ";
    getline(cin,str);

    if (str.length() != 1) {
        cout<<endl<<"Opcion invalida"<<endl;
        enterToContinue();
        return;
        }

    order = toupper(str[0]);

    switch ( order ) {
        case 'A': {
            songs->sortDataMerge();
            }
        break;
        case 'B': {
            songs->sortDataQuick();
            }
        break;
        case 'C': {
            songs->sortDataInsert();
            }
        break;
        case 'D': {
            songs->sortDataShell();
            }
        break;
        default: {
            cout << endl << "Ningun ordenamiento seleccionado" << endl;
            enterToContinue();
            return;
            }
        }

    if ( opc == 'A' ) {
        orderByName = true;
        orderByAuthor = false;
        }
    else {
        orderByAuthor = true;
        orderByName = false;
        }

    cout << endl << "Canciones ordenadas con exito" << endl << endl;

    enterToContinue();
    }

void Broadcaster::searchSong() {
    system("cls");

    Song s;
    string str, searchIn;
    char opc, searchOpc;
    int pos;

    cout << "*** Buscando cancion ***" << endl;

    cout << endl << "Como desear buscar?" << endl;
    cout << "[A] Por nombre de la cancion" << endl;
    cout << "[B] Por nombre del autor" << endl;
    cout << "Ingrese una opcion ( A, B ): ";
    getline(cin,str);

    if (str.length() != 1) {
        cout<<endl<<"Opcion invalida"<<endl;
        enterToContinue();
        return;
        }

    opc = toupper(str[0]);

    if ( opc != 'A' && opc != 'B' ) {
        cout<<endl<<"Opcion invalida"<<endl;
        enterToContinue();
        return;
        }

    cout << endl << "Ingrese la busqueda: ";
    getline( cin, searchIn );

    cout << endl << "Opciones de busqueda" << endl;
    cout << "[A] Lineal" << endl;
    cout << "[B] Binaria" << endl;
    cout << "Ingrese una opcion ( A, B ): ";
    getline(cin, str);

    if (str.length() != 1) {
        cout<<endl<<"Opcion invalida"<<endl;
        enterToContinue();
        return;
        }

    searchOpc = toupper(str[0]);

    if ( searchOpc != 'A' && searchOpc != 'B' ) {
        cout<<endl<<"Opcion invalida"<<endl;
        enterToContinue();
        return;
        }

    if ( opc == 'A' ) {
        s.setName(searchIn);
        Song::setCompare(Song::COMPARE_BY_NAME);
        }
    else {
        s.setAuthor(searchIn);
        Song::setCompare(Song::COMPARE_BY_AUTHOR);
        }

    if ( searchOpc == 'A' ) {
        pos = songs->findDataLinear(s);
        }
    else {
        if ( (opc == 'A' and orderByName) or (opc == 'B' and orderByAuthor) ) {
            pos = songs->findDataLinear(s);
            }
        else {
            cout << endl << "La busqueda no se puede realizar por que las canciones no estan ordenadas" << endl;
            cout << "Ordena las canciones antes de realizar la busqueda" << endl << endl;
            enterToContinue();
            return;
            }
        }

    if (  pos == -1 ) {
        string c = ( opc == 'A' ) ? "nombre" : "autor";
        cout << endl <<"No se a encontrado una cancion con el " << c << " \"" << searchIn << "\"" << endl;
        }
    else {
        cout << endl << "Se ha encontrado la cancion" << endl << endl;
        cout << "Cancion en la posicion " << pos + 1 << endl;
        cout << songs->retrieve(pos)->toString() << endl;
        cout << "Archivo MP3: " << songs->retrieve(pos)->getSourceMP3() << endl;
        }

    cout << endl;
    enterToContinue();
    }

Broadcaster::Broadcaster(List<Song>* s) : songs(s), orderByName(false), orderByAuthor(false) {
    showMenu();
    }

