#include "Reloj.h"
#include "Evento.h"
#include "Lista.h"

#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

class Planificador{

protected:
  Lista<Reloj>* relojes = new Lista<Reloj>(); //Guarda los relojes en una lista (necesario para regenrar)
  void regenerar();                           //Vuelve a crear 50 eventos por cada reloj en el planificador

public:
  unsigned int eventosLanzados, comparaciones, contAux;
  virtual void agregarReloj(Reloj r) = 0;                  // Se debe sobrescribir en cada planificador
  virtual Evento getProximoEvento() = 0;                   // Se debe sobrescribir en cada planificador
  void runito();

};

void Planificador::runito(){

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
#endif
