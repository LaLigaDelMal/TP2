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

    if(contAux == 500){

        regenerar();
        contAux = 0;
    }
}

void Planificador::regenerar(){

    Nodo<Reloj>* nodoReloj = relojes->nodo();
    // Vover a generar 50 eventos por reloj cargado en el planificador (lista de relojes)
    while(!nodoReloj->es_vacio()){
        nodoReloj->get_dato().generarEventos();
        nodoReloj = nodoReloj->get_next();
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
        cargarRelojes(p1, archivo);
        archivo.close();

        p1->run();
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
