#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <string>

class ListException : public std::exception {

    private:
        std::string msg;

    public:
        explicit ListException(const char* message) : msg(message) { }

        explicit ListException(const std::string& message) : msg(message) { }

        virtual ~ListException() throw () { }

        virtual const char* what() const throw () {
            return msg.c_str();
            }
    };

///Definicion

template<class T, int SIZE = 3200>
class List {

    private:
        T data[SIZE];
        int last;

        bool isValidPos(const int&) const;

        void copyAll(const List<T, SIZE>&);

        void swapData(T&, T&);

        void sortDataMerge(const int&, const int&);
        void sortDataQuick(const int&, const int&);

    public:
        List();
        List(List<T, SIZE>&);

        bool isEmpty() const;
        bool isFull() const;

        void insertData(const T&, const int&);

        void deleteData(const int&);

        T* retrieve(const int&);

        int getFirstPos() const;
        int getLastPos() const;
        int getPrevPos(const int&) const;
        int getNextPos(const int&) const;

        int getSize() const;

        std::string toString() const;

        int findDataLinear(const T&);
        int findDataBinary(const T&);

        void sortDataBubble();
        void sortDataInsert();
        void sortDataSelect();
        void sortDataShell();

        void sortDataMerge();
        void sortDataQuick();

        void deleteAll();

        List<T, SIZE>& operator = (const List<T, SIZE>&);
    };


///Implementacion

using namespace std;

template<class T, int SIZE>
bool List<T, SIZE>::isValidPos(const int& pos) const {
    return pos > -1 && pos <= last;
    }

template<class T, int SIZE>
void List<T, SIZE>::copyAll(const List<T, SIZE>& l) {
    for (int i(0); i < l.last ; i++) {
        data[i] = l.data[i];
        }
    last = l.last;
    }

template<class T, int SIZE>
void List<T, SIZE>::swapData(T &a, T &b) {
    T aux(a);
    a = b;
    b = aux;
    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataMerge(const int& left, const int& right) {

    ///Criterio de paro
    if ( left >= right ) {
        return;
    }

    ///Punto medio
    int m((left + right) / 2);

    ///Divide y venceras
    sortDataMerge(left, m);
    sortDataMerge(m + 1, right);

    ///Arreglo auxiliar
    static T tmpData[SIZE];
    for (int i(left); i <= right; i++) {
        tmpData[i] = data[i];
    }

    ///Intercalacion
    int i(left), j(m + 1), x(left);

    while ( i <= m and j <= right ) {

        while ( i <= m and tmpData[i] <= tmpData[j] ) {
            data[x++] = tmpData[i++];
        }

        if ( i <= m ) {
            while ( j <= right and tmpData[j] <= tmpData[i] ) {
                data[x++] = tmpData[j++];
            }
        }
    }

    while ( i <= m ) {
        data[x++] = tmpData[i++];
        }

    while ( j <= right ) {
        data[x++] = tmpData[j++];
        }

    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataQuick(const int& left, const int& right)
{
    ///Criterio de paro
    if ( left >= right ) {
        return;
    }

    ///Separacion
    int i(left), j(right);

    ///Algoritmo de intercambio
    while ( i < j ) {

        while ( i < j and data[i] <= data[right] ) {
            i++;
        }

        while ( i < j and data[j] >= data[right] ) {
            j--;
        }

        if ( i != j ) {
            swapData( data[i], data[j] );
        }
    }

    if ( i != right ) {
        swapData( data[i], data[right] );
    }

    //Divide y venceras
    sortDataQuick( left, i - 1 );
    sortDataQuick( i + 1, right );
}

template<class T, int SIZE>
List<T, SIZE>::List() : last(-1) { }

template<class T, int SIZE>
List<T, SIZE>::List(List<T, SIZE>& l) {
    copyAll(l);
    }

template<class T, int SIZE>
bool List<T, SIZE>::isEmpty() const {
    return last == -1;
    }

template<class T, int SIZE>
bool List<T, SIZE>::isFull() const {
    return last == SIZE - 1;
    }

template<class T, int SIZE>
void List<T, SIZE>::insertData(const T& d, const int& pos) {
    if (isFull()) {
        throw ListException("La lista esta llena, insertData");
        }

    if ( pos != -1 && !isValidPos(pos) ) {
        throw ListException("Posicion invalida, insertData");
        }

    for (int i(last); i > pos; i-- ) {
        data[i+1] = data[i];
        }

    data[pos + 1] = d;
    last++;
    }

template<class T, int SIZE>
void List<T, SIZE>::deleteData(const int& pos) {
    if ( !isValidPos(pos) ) {
        throw ListException("Posicion invalida, deleteData");
        }

    for (int i(pos); i < last; i++) {
        data[i] = data[i+1];
        }
    last--;
    }

template<class T, int SIZE>
T* List<T, SIZE>::retrieve(const int& pos) {
    if ( !isValidPos(pos) ) {
        throw ListException("Posicion invalida, retrieve");
        }

    return &data[pos];
    }

template<class T, int SIZE>
int List<T, SIZE>::getFirstPos() const {
    return ( isEmpty() ) ? -1 : 0;
    }

template<class T, int SIZE>
int List<T, SIZE>::getLastPos() const {
    return last;
    }

template<class T, int SIZE>
int List<T, SIZE>::getPrevPos(const int& pos) const {
    return ( !isValidPos(pos) || pos == getFirstPos() ) ? -1 : pos -1;
    }

template<class T, int SIZE>
int List<T, SIZE>::getNextPos(const int& pos) const {
    return ( !isValidPos(pos) || pos == getLastPos()) ? -1 : pos + 1;
    }

template<class T, int SIZE>
int List<T, SIZE>::getSize() const {
    return last + 1;
    }

template<class T, int SIZE>
string List<T, SIZE>::toString() const {
    string str;
    for (int i(0); i <= last; i++) {
        str += data[i].toString() + "\n";
        }
    return str;
    }

template<class T, int SIZE>
int List<T, SIZE>::findDataLinear(const T &f) {
    int i(0);

    while ( i <= last) {

        if ( data[i] == f ) {
            return i;
            }
        i++;

        }

    return -1;
    }

template<class T, int SIZE>
int List<T, SIZE>::findDataBinary(const T &f) {
    int i(0), j(last), m;

    while ( i <= j) {

        m = (i + j) / 2;

        if ( data[m] == f ) {
            return m;
            }

        if ( f < data[m] ) {
            j = m - 1;
            }
        else {
            i = m + 1;
            }
        }

    return -1;
    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataBubble() {
    int i(last), j;
    bool flaj;

    do {
        flaj = false;
        j = 0;
        while ( j < i ) {

            if ( data[j] > data[j + 1] ) {
                swapData(data[j],data[j+1]);
                flaj = true;
                }

            j++;
            }

        i--;

        }
    while ( flaj );
    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataInsert() {
    int i(1), j;
    T aux;

    while ( i <= last ) {
        j = i;
        aux = data[j];

        while ( j > 0 and aux < data[j - 1] ) {
            data[j] = data[j-1];
            j--;
            }

        if ( j != i ) {
            data[j] = aux;
            }

        i++;
        }
    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataSelect() {
    int i(0), j, less_;

    while ( i < last ) {

        less_ = i;
        j = i + 1;

        while ( j <= last ) {

            if ( data[j] < data[less_] ) {
                less_ = j;
                }

            j++;
            }

        if ( less_ != i ) {
            swapData( data[less_], data[i] );
            }

        i++;
        }
    }

/*template<class T, int SIZE>
void List<T, SIZE>::sortDataShell()
{
    float factor(1.0 / 2.0);
    int dif( (last + 1) * factor ), i, j;

    while ( dif > 0 )
    {
        i = dif;

        while ( i <= last ) {

            j = i;
            while ( j >= dif and data[j - dif] > data[j] ) {
                swapData( data[j - dif], data[j] );
                j -= dif;
            }

            i++;
        }

        dif *= factor;
    }
} */

template<class T, int SIZE>
void List<T, SIZE>::sortDataShell() {
    //Factor 1/2
    //unsigned gapSeries[] = { 524288, 262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1, 0 };
    //Factor 1/3
    //unsigned gapSeries[] = { 531441, 177147, 59049, 19683, 6561, 2187, 729, 243, 81, 27, 9, 3, 1, 0 };
    //Tokuda
    //unsigned gapSeries[] = { 776591, 345152, 153401, 68178, 30301, 13467, 5985, 2660, 1182, 525, 233, 103, 46, 20, 9, 4, 1, 0};
    //Ciura
    unsigned gapSeries[] = { 510774, 227011, 100894, 44842, 19930, 8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};
    int gapPos(0), gap(gapSeries[gapPos]), i, j;

    while ( gap > 0 ) {
        i = gap;

        while (i <= last) {

            j = i;

            while ( j >= gap && data[j - gap] > data[j] ) {
                swapData( data[j - gap], data[j] );
                j -= gap;
                }

            i++;
            }

        gap = gapSeries[++gapPos];
        }
    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataMerge()
{
    sortDataMerge(0, last);
}

template<class T, int SIZE>
void List<T, SIZE>::sortDataQuick()
{
    sortDataQuick(0 , last);
}


template<class T, int SIZE>
void List<T, SIZE>::deleteAll() {
    last = -1;
    }

template<class T, int SIZE>
List<T, SIZE>& List<T, SIZE>::operator = (const List<T, SIZE>& l) {
    copyAll(l);
    return *this;
    }

#endif // LIST_H_INCLUDED
