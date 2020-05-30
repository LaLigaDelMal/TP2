#include "Planificador1.h"

void Planificador1::ordenar(){

}

void Planificador1::agregarReloj(Reloj r){

    // Se carga el reloj en la lista de relojes del Planificador
    relojes->add(r);

    // Genera 50 eventos por cada reloj que se agrega
    r.generarEventos();
    for(int c = 0; c < 50; c++){
    // Guarda los eventos en la lista del planificador donde seran ordenados y luego ejecutados
    eventos->add(r.getEventos()[c]);
  }
    ordenar();
}

Evento Planificador1::getProximoEvento(){

    Evento ev = eventos->cabeza();
    eventos->borrar();               //Borra la cabeza de la lista

  return  ev;
}
