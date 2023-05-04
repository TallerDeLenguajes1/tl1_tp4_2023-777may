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


void inicializar(Nodo ** lista);
void cargarTareas(Nodo ** lista);
void comprobarEstadoTareas(Nodo ** pendiente, Nodo ** hecho);
void mostrarAmbos(Nodo * pendiente, Nodo * hecho);
void mostrarLista(Nodo * lista, char texto[]);
void mostrarTarea(Nodo * tarea);
Nodo *BuscaTareaPorPalabra(Nodo * pendiente, Nodo * hecho, char * clave);
Nodo *BuscaTareaPorId(Nodo * pendiente, Nodo * hecho, int id);
int menu();
void freeMemoria(Nodo ** pendiente, Nodo ** hecho);



void main ()
{
    int  buscado, num;
    char clave[100];
    Nodo *TareasPendientes, *TareasRealizadas;
    inicializar(&TareasPendientes);
    inicializar(&TareasRealizadas);

    num = menu();
    while (num != 0)
    {
        switch (num)
        {
        case 1:
            comprobarEstadoTareas(&TareasPendientes, &TareasRealizadas);
            break;
        case 2:
            mostrarAmbos(TareasPendientes, TareasRealizadas);
            break;
        case 3:
            printf("\nIngrese el ID a buscar: ");
            scanf("%d", &buscado);
            printf("\nBuscando la tarea ID \"%d\": ", buscado);
            mostrarTarea(BuscaTareaPorId(TareasPendientes, TareasRealizadas, buscado));
            break;
        case 4:
            printf("\nIngrese la palabra a buscar: ");
            scanf("%s", clave);
            printf("\n Buscando la tarea con la palabra \"%s\"", clave);
            mostrarTarea(BuscaTareaPorPalabra(TareasPendientes, TareasRealizadas, clave));
            break;
        case 5:
            cargarTareas(&TareasPendientes);
            break;
        }
        num = menu();
    }
    freeMemoria(&TareasPendientes, &TareasRealizadas);
}



void inicializar(Nodo **lista) 
{
    *lista = NULL;
}
void cargarTareas(Nodo ** lista)
{
    Nodo *nuevo;
    char *texto = malloc(sizeof(char)*100);
    srand(time(NULL));
    nuevo = malloc(sizeof(Nodo));
    if (!(*lista))
    {
        nuevo->T.TareaID = 0;
    }else{
        nuevo->T.TareaID = (*lista)->T.TareaID +1;
    }
    printf("\nIngrese la descripcion de la nueva tarea :");
    fflush(stdin);
    gets(texto);
    fflush(stdin);
    nuevo->T.Descripcion = malloc(sizeof(char)*(strlen(texto)+1));
    strcpy(nuevo->T.Descripcion, texto);
    nuevo->T.Duracion = 10 + rand()%91;
    nuevo->Siguiente = *lista;
    *lista = nuevo;
    free(texto);
}
void comprobarEstadoTareas(Nodo ** pendiente, Nodo ** hecho)
{
    int respuesta;
    Nodo *aux = *pendiente, *anterior = *pendiente, *pHecho;
    if (!*pendiente){
        printf("\n  No quedan tareas pendientes\n");
    }
    while (aux)
    {
        printf("\nHa realizado la tarea %d: \"%s\"? \n", (aux)->T.TareaID, (aux)->T.Descripcion);
        do
        {
            printf(" 1: SI \n 0: NO \n" );
            scanf("%d", &respuesta);
        } while (respuesta!= 1 && respuesta!= 0);
        if (respuesta){
            pHecho = aux;
            if (anterior == aux)
            {
                *pendiente = aux->Siguiente;
                anterior = aux->Siguiente;
            }else{
                anterior->Siguiente = aux->Siguiente;
            }
                aux = aux->Siguiente;
                pHecho->Siguiente = *hecho;
                *hecho = pHecho;
            
        }else{
            anterior = aux;
            aux = aux->Siguiente;
        }
    }
}
void mostrarAmbos(Nodo * pendiente, Nodo * hecho)
{
    mostrarLista(hecho, "Realizadas");
    mostrarLista(pendiente, "Pendientes");
}
void mostrarLista(Nodo * lista, char texto[])
{
    printf("\n\nTareas %s: ", texto);
    if (!lista)
    {
        printf("\n    No hay tareas %s \n", texto);
    }
    while(lista)
    {
        mostrarTarea(lista);
        lista = lista->Siguiente;
    }
}
void mostrarTarea(Nodo * tarea)
{
    if (tarea)
    {
        printf("\n  ID: %d",tarea->T.TareaID);
        printf("\n  Descripcion: %s",tarea->T.Descripcion);
        printf("\n  Duracion: %d",tarea->T.Duracion);
        printf("\n---------------------------------------------------------------");
    }else{
        printf("\n    No se ha encontrado la tarea\n");
    }
}
Nodo *BuscaTareaPorPalabra(Nodo * pendiente, Nodo * hecho, char * clave)
{
    while(pendiente)
    {
        if (strstr(pendiente->T.Descripcion, clave))
        {
            return pendiente;
        }
        pendiente = pendiente->Siguiente;
    }
    while(hecho)
    {
        if (strstr(hecho->T.Descripcion, clave))
        {
            return hecho;
        }
        hecho = hecho->Siguiente;
    }
    return NULL;
}
Nodo *BuscaTareaPorId(Nodo * pendiente, Nodo * hecho, int id)
{
    while(pendiente)
    {
        if (pendiente->T.TareaID == id)
        {
            return pendiente;
        }
        pendiente = pendiente->Siguiente;
    }
    while(hecho)
    {
        if (hecho->T.TareaID == id)
        {
            return hecho;
        }
        hecho = hecho->Siguiente;
    }
    return NULL;
}
int menu()
{
    int num;
    printf("\nMENU");
    printf("\n1: Cambiar estado de las tareas pendientes ");
    printf("\n2: Listar las tareas ");
    printf("\n3: Buscar tarea por ID ");
    printf("\n4: Buscar tarea por palabra ");
    printf("\n5: Cargar nueva tarea");
    printf("\n0: Salir \n");
    scanf("%d", &num);
    return num;
}
void freeMemoria(Nodo ** pendiente, Nodo ** hecho)
{
    Nodo * aux;
    while(*hecho)
    {
        aux = *hecho;
        *hecho = aux->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
    free(*hecho);   

    while(*pendiente)
    {
        aux = *pendiente;
        *pendiente = aux->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
    free(*pendiente);    
}