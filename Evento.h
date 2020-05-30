#include <string>

#ifndef EVENTO_H
#define EVENTO_H

using namespace std;

class Evento {

public:
  Evento(){};
  Evento(string nombre, unsigned int tiempo)
            : nombreDelEvento(nombre), horaDeEjecucion(tiempo){};   //Constructor con parametros
  string nombreDelEvento;
  unsigned int horaDeEjecucion;

};

#endif
