#include <cstdlib>

#ifndef NODO_H
#define NODO_H

template <class T> class Nodo
{
private:
    T dato;
    Nodo* next;

public:
    Nodo();
    Nodo(T a);

    void set_dato(T a);
    void set_next(Nodo* n);
    T get_dato();
    Nodo* get_next();
    bool es_vacio();
};



template <class T> Nodo<T>::Nodo(){
    next = NULL;
}

template <class T> Nodo<T>::Nodo(T a){
    dato = a;
    next = NULL;
}

template <class T> void Nodo<T>::set_dato(T a){
    dato = a;
}

template <class T> void Nodo<T>::set_next(Nodo* n){
    next = n;
}

template <class T> T Nodo<T>::get_dato(){
    return dato;
}

template <class T> Nodo<T>* Nodo<T>::get_next(){
    return next;
}

template <class T> bool Nodo<T>::es_vacio(){
    return next == NULL;
}

#endif