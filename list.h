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
        T** data;
        int last;

        bool isValidPos(const int&) const;

        void copyAll(const List<T, SIZE>&);

        void swapData(T*&, T*&);

        void sortDataMerge(const int&, const int&);
        void sortDataQuick(const int&, const int&);

    public:
        List();
        List(List<T, SIZE>&);
        ~List();

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
    deleteAll();

    T* aux;
    int i = 0;

    while (i <= l.last) {
        aux = new T( *(l.data[i]) );
        if ( aux == nullptr ) {
            throw ListException("Memoria insuficiente, copyAll");
            }
        data[i] = aux;
        i++;
        }

    last = l.last;
    }

template<class T, int SIZE>
void List<T, SIZE>::swapData(T*& a, T*& b) {
    T* aux(a);
    a = b;
    b = aux;
    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataMerge(const int& left, const int& right) {
    if ( left >= right ) {
        return;
        }
    int m((left + right) / 2);

    sortDataMerge(left, m);
    sortDataMerge(m + 1, right);

    static T* tmpData[SIZE];
    for (int i(left); i <= right; i++) {
        tmpData[i] = data[i];
        }

    int i(left), j(m + 1), x(left);
    while ( i <= m and j <= right ) {

        while ( i <= m and *(tmpData[i]) <= *(tmpData[j]) ) {
            data[x++] = tmpData[i++];
            }

        if ( i <= m ) {
            while ( j <= right and *(tmpData[j]) <= *(tmpData[i]) ) {
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
void List<T, SIZE>::sortDataQuick(const int& left, const int& right) {
    if ( left >= right ) {
        return;
        }

    int i(left), j(right);
    while ( i < j ) {

        while ( i < j and *(data[i]) <= *(data[right]) ) {
            i++;
            }

        while ( i < j and *(data[j]) >= *(data[right]) ) {
            j--;
            }

        if ( i != j ) {
            swapData( data[i], data[j] );
            }
        }

    if ( i != right ) {
        swapData( data[i], data[right] );
        }

    sortDataQuick( left, i - 1 );
    sortDataQuick( i + 1, right );
    }

template<class T, int SIZE>
List<T, SIZE>::List() : last(-1) {
    data = new T*[SIZE];
    for (int i = 0; i < SIZE; i++) {
        data[i] = nullptr;
        }
    }

template<class T, int SIZE>
List<T, SIZE>::List(List<T, SIZE>& l) : List() {
    copyAll(l);
    }

template<class T, int SIZE>
List<T, SIZE>::~List() {
    deleteAll();
    delete[] data;
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

    T* aux = new T(d);
    if (aux == nullptr) {
        throw ListException("Memoria insuficiente, insertData");
        }

    int i(last);
    while (i > pos) {
        data[i + 1] = data[i];
        i--;
        }

    data[pos + 1] = aux;
    last++;
    }

template<class T, int SIZE>
void List<T, SIZE>::deleteData(const int& pos) {
    if ( !isValidPos(pos) ) {
        throw ListException("Posicion invalida, deleteData");
        }

    int i(pos);
    while (i < last) {
        data[i] = data[i + 1];
        i++;
        }

    data[last--] = nullptr;
    }

template<class T, int SIZE>
T* List<T, SIZE>::retrieve(const int& pos) {
    if ( !isValidPos(pos) ) {
        throw ListException("Posicion invalida, retrieve");
        }

    return data[pos];
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
    int i(0);
    while ( i <= last) {
        str += data[i++]->toString() + "\n";
        }
    return str;
    }

template<class T, int SIZE>
int List<T, SIZE>::findDataLinear(const T &f) {
    int i(0);

    while ( i <= last) {

        if ( *(data[i]) == f ) {
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

        if ( *(data[m]) == f ) {
            return m;
            }

        if ( f < *(data[m]) ) {
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

            if ( *(data[j]) > *(data[j + 1]) ) {
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
    T* aux;

    while ( i <= last ) {
        j = i;
        aux = data[j];

        while ( j > 0 and *(aux) < *(data[j - 1]) ) {
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

            if ( *(data[j]) < *(data[less_]) ) {
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

template<class T, int SIZE>
void List<T, SIZE>::sortDataShell() {
    unsigned gapSeries[] = { 510774, 227011, 100894, 44842, 19930, 8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};
    int gapPos(0), gap(gapSeries[gapPos]), i, j;

    while ( gap > 0 ) {
        i = gap;

        while (i <= last) {

            j = i;

            while ( j >= gap && *(data[j - gap]) > *(data[j]) ) {
                swapData( data[j - gap], data[j] );
                j -= gap;
                }

            i++;
            }

        gap = gapSeries[++gapPos];
        }
    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataMerge() {
    sortDataMerge(0, last);
    }

template<class T, int SIZE>
void List<T, SIZE>::sortDataQuick() {
    sortDataQuick(0, last);
    }

template<class T, int SIZE>
void List<T, SIZE>::deleteAll() {
    int i(last);
    while ( i >= 0) {
        delete data[i--];
        }
    last = i;
    }

template<class T, int SIZE>
List<T, SIZE>& List<T, SIZE>::operator = (const List<T, SIZE>& l) {
    copyAll(l);
    return *this;
    }

#endif // LIST_H_INCLUDED
