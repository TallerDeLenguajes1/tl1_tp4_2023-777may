#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;
struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}typedef Nodo;
struct Conjunto{
    Nodo * TareasPendientes;
    Nodo * TareasRealizadas;
    Nodo * TareasEnProceso;
    Nodo * Anterior;
}typedef Conjunto;



void main ()
{
    Conjunto listas;

}

