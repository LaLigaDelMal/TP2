#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <cmath>


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


/////////////////////////////////////////////Codigo de Prueba////////////////////////////////////////////////

template <class T> class NodoBin {
public:
    NodoBin(){};
    Evento evento;
    T info, grado;
    NodoBin *p;
    NodoBin *hijo;
    NodoBin *hermano;
};


template <class T> class BinomialHeap {
private:
    NodoBin<T>* raiz;				// apunta a la raíz del árbol binomial más a la izquierda

    void inicioNodo(NodoBin<T>* nodo, T info, T grado, Evento event) {		//inicializo en null
        nodo->evento = event;
        nodo->info = info;
        nodo->grado = grado;
        nodo->p = NULL;
        nodo->hijo = NULL;
        nodo->hermano = NULL;
    }

    static void UnirArbolBinomial(NodoBin<T>* x, NodoBin<T>* y) {
        // x debe ser padre de y
        y->p = x;
        y->hermano = x->hijo;
        x->hijo = y;

        // aumenta el grado de x
        x->grado += 1;
    }

public:
    BinomialHeap() {	raiz = NULL;	}


/*	NodePtr getMinimo() {							// encuentra el nodo con los datos mas chicos (compara todas las raices de los arboles y elije la mas chica)
		int min = 999999;
		NodePtr raizPtr = raiz;
		NodePtr minPtr = NULL;

		while (raizPtr != NULL) {
			if (raizPtr->info < min) {
				min = raizPtr->info;
				minPtr = raizPtr;
			}
			raizPtr = raizPtr->hermano;
		}

		return minPtr;

	}*/


    void creoHeap() {
        // B0
        Evento* ev = new Evento("Evento original",0);
        NodoBin<T>* node1 = new NodoBin<T>;
        inicioNodo(node1, 0, 0, *ev);
        raiz = node1;

    }


    void insert(int info, Evento ev) {        //inserto un nodo
        BinomialHeap h;
        NodoBin<T>* node = new NodoBin<T>;
        inicioNodo(node, info, 0, ev);
        h.setRaiz(node);
        merge(h);
    }

/*
    void printHeap() {
        Nodo<T>* currPtr = raiz;
        while (currPtr != NULL) {
            cout<<"B"<<currPtr->grado<<endl;
            cout<<"Hay "<<pow(2, currPtr->grado)<<" nodos en este arbol"<<endl;
            cout<<"El recorrido de orden de nivel es"<<endl;
            queue<Nodo<T>*> q;
            q.push(currPtr);
            while (!q.empty()) {
                Nodo<T>* p = q.front();
                q.pop();
                cout<<p->info<<" ";

                if (p->hijo != NULL) {
                    Nodo<T>* tempPtr = p->hijo;
                    while (tempPtr != NULL) {
                        q.push(tempPtr);
                        tempPtr = tempPtr->hermano;
                    }
                }
            }
            currPtr = currPtr->hermano;
            cout<<endl<<endl;
        }
    }

*/
    NodoBin<T>* getRaiz() {
        return raiz;
    }

    void setRaiz(NodoBin<T>* raiz) {
        this->raiz = raiz;
    }


    //fusiona dos heap binomial del mismo grado H y H' = H
    void merge(BinomialHeap h1) {
        NodoBin<T>* curr1 = getRaiz();
        NodoBin<T>* curr2 = h1.getRaiz();
        NodoBin<T>* curr3 = NULL;
        NodoBin<T>* temp = NULL;

        if (curr1->grado <= curr2->grado) {
            curr3 = curr1;
            curr1 = curr1->hermano;
        } else {
            curr3 = curr2;
            curr2 = curr2->hermano;
        }

        temp = curr3;

        // 1- fusiona dos montones sin cuidar los árboles con el mismo grado
        //    las raíces del árbol deben estar en orden ascendente de grado de izquierda a derecha
        while(curr1 != NULL && curr2 != NULL) {
            if (curr1->grado <= curr2->grado) {
                curr3->hermano = curr1;
                curr1 = curr1->hermano;
            } else {
                curr3->hermano = curr2;
                curr2 = curr2->hermano;
            }
            curr3 = curr3->hermano;
        }

        // copia todos los árboles restantes de heap1
        if (curr1 != NULL) {
            while(curr1 != NULL) {
                curr3->hermano = curr1;
                curr1 = curr1->hermano;
                curr3 = curr3->hermano;
            }
        }

        // copia todos los árboles restantes de heap2
        if (curr2 != NULL) {
            while(curr2 != NULL) {
                curr3->hermano = curr2;
                curr2 = curr2->hermano;
                curr3 = curr3->hermano;
            }
        }

        // 2- combina repetidamente árboles binarios con el mismo grado
        curr3 = temp;
        NodoBin<T>* prev = NULL;
        NodoBin<T>* next = curr3->hermano;

        while (next != NULL) {
            // si dos raíces de árboles adyacentes tienen un grado diferente o 3 raíces consecutivas tienen el mismo grado
            // pasar al siguiente árbol
            if ((curr3->grado != next->grado )|| (next->hermano != NULL && curr3->grado == next->hermano->grado)) {
                prev = curr3;
                curr3 = next;
            } else {
                // de lo contrario, fusionar repetidamente árboles binomiales con el mismo grado (tiene que identif la menor raiz)
                if (curr3->info <= next->info) {
                    curr3->hermano = next->hermano;
                    BinomialHeap::UnirArbolBinomial(curr3, next);
                } else {
                    if (prev == NULL) {
                        temp = next;
                    } else {
                        prev->hermano = next;
                    }

                    BinomialHeap::UnirArbolBinomial(next, curr3);
                    curr3 = next;
                }
            }

            next = curr3->hermano;
        }

        setRaiz(temp);
    }


    NodoBin<T>* borrarMinimo() {

        NodoBin<T>* curr = raiz;
        NodoBin<T>* prevMin = NULL;
        // encuentra la raiz con el dato minimo
        NodoBin<T>* minPtr = NULL;
        NodoBin<T>* prevPtr = NULL;
        int min = 999999;

        while (curr != NULL) {
            if (curr->info <= min) {
                min = curr->info;
                prevMin = prevPtr;
                minPtr = curr;
            }
            prevPtr = curr;
            curr = curr->hermano;
        }

        // borro el puntero al nodo minimo
        if (prevMin != NULL && minPtr->hermano != NULL) {
            prevMin->hermano = minPtr->hermano;
        } else if (prevMin != NULL && minPtr->hermano == NULL) {
            prevMin->hermano = NULL;
        }

        // borraro el puntero a padre
        NodoBin<T>* childPtr = minPtr->hijo;
        while (childPtr != NULL) {
            childPtr->p = NULL;
            childPtr = childPtr->hermano;
        }

        // reacomodo
        stack<NodoBin<T>*> s;
        childPtr = minPtr->hijo;
        while (childPtr != NULL) {
            s.push(childPtr);
            childPtr = childPtr->hermano;
        }

        curr = s.top();
        NodoBin<T>* temp = curr;
        s.pop();

        while (!s.empty()) {
            curr->hermano = s.top();
            s.pop();
            curr = curr->hermano;
        }

        curr->hermano = NULL;

        BinomialHeap h;
        h.setRaiz(temp);

        merge(h);

        return minPtr;
    }

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

        archivo << buffer << " " << ev.nombreDelEvento<<endl;
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

        // Recursion Binaria
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
            comparaciones++;// el hijo es > temporario
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



//-------------------------------------------------------------------------------------------
//  PLANIFICADOR 3 (Heap Binomial)

class Planificador3 : public Planificador{

private:
    BinomialHeap<int> binHeap;

public:
    Planificador3(){binHeap.creoHeap();};
    void agregarEventos() override;
    Evento getProximoEvento() override;
};

void Planificador3::agregarEventos() {

    // Se inicializa nodoReloj con el puntero al comienzo de la lista
    Nodo<Reloj*>* nodoReloj = relojes->nodo();

    // Se recorre la lista de relojes y se le extraen los eventos a cada uno
    while(!nodoReloj->es_vacio()){

        // Arreglo de punteros a objetos Evento
        Evento** temp = nodoReloj->get_dato()->getEventos();

        for(int x = 0; x < 50; x++){

            binHeap.insert(temp[x]->horaDeEjecucion,*temp[x]);
        }
        nodoReloj = nodoReloj->get_next();
    }
}

Evento Planificador3::getProximoEvento() {

    return binHeap.borrarMinimo()->evento;

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

     //   cout << numeroDeReloj << " " << tiempoDeRepeticion << " " << nombreDeReloj << " " << aleatorio << endl;
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
    Planificador2* p2 = new Planificador2();
    Planificador3* p3 = new Planificador3();

    if(archivo.is_open()){

      //  cout << "**************** Relojes Cargados ******************" << endl;

        cargarRelojes(p1, archivo);

        archivo.clear();
        archivo.seekg(0, std::ios::beg);

        cargarRelojes(p2, archivo);

        archivo.clear();
        archivo.seekg(0, std::ios::beg);

        cargarRelojes(p3, archivo);

        archivo.close();
/*

        cout << "**************** Eventos Lanzados (Planificador 1) ******************" << endl;

        int c = 0;
        while(c<=2000) {     // Puse 2000 solo para probar
            p1->run();
            c++;
        }

        cout << "**************** Eventos Lanzados (Planificador 2) ******************" << endl;

        int x = 0;
        while(x<=2000) {
            p2->run();
            x++;
        }
*/
        cout << "**************** Eventos Lanzados (Planificador 3) ******************" << endl;

        int y = 0;
        while(y<=2000) {
            p3->run();
            y++;
        }


        cout << "Numero de comparaciones del Planificador 1 (QS): " << p1->comparaciones << endl;
        cout << "Numero de comparaciones del Planificador 2 (Heap): " << p2->comparaciones << endl;
    }
    else{
        cout << "El archivo no pudo ser abierto.";
        exit(1);  // Terminacion del programa por error
    }

    return 0;
}
