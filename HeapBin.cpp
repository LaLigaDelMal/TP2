#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;

template <class T> class Nodo {
public:
    T info, grado;
    Nodo *p;
    Nodo *hijo;
    Nodo *hermano;
};


template <class T> class BinomialHeap {
private:
	Nodo<T>* raiz;				// apunta a la raíz del árbol binomial más a la izquierda

	void inicioNodo(Nodo<T>* nodo, T info, T grado) {		//inicializo en null
		nodo->info = info;
		nodo->grado = grado;
		nodo->p = NULL;
		nodo->hijo = NULL;
		nodo->hermano = NULL;
	}

	static void UnirArbolBinomial(Nodo<T>* x, Nodo<T>* y) {
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
		Nodo<T>* node1 = new Nodo<T>;
		inicioNodo(node1, 0, 0);
		raiz = node1;

}


	void insert(int info) {        //inserto un nodo
		BinomialHeap h;
		Nodo<T>* node = new Nodo<T>;
		inicioNodo(node, info, 0);
		h.setRaiz(node);
		merge(h);
	}


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


	Nodo<T>* getRaiz() {
		return raiz;
	}

	void setRaiz(Nodo<T>* raiz) {
		this->raiz = raiz;
	}


	//fusiona dos heap binomial del mismo grado H y H' = H
	void merge(BinomialHeap h1) {
		Nodo<T>* curr1 = getRaiz();
		Nodo<T>* curr2 = h1.getRaiz();
		Nodo<T>* curr3 = NULL;
		Nodo<T>* temp = NULL;

		if (curr1->grado <= curr2->grado) {
			curr3 = curr1;
			curr1 = curr1->hermano;
		} else {
			curr3 = curr2;
			curr2 = curr2->hermano;
		}

		temp = curr3;


	}

/*	// deletes the smallest node from the heap
	NodePtr borrarMinimo() {
		NodePtr curr = raiz;
		NodePtr prevMin = NULL;
		// find the root with minimum key
		NodePtr minPtr = NULL;
		NodePtr prevPtr = NULL;
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

		// delete the node pointed by minPtr
		if (prevMin != NULL && minPtr->hermano != NULL) {
			prevMin->hermano = minPtr->hermano;
		} else if (prevMin != NULL && minPtr->hermano == NULL) {
			prevMin->hermano = NULL;
		}

		// remove parent reference from all its child
		NodePtr childPtr = minPtr->hijo;
		while (childPtr != NULL) {
			childPtr->p = NULL;
			childPtr = childPtr->hermano;
		}

		// reverse the order
		stack<NodePtr> s;
		childPtr = minPtr->hijo;
		while (childPtr != NULL) {
			s.push(childPtr);
			childPtr = childPtr->hermano;
		}

		curr = s.top();
		NodePtr temp = curr;
		s.pop();

		while (!s.empty()) {
			curr->hermano = s.top();
			s.pop();
			curr = curr->hermano;
		}

		curr->hermano = NULL;

		BinomialHeap h;
		h.setRaiz(temp);

		// merge
		merge(h);

		// return the min root
		return minPtr;
	}
	*/
};



int main() {

	BinomialHeap<int> heap1;

  int vec[10] = { 50,12,18,240,222,45,410,325,38,95 };

	heap1.creoHeap();


  for (int i = 0; i < 10; i++) {
      heap1.insert(vec[i]);
  }

  int vec1[10] = { 60,72,80,77,110,21,4,280,49,97 };

  for (int i = 0; i < 10; i++) {
      heap1.insert(vec1[i]);
  }

  heap1.printHeap();



	return 0;
}
