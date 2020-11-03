#include <iostream>

#include "list.h"
#include "song.h"

using namespace std;

int main() {
    List<Song,100> l;
    Song s;
    s.setRanking(1);
    s.setSourceMP3("musica/mi_musica.mp3");
    s.setName("Mi muerte");
    s.setInterpreter("Interprete 2");
    s.setAuthor("Rafael");
    if ( l.isEmpty() ) {
        cout << "Esta vacia" << endl;
        }
    else {
        cout << "No esta vacia" << endl;
        }

    if ( l.isFull() ) {
        cout << "Esta llena" << endl;
        }
    else {
        cout << "No esta llena" << endl;
        }

    for (int i = 1; i <= 20; i++) {
        s.setName("Cancion " + to_string(i));
        s.setRanking(i);
        l.insertData(s, l.getFirstPos());
    }

    cout << "Lista: " << endl;
    cout << l.toString() << endl;

    try {
        l.deleteData(0);
        l.deleteData(0);
        l.deleteData(0);
    } catch (ListException ex) {
        cout << "Excepcion " << ex.what() << endl;
    }

    l.sortDataShell();

    cout << "Lista: " << endl;
    cout << l.toString() << endl;

}
