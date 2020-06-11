#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;

/*struct Node {
	int info; // contains the key
	int grado; // número de hijos
	Node *p; // pointer to parent
	Node *hijo; // pointer to the leftmost child
	Node *hermano; // pointer to the right sibling
};
typedef Node *NodePtr;*/

template <class T> class Nodo {
public:
    T info, grado;
    Nodo *p;
    Nodo *hijo;
    Nodo *hermano;
};


// Class that represents Binomial heap data structure
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


	// create sample heap (given in figure 5) with three trees for testing
	void createSampleHeap() {
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


	//fusiona dos heap binomiales del mismo grado H y H' = H
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

    // 2- combina repetidamente árboles binomiales con el mismo grado
		curr3 = temp;
		Nodo<T>* prev = NULL;
		Nodo<T>* next = curr3->hermano;

		while (next != NULL) {
			// si dos raíces de árboles adyacentes tienen un grado diferente o 3 raíces consecutivas tienen el mismo grado
			// pasar al siguiente árbol
			if ((curr3->grado != next->grado )|| (next->hermano != NULL && curr3->grado == next->hermano->grado)) {
				prev = curr3;
				curr3 = next;
			} else {
				// de lo contrario, fusionar repetidamente árboles binomiales con el mismo grado
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
  int Display(Nodo<T>* H)
  {
      if (H == NULL)
      {
          cout<<"The Heap is empty"<<endl;
          return 0;
      }
      cout<<"The root nodes are: "<<endl;
      Nodo<T>* p;
      p = H;
      while (p != NULL)
      {
          cout<<p->info;
          if (p->hermano != NULL)
              cout<<"-->";
          p = p->hermano;
      }
      cout<<endl;
  }
};



int main() {

	BinomialHeap<int> heap1;

  int vec[10] = { 50,12,18,240,222,45,410,325,38,95 };

	heap1.createSampleHeap();


  for (int i = 0; i < 10; i++) {
      heap1.insert(vec[i]);
  }

  heap1.insert(55);

	heap1.printHeap();
//	heap1.borrarMinimo();
	heap1.printHeap();
	return 0;
}
