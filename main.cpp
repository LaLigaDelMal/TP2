#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

//-------------------------------------------------------------------------------------------
// NODO

template <class T> class Nodo
{
public:
    Nodo();
    Nodo(T a);

    void set_dato(T a);
    void set_next(Nodo* n);
    T get_dato();
    Nodo* get_next();
    bool es_vacio();
    Nodo* der, * izq;
    T dato;
    Nodo* next;
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

//-------------------------------------------------------------------------------------------
//  LISTA

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
    Nodo<T>* nodo();
};

template <class T> Lista<T>::Lista(){
    czo = new Nodo<T>();
}

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

       // return NULL;
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

//----------------------------------------------------------
//ARBOL
template <class T> class Arbol {
private:
    Nodo<T>* raiz, * q;
    void arbolBusq(T x, Nodo<T>*& nuevo);
    void rid(Nodo<T>* aux);
    void ird(Nodo<T>* aux);
    void idr(Nodo<T>* aux);
    void show(Nodo<T>* aux, int n);

    void borrar(Nodo<T>*& p, T x);
    void bor(Nodo<T>*& d);
    void mh(Nodo<T>* aux);
    T menor(Nodo<T>* aux);
    bool esta(Nodo<T>* aux, T x);

public:
    Arbol() { raiz = NULL; };
    ~Arbol() {};
    void creaArbolBus(T x);
    void RID() { rid(raiz); }
    void IRD() { ird(raiz); }
    void IDR() { idr(raiz); }
    void VerArbol() { show(raiz, 0); }

    void borrar(T x) { borrar(raiz, x); }
    void mostrarHojas() { mh(raiz); }
    T menor() { return menor(raiz); }
    bool esta(T x) { return esta(raiz, x); }
};


template <class T> void Arbol<T>::creaArbolBus(T x)
{
    arbolBusq(x, raiz);
}
template <class T> void Arbol<T>::arbolBusq(T x, Nodo<T>*& nuevo)
{
    std::cout << x.getTiempo() << '\n';
    if (nuevo == NULL) {
        nuevo = new Nodo<T>;
        nuevo->dato = x;
        nuevo->der = nuevo->izq = NULL;
    }
    if ( x.getTiempo() > nuevo->get_dato().getTiempo() ) arbolBusq(x, nuevo->der);
    if ( x.getTiempo() < nuevo->get_dato().getTiempo() ) arbolBusq(x, nuevo->izq);
}
template <class T> void Arbol<T>::ird(Nodo<T>* aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        cout << "\n" << aux->get_dato();
        ird(aux->der);
    }
}
template <class T> void Arbol<T>::rid(Nodo<T>* aux)
{
    if (aux != NULL) {
        cout << "\n" << aux->get_dato();
        rid(aux->izq);
        rid(aux->der);
    }
}
template <class T> void Arbol<T>::idr(Nodo<T>* aux)
{
    if (aux != NULL) {
        idr(aux->izq);
        idr(aux->der);
        cout << "\n" << aux->get_dato();
    }
}
template <class T> void Arbol<T>::show(Nodo<T>* aux, int n)
{
    int i;
    if (aux != NULL) {                      //OjO este es un recorrido dri
        show(aux->der, n + 1);
        for (i = 1; i <= n; i++) cout << "     ";
        cout << aux->get_dato().getTiempo() << "\n";
        show(aux->izq, n + 1);
    }
}
template <class T> bool Arbol<T>::esta(Nodo<T>* aux, T x)
{
    if (aux == NULL) return false;
    else if (x.getTiempo() > aux->get_dato().getTiempo() ) return esta(aux->der, x);
    else if (x.getTiempo() < aux->get_dato().getTiempo() ) return esta(aux->izq, x);
    return true;

}
template <class T> void Arbol<T>::mh(Nodo<T>* aux)
{
    if (aux != NULL) {
        mh(aux->izq);
        if (aux->izq == NULL && aux->der == NULL)cout << "\n" << aux->get_dato().getTiempo();
        mh(aux->der);
    }
}
template <class T> T Arbol<T>::menor(Nodo<T>* aux)
{
    if (aux->izq == NULL)return aux->get_dato();
    return menor(aux->izq);
}
template <class T> void Arbol<T>::borrar(Nodo<T>*& p, T x)
{
    if (p == NULL) cout << "\n El dato NO esta\n\n";
    else if ( x.getTiempo() > p->get_dato().getTiempo() ) borrar(p->der, x);
    else if ( x.getTiempo() < p->get_dato().getTiempo() ) borrar(p->izq, x);
    else {// lo encontre en el nodo p
        q = p;
        if (q->der == NULL) p = q->izq;// raiz<=raiz del subarbol izq
        else if (q->izq == NULL) p = q->der;//raiz<=raiz del subarbol der
        else bor(q->izq);//busca en el sub arbol izq
        delete q;
    }
}
template <class T> void Arbol<T>::bor(Nodo<T>*& d)
{
    if (d->der != NULL) bor(d->der);//busca el elemento mas a la derecha
    else {
        q->set_dato( d->get_dato() );
        q = d;
        d = d->izq;
    }
}



//-------------------------------------------------------------------------------------------
//  EVENTO

class Evento {

public:
    Evento(){};
    Evento(string nombre, unsigned int tiempo)
            : nombreDelEvento(nombre), horaDeEjecucion(tiempo){};   //Constructor con parametros
    string nombreDelEvento;
    unsigned int horaDeEjecucion;
    int getTiempo();

};

int Evento::getTiempo(){
    return horaDeEjecucion;
}



//-------------------------------------------------------------------------------------------
//  RELOJ

class Reloj {

private:
    int numeroDeReloj, intervaloRep;
    string nombreDeReloj;
    bool aleatorio = false;
    Evento* eventos[50];      // Arreglo de punteros a eventos
    int generarRnd(int max);

public:
    Reloj(){};
    Reloj(int numRel, int tieRep, string nomRel, bool al)
    : numeroDeReloj(numRel), intervaloRep(tieRep), nombreDeReloj(nomRel), aleatorio(al){};
    ~Reloj(){};

    void generarEventos();
    Evento* getEventos();

};

void Reloj::generarEventos(){

    unsigned int tiempo = 0;
    string nombre;

    if(aleatorio == true){

        for(int c = 0; c < 50; c++){

            nombre = nombreDeReloj + " Evento " + std::to_string(c + 1);
            this->eventos[c] = new Evento(nombre, tiempo);
            tiempo += generarRnd(intervaloRep);
        }

    }else{

        for(int c = 0; c < 50; c++){

            nombre = nombreDeReloj + " Evento " + std::to_string(c + 1);
            this->eventos[c] = new Evento(nombre, tiempo);
            tiempo += intervaloRep;
        }
    }
}

Evento* Reloj::getEventos(){

    return this->eventos[50];
}

int Reloj::generarRnd(int max){

    srand((unsigned) time(0));
    return (rand() % max);
}






//-------------------------------------------------------------------------------------------
//  PLANIFICADOR (clase abstracta)

class Planificador{

protected:
    Lista<Reloj>* relojes = new Lista<Reloj>(); //Guarda los relojes en una lista (necesario para regenrar)
    void regenerar();                           //Vuelve a crear 50 eventos por cada reloj en el planificador

public:
    unsigned int eventosLanzados, comparaciones, contAux;
    virtual void agregarReloj(Reloj* r) = 0;                  // Se debe sobrescribir en cada planificador
    virtual Evento getProximoEvento() = 0;                   // Se debe sobrescribir en cada planificador
    void run();

};

void Planificador::run(){

    Evento ev = getProximoEvento();
    //Ejecutar
    cout << ev.horaDeEjecucion << ' ' << ev.nombreDelEvento << endl;
    eventosLanzados++;
    contAux++;
    //TODO sleep de evento

    if(contAux == 500){

        regenerar();
        contAux = 0;
    }
}

void Planificador::regenerar(){

    Nodo<Reloj>* NodoReloj = relojes->nodo();
    // Vover a generar 50 eventos por reloj cargado en el planificador (lista de relojes)
    while(!NodoReloj->es_vacio()){
        NodoReloj->get_dato().generarEventos();
        NodoReloj = NodoReloj->get_next();
    }

}





//-------------------------------------------------------------------------------------------
//  PLANIFICADOR 1 (lista enlazada)

class Planificador1 : public Planificador{

private:
    Lista<Evento>* eventos = new Lista<Evento>();
    void ordenar();

public:
    void agregarReloj(Reloj* r) override ;
    Evento getProximoEvento() override ;

};

void Planificador1::ordenar(){

}

void Planificador1::agregarReloj(Reloj* r){

    // Se carga el reloj en la lista de relojes del Planificador
    this->relojes->add(*r);  // Puntero a Reloj desreferenciado
    // Genera 50 eventos por cada reloj que se agrega
    r->generarEventos();
    Evento* ArrDeEventos = r->getEventos();

    for(int c = 0; c < 50; c++){
        // Guarda los eventos en la lista del planificador donde seran ordenados y luego ejecutados

        // LINEA QUE CAUSA EL ERROR (No descomentar!!!)
        // eventos->add(ArrDeEventos[c]);

    }
    ordenar();
}

Evento Planificador1::getProximoEvento(){

    Evento ev = eventos->cabeza();
    eventos->borrar();

    return  ev;
}

//-------------------------------------------------------------------------------------------
//  PLANIFICADOR 1 (lista enlazada)

class Planificador2 : public Planificador{

private:
    Arbol<Evento>* eventos = new Arbol<Evento>();
    void ordenar();

public:
    void agregarReloj(Reloj* r) override ;
    Evento getProximoEvento() override ;

};

void Planificador2::ordenar(){

}

void Planificador2::agregarReloj(Reloj* r){

    // Se carga el reloj en la lista de relojes del Planificador
    this->relojes->add(*r);  // Puntero a Reloj desreferenciado
    // Genera 50 eventos por cada reloj que se agrega
    r->generarEventos();
    Evento* ArrDeEventos = r->getEventos();

    for(int c = 0; c < 50; c++){
        // Guarda los eventos en la lista del planificador donde seran ordenados y luego ejecutados
        eventos->creaArbolBus(ArrDeEventos[c]);
    }
    //ordenar();
}

Evento Planificador2::getProximoEvento(){

    Evento ev = eventos->menor();
    eventos->borrar(ev);

    return  ev;
}




//-------------------------------------------------------------------------------------------
//  Funciones

// Lee el archivo, crea los relojes y los carga en el planificador
void cargarRelojes(Planificador *p, ifstream &archivo){

    string linea, nombreDeReloj, tipo;
    int numeroDeReloj, tiempoDeRepeticion;
    bool aleatorio = false;

    while(!archivo.eof())
    {
        getline(archivo, linea);
        istringstream iss(linea);

        iss >> numeroDeReloj;

        iss >> nombreDeReloj;

        iss >> tipo;
        if(tipo == "aleatorio") {
            aleatorio = true;
        }else{
            aleatorio = false;
        }

        iss >> tiempoDeRepeticion;

        cout << numeroDeReloj << " " << tiempoDeRepeticion << " " << nombreDeReloj << " " << aleatorio << endl;
        p->agregarReloj(new Reloj(numeroDeReloj, tiempoDeRepeticion, nombreDeReloj, aleatorio));
    }

};


//-------------------------------------------------------------------------------------------
//  MAIN

int main(){

    // Leer Archivo
    ifstream archivo;
    archivo.open("relojes.txt");

    // Inicializar planificadores
    //Planificador1* p1 = new Planificador1();
    Planificador2* p2 = new Planificador2();

    if(archivo.is_open()){
        cargarRelojes(p2, archivo);
        archivo.close();

        p2->run();
    }
    else{
        cout << "El archivo no pudo ser abierto.";
        exit(1);  // Terminacion del programa por error
    }

    return 0;
}



/*
 *     PROBLEMAS:
 *     1) El ultimo reloj en el archivo relojes.txt se esta cargando dos veces. Aparentemente el problema
 *     es el metodo eof() que se usa para detectar el final del archivo (linea 311).
 *     2) El Planificador 1 tiene un problema al cargar los eventos en la lista en la que seran ordenados.
 *        Esto esta generando el "segmentation fault". Ignorar la clase Planificador1 hasta que no se solucione.
 */
