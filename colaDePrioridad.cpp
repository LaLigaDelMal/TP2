#include <iostream>

#include <cstdlib>
#include <sstream>
#include <time.h>
#define MAX 50000

using namespace std;

template <class T> class nodo{
private:
    T data;
public:
    nodo(){data = NULL;}
    nodo(T d){data = d;}
    void setData(T d) {data = d;}
    T getData(){return data;}
};

template <class T> class Heap{
private:
    nodo<T>* cola[MAX];
    int tam = 0;
    int contadorEncolar=0;
    int contadorEliminar=0;
public:
    void insertar(T nuevo);
    nodo<T>* reflotar(int pos);
    void elimMin();
    void hundir(int temp);
    void imprimir();
    T minimo(){return (cola[0])->getData();}
    int contarE(){return contadorEncolar;}
    int contarM(){return contadorEliminar;}
    bool empty() {if(tam == 0)return true;
        else return false; };
};


template <class T>
void Heap<T>::insertar(T nuevo) {
    nodo<T>* n = new nodo<T>(nuevo);
    if(tam == 0){//Si no hay nada en la cola, mete el primer elemento;
        cola[tam] = n;
        tam++;
        return;
    }
    if(nuevo >= (cola[(tam-1)/2])->getData()){// si el valor nuevo es mayor o igual a su supuesto padre se ingresa
        contadorEncolar++;
        cola[tam] = n;
        tam++;
        return;
    }
    else{// si el valor nuevo es mas chico que su supuesto padre, pasara a ser el el padre
    cola[tam] = cola[(tam-1)/2];
    cola[(tam-1)/2] = n;
    reflotar((tam-1)/2);// Ahora verifica que nuevo como padre no sea mas chico que su nuevo supuesto padre
    contadorEncolar +=3;
    tam++;
    }
}

template <class T>
nodo<T> * Heap<T>::reflotar(int pos) {
    if((cola[pos])->getData() < (cola[(pos-1)/2])->getData()){// si el valor nuevo es menor a su supuesto padre se intercambian
        contadorEncolar++;
        T temp = cola[(pos-1)/2]->getData();
        cola[(pos-1)/2]->setData(cola[pos]->getData());
        cola[pos]->setData(temp);
        contadorEncolar+=3;
        reflotar((pos-1)/2);
    }
}


template <class T>
void Heap<T>::elimMin() {
    if(tam != 0){//verifica que la cola no este vacia
        (cola[0])->setData((cola[tam-1])->getData());contadorEliminar++;
        cola[tam-1] = NULL;
        hundir(0);//Una vez borrada la cabeza verifica si el padre cumple la condicion
        tam--;
    }
}

template <class T>
void Heap<T>::hundir(int temp) {
    if (cola[(2 * temp) + 1] != NULL && cola[(2 * temp) + 2] != NULL) {contadorEliminar+=2;//CASO HIJOS NO NULOS
        if ((cola[temp])->getData() > (cola[(2 * temp) + 1])->getData() || (cola[temp])->getData() > (cola[(2 * temp) +2])->getData()){//Pregunta si el nuevo padre es mas grande que sus hijos
            contadorEliminar+=2;
            nodo<T> *t = cola[temp];
            if ((cola[(2 * temp) + 1])->getData() <= (cola[(2 * temp) +2])->getData()) {//Si el hijo izquierdo es mas chico o igual que el derecho, el hijo izquierdo es quien se cambia por el padre
                contadorEliminar++;
                cola[temp] = cola[(2 * temp) + 1];
                cola[(2 * temp) + 1] = t;
                contadorEliminar+=2;
                hundir((2 * temp) + 1);//Verifica si el hijo rotado cumple la condicion
            } else {//Si el hijo derecho es mas chico que el izquierdo, es el derecho quien rota con el padre
                cola[temp] = cola[(2 * temp) + 2];
                cola[(2 * temp) + 2] = t;
                contadorEliminar+=3;
                hundir((2 * temp) + 2);//Verifica si el hijo rotado cumple la condicion
            }
        }
        return;
    }

    if (cola[(2 * temp) + 1] != NULL && cola[(2 * temp) + 2] == NULL) {contadorEliminar +=2;//CASO HIJO HIZQUIEDO NO NULO
        if ((cola[temp])->getData() >(cola[(2 * temp) + 1])->getData()) {contadorEliminar ++;//Pregunta si el nuevo padre es mas grande que su hijo izquiedo
            nodo<T> *t = cola[temp];
            cola[temp] = cola[(2 * temp) + 1];
            cola[(2 * temp) + 1] = t;
            contadorEliminar+=3;
            hundir((2 * temp) + 1);//Verifica si el hijo rotado cumple la condicion
        }
        return;
    }
    if (cola[(2 * temp) + 1] == NULL && cola[(2 * temp) + 2] != NULL) {contadorEliminar+=2;//CASO HIJO DERECHO NO NULO
        if ((cola[temp])->getData() >(cola[(2 * temp) + 2])->getData()) {contadorEliminar++;//Pregunta si el nuevo padre es mas grande que su hijo izquiedo
            nodo<T> *t = cola[temp];
            cola[temp] = cola[(2 * temp) + 2];
            cola[(2 * temp) + 2] = t;
            contadorEliminar+=3;
            hundir((2 * temp) + 2);//Verifica si el hijo rotado cumple la condicion
        }
        return;
    }
}

template <class T>
void Heap<T>::imprimir() {
    for(int i=0 ; i < tam ; i++){
        cout<<((cola[i])->getData())<<" ";
    }
    cout<<endl;
}

int main() {
    Heap<int>* h = new Heap<int>();

    srand(time(NULL));
    for(int i = 1; i <= 11000; i++)
    {
        int t=(1 + rand() % (30000 - 1));
        h->insertar(t);
        //cout<<"se ingreso el : "<<t<<endl;
    }
    //h->imprimir();
int actual=0;
    bool estado= true;
    while (!h->empty()){
        //cout<<h->minimo()<<endl;
        if(actual > h->minimo()) estado=false;
        actual=h->minimo();
        h->elimMin();
    }
    if(estado)cout<<"Todo bien"<<endl;
    else cout<<"MAAAAAL"<<endl;
    cout<<"operaciones de agregar: "<<h->contarE()<<endl;
    cout<<"operaciones de eliminar: "<<h->contarM();

}
