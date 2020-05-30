#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include "Reloj.h"
#include "Evento.h"

using namespace std;

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
