#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include "Reloj.h"
#include "Planificador1.h"    // Lista enlazada
//#include "Planificador2.h"    // Cola de prioridad
//#include "Planificador3.h"    // Monticulo binomial

using namespace std;

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
        if(tipo == "aleatorio")
            aleatorio = true;

        iss >> tiempoDeRepeticion;

        p->agregarReloj(*new Reloj(numeroDeReloj, tiempoDeRepeticion, nombreDeReloj, aleatorio));
    }

};

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
