//==============================================================================================
// Name        : tp2-master
// Author      : Castellano Evangelina, Chagay Vera Adriel, Segura Gaspar, Wortley Agustina
// Version     : 1
// Description : Segundo parcial de algoritmos y estructuras de datos
//==============================================================================================
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <signal.h>

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
    int numeroDeReloj, intervaloRep, nroEvento, timeStamp;
    string nombreDeReloj;
    bool aleatorio = false;
    Evento* eventos[50];
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

    unsigned int tiempo = timeStamp;

    string nombre;

    if(aleatorio == true){

        for(int c = 0; c < 50; c++){

            nroEvento++;
            tiempo += generarRnd(intervaloRep);
            nombre = nombreDeReloj + " Evento " + std::to_string(nroEvento);
            eventos[c] = new Evento(nombre, tiempo);
        }

    }else{

        for(int c = 0; c < 50; c++){

            nroEvento++;
            tiempo += intervaloRep;
            nombre = nombreDeReloj + " Evento " + std::to_string(nroEvento);
            eventos[c] = new Evento(nombre, tiempo);
        }
    }
    timeStamp = tiempo;
}

Evento** Reloj::getEventos(){

    return eventos;
}

int Reloj::generarRnd(int max){

    srand((unsigned) time(0));
    int rnd = (rand() % max);
    if (rnd == 0) return 1;   // No se aceptan valores iguales a cero
    return rnd;
}

//-------------------------------------------------------------------------------------------
//  PLANIFICADOR (clase abstracta)

class Planificador{

protected:
    Lista<Reloj*>* relojes = new Lista<Reloj*>(); //Guarda los punteros a relojes en una lista (necesario para regenrar)
    void regenerar();                             //Vuelve a crear 50 eventos por cada reloj en el planificador

public:
    unsigned int eventosLanzados, comparaciones, contAux;
    void agregarReloj(Reloj* r);
    virtual void agregarEventos() = 0;           // Funcion virtual pura
    virtual Evento getProximoEvento() = 0;       // Funcion virtual pura
    void run();
    void imprimir(Evento ev);
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

    //Ejecutar evento
    // cout << ev.horaDeEjecucion << ' ' << ev.nombreDelEvento << endl;

    // Guarda los eventos en el archivo de salida (si este archivo no existe, es creado)
    imprimir(ev);
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

void Planificador::imprimir(Evento ev) {

    ofstream archivo;
    archivo.open("Planificacion.txt", ios::app);

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo de salida.";
        exit(1);
    }else{
        time_t tiempo = ev.horaDeEjecucion + time(nullptr);
        struct tm * info;
        char buffer [80];
        info = localtime (&tiempo);
        strftime (buffer,80,"%m-%d-%G %H:%M:%S",info);
        archivo.close();
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
  //  cout << "Numero de eventos en la lista: " << nroDeEventos << endl;

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
            comparaciones++;
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
    } else { // nodeA es la cabeza
        eventos->czo = nodoB;
    }

    if(previoB){
        previoB->set_next(nodoA);
    } else { // nodeB es la cabeza
        eventos->czo = nodoA;
    }

    Nodo<Evento> *tmp = nodoA->get_next();
    nodoA->set_next(nodoB->get_next());
    nodoB->set_next(tmp);
}


// Se agregan los eventos generados en la lista y luego se ordenan
void Planificador1::agregarEventos(){

    // Se inicializa nodoReloj con el puntero al comienzo de la lista
    Nodo<Reloj*>* nodoReloj = relojes->nodo();

    // Se recorre la lista de relojes y se le extraen los eventos a cada uno
    while(!nodoReloj->es_vacio()){

        // Arreglo de punteros a objetos Evento
        Evento** temp = nodoReloj->get_dato()->getEventos();

        for(int x = 0; x < 50; x++){

            // Guarda los eventos en la lista del planificador donde seran ordenados y luego ejecutados
            eventos->add(*temp[x]);
        }
        nodoReloj = nodoReloj->get_next();
    }
    ordenar();
}

Evento Planificador1::getProximoEvento(){

    Evento ev = eventos->cabeza();
    eventos->borrar();

    return  ev;
}




//-------------------------------------------------------------------------------------------
//  PLANIFICADOR 2 (cola de prioridad)

class Planificador2 : public Planificador{

private:
    Evento** HeapEventos;       // Puntero a un array de punteros a eventos
    unsigned int nroDeEventos = 0;       // Contador de eventos en la heap
    void ordenar();

public:
    void agregarEventos() override;
    Evento getProximoEvento() override;
};


void Planificador2::ordenar() {

    if(nroDeEventos==0) return; // heap esta vacio?
    Evento* temp;
    unsigned int n = nroDeEventos, parent = nroDeEventos/2, index, child; //indices del heap

    while (1) { // while hasta que este ordenado
        if (parent > 0) {
            // primera etapa - ordenar el heap
            temp = HeapEventos[--parent];  // valor temporario

        } else {
            // segunda etapa - extraer elementos
            n--;
            if (n == 0) return;
            temp = HeapEventos[n];
            HeapEventos[n] = HeapEventos[0];
        }

        // insercion
        index = parent; // inicio con el padre
        child = index * 2 + 1; // hijo izquierdo

        while (child < n) {
            comparaciones++;// busco el hijo mayor
            if (child + 1 < n  &&  (HeapEventos[child + 1]->horaDeEjecucion) > (HeapEventos[child]->horaDeEjecucion)) {
                child++; // mayor hijo es el derecho
            }
            //comparaciones++;// el hijo es > temporario
            if ((HeapEventos[child]->horaDeEjecucion) > (temp->horaDeEjecucion)){
                HeapEventos[index] = HeapEventos[child]; // sobreescribo con el hijo

                index = child; // muevo index
                child = index * 2 + 1; // recalculo hijo izq
            } else break; // encontro el lugar para temporario
        }
        HeapEventos[index] = temp;
    }
}


void Planificador2::agregarEventos() {

    // Se cuenta la cantidad de relojes para determinar la cantidad de eventos
    Nodo<Reloj*>* nodoReloj = relojes->nodo();
    unsigned int nroDeRelojes = 0;

    while(!nodoReloj->es_vacio()){

        nroDeRelojes++;
        nodoReloj = nodoReloj->get_next();
    }
   // cout << "Numero de relojes cargados: " << nroDeRelojes << endl;



    Evento** aux = new Evento*[nroDeEventos + (50 * nroDeRelojes)];

    // Se copian los elementos de la heap en el arreglo auxiliar de mayor tamaño
    for(int y = 0; y < nroDeEventos; y++){

        aux[y] = HeapEventos[y];
    }

    nodoReloj = relojes->nodo();

    while(!nodoReloj->es_vacio()) {

        Evento** temp = nodoReloj->get_dato()->getEventos();

        for (int x = 0; x < 50; x++) {

            aux[x + nroDeEventos] = temp[x];
        }
        nroDeEventos += 50;
        nodoReloj = nodoReloj->get_next();
    }

    HeapEventos = aux;

    ordenar();
}


Evento Planificador2::getProximoEvento() {

    // Se eliminar el primer elemento y se desplaza todo el arreglo
    Evento* ev = HeapEventos[0];

    // Shift
    Evento** aux = new Evento*[nroDeEventos - 1];
    for (int i = 1; i < nroDeEventos; ++i) {

        aux[i - 1] = HeapEventos[i];
    }
    nroDeEventos--;
    HeapEventos = aux;

    return *ev;
}


//-----------------------------------------------------------------------------------------
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

     //   cout << numeroDeReloj << " " << tiempoDeRepeticion << " " << nombreDeReloj << " " << aleatorio << endl;
        p->agregarReloj(new Reloj(numeroDeReloj, tiempoDeRepeticion, nombreDeReloj, aleatorio));
    }

};

//------------------------------------------------------------------------------
//CTRL-C HANDLER

int COMP1=0;  //Algunas mouske-variables globales que nos ayudaran mas tarde
int COMP2=0;
int COMP3=0;

void signal_callback_handler(int signum) {
    if(COMP2==0){
        cout << "Numero de comparaciones del Planificador 1 (QS): " << COMP1 << endl;
    }else if(COMP3==0){
        cout << "Numero de comparaciones del Planificador 2 (Heap):  " << COMP2 << endl;
    }else{
        cout << "Numero de comparaciones del Planificador 3 (Heap Binomial):  " << COMP3 << endl;
    }
    exit(signum);
}
//-------------------------------------------------------------------------------------------
//  MAIN

int main(){

    // Leer Archivo
    ifstream archivo;
    archivo.open("relojes.txt");

    // Inicializar planificadores
    Planificador1* p1 = new Planificador1();
    Planificador2* p2 = new Planificador2();
    //Planificador3* p3 = new Planificador3();

    if(archivo.is_open()){

      //  cout << "**************** Relojes Cargados ******************" << endl;

        cargarRelojes(p1, archivo);

        archivo.clear();
        archivo.seekg(0, std::ios::beg);

        cargarRelojes(p2, archivo);

        archivo.close();

        int aa;
        cout << "==============================================================================================" <<'\n'<< endl;
        std::cout << " Name        : Parcial 2" << '\n';
        std::cout << " Author      : Segura Gaspar, Wortley Agustina, Castellano Evangelina, Chagay Vera Adriel" << '\n';
        std::cout << " Version     : 1.0" << '\n';
        std::cout << " Description : Segundo parcial de algoritmos y estructuras de datos" << '\n' <<'\n';
        std::cout << "==============================================================================================" << '\n' << '\n';

        cout << "**************** Seleccionar Planificador ******************" << '\n' << endl;
        cout << "1.- Planificador 1" << '\n' << "2.- Planificador 2" << '\n' << "3.- Planificador 3 (BETA)" << '\n' << '\n';
        cout << "Seleccione una opcion: ";
        cin >> aa;
        switch (aa) {
            case 1:
                cout << '\n' << "**************** Eventos Lanzados (Planificador 1) ******************" << '\n' << endl;
                signal(SIGINT, signal_callback_handler );
                while(true) {
                    p1->run();
                    COMP1=p1->comparaciones;
                }

            case 2:
                cout << '\n' << "**************** Eventos Lanzados (Planificador 2) ******************" << '\n' << endl;
                signal(SIGINT, signal_callback_handler);
                while(true) {
                    p2->run();
                    COMP2=p2->comparaciones;
                }

            case 2:
                cout << '\n' << "**************** Eventos Lanzados (Planificador 3) ******************" << '\n' << endl;
                signal(SIGINT, signal_callback_handler);
                while(true) {
                    //p3->run();
                    //COMP3=p3->comparaciones;
                }
            }

    }
    else{
        cout << "El archivo no pudo ser abierto.";
        exit(1);  // Terminacion del programa por error
    }

    return 0;
}
