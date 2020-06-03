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

//-------------------------------------------------------------------------------------------
//  LISTA

template <class T> class Lista{

public:
    Lista();
    Lista(Nodo<T>* n);
    void add(T d);
    bool es_vacia();
    T cabeza();
    void borrar();     // Borra el Nodo cabeza
    Nodo<T>* nodo();
    Nodo<T>* czo;
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





//-------------------------------------------------------------------------------------------
//  EVENTO

class Evento {

public:
    Evento(){};
    Evento(string nombre, unsigned int tiempo)
            : nombreDelEvento(nombre), horaDeEjecucion(tiempo){};   //Constructor con parametros
    string nombreDelEvento;
    unsigned int horaDeEjecucion;
};




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
    Evento** getEventos();

};

void Reloj::generarEventos(){

    unsigned int tiempo = 0;
    string nombre;

    if(aleatorio == true){

        for(int c = 0; c < 50; c++){

            nombre = nombreDeReloj + " Evento " + std::to_string(c + 1);
            eventos[c] = new Evento(nombre, tiempo);
            tiempo += generarRnd(intervaloRep);
        }

    }else{

        for(int c = 0; c < 50; c++){

            nombre = nombreDeReloj + " Evento " + std::to_string(c + 1);
            eventos[c] = new Evento(nombre, tiempo);
            tiempo += intervaloRep;
        }
    }
}

Evento** Reloj::getEventos(){

    return eventos;
}

int Reloj::generarRnd(int max){

    srand((unsigned) time(0));
    return (rand() % max);
}






//-------------------------------------------------------------------------------------------
//  PLANIFICADOR (clase abstracta)

class Planificador{

protected:
    Lista<Reloj*>* relojes = new Lista<Reloj*>(); //Guarda los relojes en una lista (necesario para regenrar)
    void regenerar();                             //Vuelve a crear 50 eventos por cada reloj en el planificador

public:
    unsigned int eventosLanzados, comparaciones, contAux;
    void agregarReloj(Reloj* r);
    virtual void agregarEventos() = 0;           // Se debe sobrescribir en cada planificador
    virtual Evento getProximoEvento() = 0;       // Se debe sobrescribir en cada planificador
    void run();
};

// Carga el reloj en la lista de relojes y genera eventos para dicho reloj
void Planificador::agregarReloj(Reloj* r){

    // Se carga el reloj en la lista de relojes del Planificador
    this->relojes->add(r);
    // Genera 50 eventos por cada reloj que se agrega
    r->generarEventos();
}

void Planificador::run(){

    // Se agregan los eventos cuando el programa comienza y despues de cada llamada a regenerar()
    if(contAux == 0){
        // Se agregan los eventos generados en la estructura del Planificador
        agregarEventos();
    }

    if(contAux == 500){

        cout << "Se lanzaron 500 eventos !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "Eventos lanzados en total: " << eventosLanzados << endl;
        regenerar();
        contAux = 0;
        run();
    }

    Evento ev = getProximoEvento();
    //Ejecutar
    cout << ev.horaDeEjecucion << ' ' << ev.nombreDelEvento << endl;
    eventosLanzados++;
    contAux++;
}

// Recorre la lista de relojes y genera eventos para cada reloj
void Planificador::regenerar(){

    Nodo<Reloj*>* nodoReloj = relojes->nodo();
    // Volver a generar 50 eventos por reloj cargado en el planificador (lista de relojes)
    while(!nodoReloj->es_vacio()){
        nodoReloj->get_dato()->generarEventos();
        nodoReloj = nodoReloj->get_next();
    }
}





//-------------------------------------------------------------------------------------------
//  PLANIFICADOR 1 (lista enlazada)

class Planificador1 : public Planificador{

private:
    Lista<Evento>* eventos = new Lista<Evento>();
    void ordenar();
    void ordenaQS(int primero, int ultimo);
    unsigned int getHoraDelEvento(int posicion);
    void swapEventos(int posicionA, int posicionB);

public:
    void agregarEventos() override ;
    Evento getProximoEvento() override ;

};


void Planificador1::ordenar(){

    // Primero obtener la cantidad de Nodos en la lista de eventos
    int nroDeEventos = 0;

    Nodo<Evento>* nodoEvento = eventos->nodo();

    while(!nodoEvento->es_vacio()){
        nroDeEventos++;
        nodoEvento = nodoEvento->get_next();
    }
    cout << "Numero de eventos en la lista: " << nroDeEventos << endl;

    ordenaQS(0, nroDeEventos);
}

// Implementacion del Algoritmo Quick Sort
void Planificador1::ordenaQS(int primero, int ultimo){

    int i,j,pivot;

    if(ultimo>primero){

        pivot= getHoraDelEvento(ultimo);
        i=primero-1;
        j=ultimo;

        for(;;){
            while(getHoraDelEvento(++i) <pivot);
            while(getHoraDelEvento(--j) >pivot);
            if(i >= j) break;
            swapEventos(i,j);
        }
        swapEventos(i, ultimo);

        ordenaQS(primero,i-1);
        ordenaQS(i+1,ultimo);
    }
}

// Devuelve la hora de ejecucion del evento en la posicion especificada de la lista
unsigned int Planificador1::getHoraDelEvento(int posicion){

    Nodo<Evento>* nodoEvento = eventos->nodo();

    for(int c = 0; c <= posicion; c++){

        if(c == posicion){

            return nodoEvento->get_dato().horaDeEjecucion;
        }
        nodoEvento = nodoEvento->get_next();
    }
    return 0;
}

// Intercambia los Nodos en las respectivas posiciones de la lista enlazada de eventos
void Planificador1::swapEventos(int posicionA, int posicionB){

        // Obtengo la posicion mas grande para determinar los ciclos del for
        if (posicionA < posicionB) {

            int temp = posicionA;
            posicionA = posicionB;
            posicionB = temp;
        }

    Nodo<Evento> *nodoEvento = eventos->nodo();

    if(posicionA == posicionB || !nodoEvento || !nodoEvento->get_next())
        return;

    Nodo<Evento> *nodoA = nullptr;
    Nodo<Evento> *nodoB = nullptr;
    Nodo<Evento> *previoA = nullptr;
    Nodo<Evento> *previoB = nullptr;

    for(int x = 0; x <= posicionA; x++){

        if(x == (posicionA - 1)){previoA = nodoEvento;}
        if(x == posicionA){nodoA = nodoEvento;}
        if(x == (posicionB - 1)){previoB = nodoEvento;}
        if(x == posicionB){nodoB = nodoEvento;}

        nodoEvento = nodoEvento->get_next();
    }

    if(!nodoA || !nodoB)
        return;

    if(previoA){
        previoA->set_next(nodoB);
    } else { // nodeA is head
        eventos->czo = nodoB;
    }

    if(previoB){
        previoB->set_next(nodoA);
    } else { // nodeB is head
        eventos->czo = nodoA;
    }

    Nodo<Evento> *tmp = nodoA->get_next();
    nodoA->set_next(nodoB->get_next());
    nodoB->set_next(tmp);
}



void Planificador1::agregarEventos(){

    Nodo<Reloj*>* nodoReloj = relojes->nodo();

    while(!nodoReloj->es_vacio()){

        // Arreglo de punteros a objetos Evento
        Evento** ArrDeEventos = nodoReloj->get_dato()->getEventos();

        for(int x = 0; x < 50; x++){

            // Guarda los eventos en la lista del planificador donde seran ordenados y luego ejecutados
            eventos->add(*ArrDeEventos[x]);
        }
        nodoReloj = nodoReloj->get_next();
    }
    ordenar();
}

Evento Planificador1::getProximoEvento(){

    Evento ev = eventos->cabeza();
    eventos->borrar();

    return  arrDeEventos[0];
}

//-------------------------------------------------------------------------------------------
//  PLANIFICADOR 2

class Planificador2 : public Planificador{

private:
    Evento* eventos[100];
    void ordenar();
    unsigned int getHoraDelEvento(int posicion);

public:
    void agregarEventos() override ;
    Evento getProximoEvento() override ;

};


void Planificador2::ordenar(){
    std::cout << "ordena" << '\n';
}

// Devuelve la hora de ejecucion del evento en la posicion especificada de la lista
unsigned int Planificador2::getHoraDelEvento(int posicion){
    std::cout << "getHora" << '\n';
}

void Planificador1::agregarEventos(){

    Nodo<Reloj*>* nodoReloj = relojes->nodo();

    while(!nodoReloj->es_vacio()){

        // Arreglo de punteros a objetos Evento
        Evento** ArrDeEventos = nodoReloj->get_dato()->getEventos();

        for(int x = 0; x < 50; x++){

            // Guarda los eventos en la lista del planificador donde seran ordenados y luego ejecutados
            eventos->add(*ArrDeEventos[x]);
        }
        nodoReloj = nodoReloj->get_next();
    }
    ordenar();
}

Evento Planificador1::getProximoEvento(){

    Evento ev = eventos->cabeza();
    eventos->borrar();

    return  arrDeEventos[0];
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
    Planificador1* p1 = new Planificador1();

    if(archivo.is_open()){

        cout << "**************** Relojes Cargados ******************" << endl;

        cargarRelojes(p1, archivo);
        archivo.close();

        cout << "**************** Eventos Lanzados ******************" << endl;

        int c = 0;
        while(c<=2000) {
            p1->run();
            c++;
        }
    }
    else{
        cout << "El archivo no pudo ser abierto.";
        exit(1);  // Terminacion del programa por error
    }

    return 0;
}



/*
 *     PROBLEMAS:
 *     1) Imprime un cero entre los primeros 500 eventos.
 *     2) Darle formato al tiempo de los eventos (No es la prioridad en este momento)
 *
 */
