#include <string>
#include <ctime>
#include "Evento.cpp"

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
  Reloj(int numRel, int tieRep, string nomRel, bool al): numeroDeReloj(numRel), intervaloRep(tieRep), nombreDeReloj(nomRel), aleatorio(al){};
  ~Reloj(){};

  void generarEventos();
  Evento* getEventos();

};

void Reloj::generarEventos(){

    unsigned int tiempo = 0;
    string nombre;

  if(aleatorio == true){

    for(int c = 0; c < 50; c++){

      nombre = nombreDeReloj + " Evento " + std::to_string(c + 1);
      this->eventos[c] = new Evento(nombre, tiempo);
      tiempo += generarRnd(intervaloRep);
    }

  }else{

      for(int c = 0; c < 50; c++){

        nombre = nombreDeReloj + " Evento " + std::to_string(c + 1);
        this->eventos[c] = new Evento(nombre, tiempo);
        tiempo += intervaloRep;
      }
  }
}

Evento* Reloj::getEventos(){

    return this->eventos[50];
}

int Reloj::generarRnd(int max){

  srand((unsigned) time(0));
  return (rand() % max);
}


#endif
