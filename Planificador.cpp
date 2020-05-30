#include <cstdlib>
#include <iostream>
#include "Planificador.h"
#include "Lista.h"

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
