#include "Planificador.h"
#include "Lista.h"


#ifndef PLANIFICADOR1_H
#define PLANIFICADOR1_H

class Planificador1 : public Planificador{

private:
  Lista<Evento>* eventos = new Lista<Evento>();
  void ordenar();

public:
    void agregarReloj(Reloj r) override ;
    Evento getProximoEvento() override ;

};

#endif
