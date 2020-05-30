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
  void run();

};

#endif
