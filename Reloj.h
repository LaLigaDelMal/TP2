#include <string>
#include "Evento.h"

#ifndef RELOJ_H
#define RELOJ_H

using namespace std;

class Reloj {

private:
  int numeroDeReloj, intervaloRep;
  string nombreDeReloj;
  bool aleatorio = false;
  Evento* eventos[50];      // Arreglo de punteros a eventos
  int generarRnd(int max);

public:
  Reloj(int numRel, int tieRep, string nomRel, bool al)
  : numeroDeReloj(numRel), intervaloRep(tieRep), nombreDeReloj(nomRel), aleatorio(al){};
  ~Reloj(){};

  void generarEventos();
  Evento* getEventos();

};

#endif
