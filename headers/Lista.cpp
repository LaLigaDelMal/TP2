#include <cstdlib>
#include <iostream>
#include "Nodo.cpp"

#ifndef LISTA_H
#define LISTA_H

template <class T> class Lista{
private:
    Nodo<T>* czo;

public:
    Lista();
    Lista(Nodo<T>* n);
    void add(T d);
    bool es_vacia();
    T cabeza();
    void borrar();     // Borra el Nodo cabeza
    Nodo<T>* nodo();   // Devuelve el primer nodo de la lista
};

template <class T> Lista<T>::Lista(){}

template <class T> Lista<T>::Lista(Nodo<T>* n){
    czo = n;
}

template <class T> void Lista<T>::add(T d){
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}

template <class T> bool Lista<T>::es_vacia(){
    return czo->es_vacio();
}

template <class T> T Lista<T>::cabeza(){
    if (es_vacia()) {

        return NULL;
    }
    return czo->get_dato();
}

template <class T> void Lista<T>::borrar() {

    if (!this->es_vacia()) {
        Nodo<T> *tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

template <class T> Nodo<T>* Lista<T>::nodo() {

    return czo;
}

#endif
