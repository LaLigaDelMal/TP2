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
// NODO de BINOMIAL HEAP

template <class T> class NodoBH
{
public:
    T n;
    int degree;
    NodoBH<T>* parent;
    NodoBH<T>* child;
    NodoBH<T>* sibling;

    NodoBH();
    NodoBH(T a);
};

template <class T> NodoBH<T>::NodoBH(){
    parent = NULL;
    child = NULL;
    sibling = NULL;
}

template <class T> NodoBH<T>::NodoBH(T a){
    n = a;
    next = NULL;
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

    unsigned int tiempo = intervaloRep;
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
//Binomial Heap

template <class T> class BinomialHeap {
private:
    NodoBH<T> *H;
    NodoBH<T> *Hr;
    int count;
public:
    NodoBH<T>* Initializeheap();
    void Binomial_link(NodoBH<T>*, NodoBH<T>*);
    NodoBH<T>* Create_node(T);
    NodoBH<T>* Union(NodoBH<T>*, NodoBH<T>*);
    NodoBH<T>* Insert(NodoBH<T>*, NodoBH<T>*);
    NodoBH<T>* Merge(NodoBH<T>*, NodoBH<T>*);
    NodoBH<T>* Extract_Min(NodoBH<T>*);
    void Revert_list(NodoBH<T>*);
    int Display(NodoBH<T>*);
    NodoBH<T>* Search(NodoBH<T>*, int);
    //int Decrease_key(NodeBH<T>*, int, int);
    int Delete(NodoBH<T>*);
    BinomialHeap()
    {
        H = Initializeheap();
        Hr = Initializeheap();
        int count = 1;
    }
};

//Iniciar HEAP
template <class T> NodoBH<T>* BinomialHeap<T>::Initializeheap(){
    NodoBH<T>* np;
    np = NULL;
    return np;
}

//Linkear nodos en el HEAP
template <class T> void BinomialHeap<T>::Binomial_link(NodoBH<T>* y, NodoBH<T>* z){
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

//Crear nodos en el HEAP
template <class T> NodoBH<T>* BinomialHeap<T>::Create_node(T k){
    NodoBH<T>* p = new NodoBH<T>;
    p->n = k;
    return p;
}

//Insertar nodos
template <class T> NodoBH<T>* BinomialHeap<T>::Insert(NodoBH<T>* H, NodoBH<T>* x){
    NodoBH<T>* H1 = Initializeheap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = Union(H, H1);
    return H;
}

//Union de Nodos
template <class T> NodoBH<T>* BinomialHeap<T>::Union(NodoBH<T>* H1, NodoBH<T>* H2){
    NodoBH<T> *H = Initializeheap();
    H = Merge(H1, H2);
    if (H == NULL)
        return H;
    NodoBH<T>* prev_x;
    NodoBH<T>* next_x;
    NodoBH<T>* x;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
            && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
	    {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                Binomial_link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Binomial_link(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->sibling;
    }
    return H;
}

//Merge nodos
template <class T> NodoBH<T>* BinomialHeap<T>::Merge(NodoBH<T>* H1, NodoBH<T>* H2)
{
    NodoBH<T>* H = Initializeheap();
    NodoBH<T>* y;
    NodoBH<T>* z;
    NodoBH<T>* a;
    NodoBH<T>* b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }
    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

//Printear Heap
template <class T> int BinomialHeap<T>::Display(NodoBH<T>* H)
{
    if (H == NULL)
    {
        cout<<"The Heap is empty"<<endl;
        return 0;
    }
    cout<<"The root nodes are: "<<endl;
    NodoBH<T>* p;
    p = H;
    while (p != NULL)
    {
        cout<<p->n;
        if (p->sibling != NULL)
            cout<<"-->";
        p = p->sibling;
    }
    cout<<endl;
}

//Extraer Minimo
template <class T> NodoBH<T>* BinomialHeap<T>::Extract_Min(NodoBH<T>* H1)
{
    Hr = NULL;
    NodoBH<T>* t = NULL;
    NodoBH<T>* x = H1;
    if (x == NULL)
    {
        cout<<"Nothing to Extract"<<endl;
        return x;
    }
    int min = x->n;
    NodoBH<T>* p = x;
    while (p->sibling != NULL)
    {
        if ((p->sibling)->n < min)
        {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;
    if (x->child != NULL)
    {
        Revert_list(x->child);
        (x->child)->sibling = NULL;
    }
    H = Union(H1, Hr);
    return x;
}

//Revertir Lista
template <class T> void BinomialHeap<T>::Revert_list(NodoBH<T>* y)
{
    if (y->sibling != NULL)
    {
        Revert_list(y->sibling);
        (y->sibling)->sibling = y;
    }
    else
    {
        Hr = y;
    }
}

//Buscar Nodos en el HEAP
template <class T> NodoBH<T>* BinomialHeap<T>::Search(NodoBH<T>* H, int k){
    NodoBH<T>* x = H;
    NodoBH<T>* p = NULL;
    if (x->n == k)
    {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL)
        p = Search(x->child, k);
    if (x->sibling != NULL && p == NULL)
        p = Search(x->sibling, k);
    return p;
}

//Borrar nodo
template <class T> int BinomialHeap<T>::Delete(NodoBH<T>* H){
    NodoBH<T>* np;
    if (H == NULL){
        cout<<"\nHEAP EMPTY!!!!!";
        return 0;
    }
    np = Extract_Min(H);
    if (np != NULL)
        cout<<"Node Deleted Successfully"<<endl;
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
    cout << ev.horaDeEjecucion << ' ' << ev.nombreDelEvento << endl;
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
        time_t my_time = ev.horaDeEjecucion + time(nullptr);
        struct tm * timeinfo;
        char buffer [80];
        timeinfo = localtime (&my_time);
        strftime (buffer,80,"%m-%d-%G %H:%M:%S",timeinfo);

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

    return  ev;
}

//-------------------------------------------------------------------------------------------
//  PLANIFICADOR 1 (lista enlazada)

// class Planificador2 : public Planificador{
//
// private:
//     Evento* eventos[] = NULL;
// public:
//     void agregarEventos() override ;
//
// };
//
// void Planificador2::agregarEventos(){
//     //Reloj Auxiliar
//     Nodo<Reloj*>* nodoReloj = relojes->nodo();
//     //Obtener eventos del reloj
//     while(!nodoReloj->es_vacio()){
//         // Arreglo de punteros a objetos Evento
//         Evento** ArrDeEventos = nodoReloj->get_dato()->getEventos();
//         Evento* eventosGenerados[50];
//         for(int x = 0; x < 50; x++){
//             // Guarda los eventos en la lista del planificador donde seran ordenados y luego ejecutados
//             eventosGenerados[x] = *ArrDeEventos[x];
//         }
//         //TODO Llamar Funcion de Arreglo dinamico
//         nodoReloj = nodoReloj->get_next();
//     }
//     // ordenar();
// }
//
// // Evento Planificador2::getProximoEvento(){
// //
// //     Evento ev = eventos->cabeza();
// //     eventos->borrar();
// //
// //     return  ev;
// // }



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
int main()
{
    int n, m, l, i;
    BinomialHeap<int> bh;
    NodoBH<int>* p;
    NodoBH<int> *H;
    H = bh.Initializeheap();
    char ch;
    while (1)
    {
        cout<<"----------------------------"<<endl;
        cout<<"Operations on Binomial heap"<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"1)Insert Element in the heap"<<endl;
        cout<<"2)Extract Minimum key node"<<endl;
        cout<<"3)Decrease key of a node"<<endl;
        cout<<"4)Delete a node"<<endl;
        cout<<"5)Display Heap"<<endl;
        cout<<"6)Exit"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>l;
        switch(l)
        {
        case 1:
            cout<<"Enter the element to be inserted: ";
            cin>>m;
            p = bh.Create_node(m);
            H = bh.Insert(H, p);
            break;
        case 2:
            p = bh.Extract_Min(H);
            if (p != NULL)
                cout<<"The node with minimum key: "<<p->n<<endl;
            else
                cout<<"Heap is empty"<<endl;
            break;
        case 4:
            cout<<"Enter the key to be deleted: ";
            cin>>m;
            bh.Delete(H);
            break;
        case 5:
            cout<<"The Heap is: "<<endl;
            bh.Display(H);
            break;
        case 6:
            exit(1);
        default:
            cout<<"Wrong Choice";
	  }
    }
    return 0;
}
// int main(){
//
//     // Leer Archivo
//     ifstream archivo;
//     archivo.open("relojes.txt");
//
//     // Inicializar planificadores
//     Planificador1* p1 = new Planificador1();
//
//     if(archivo.is_open()){
//
//         cout << "**************** Relojes Cargados ******************" << endl;
//
//         cargarRelojes(p1, archivo);
//         archivo.close();
//
//         cout << "**************** Eventos Lanzados ******************" << endl;
//
//         int c = 0;
//         while(c<=2000) {
//             p1->run();
//             c++;
//         }
//     }
//     else{
//         cout << "El archivo no pudo ser abierto.";
//         exit(1);  // Terminacion del programa por error
//     }
//
//     return 0;
// }



/*
 *     PROBLEMAS:
 *     1) Imprime un cero entre los primeros 500 eventos.
 *     2) Darle formato al tiempo de los eventos (No es la prioridad en este momento)
 *
 */
