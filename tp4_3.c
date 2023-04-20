#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct{
    int TareaId; // num en ciclo iterativo
    char *Descripcion;
    int Duracion; // 10 - 100
}typedef Tarea;

typedef struct Tnodo{
    Tarea valor; //dato
    Tnodo * siguiente; //puntero al siguiente
}Tnodo;

void cargarTareas(Tarea **lista, int cant);
void listadoRealizadas(Tarea **pen, Tarea **real, int cant);
void mostrarRealizadas(Tarea ** real, int cant);
void mostrarPendientes(Tarea ** pend, int cant);
Tarea buscarTareaPorId(Tarea ** real, Tarea ** pen, int cant);
Tarea buscarTareaPorPalabra(Tarea ** real, Tarea ** pen, int cant);


//Funciones lista enlazada
Tarea CrearTarea();
Tnodo * CrearNodo(Tarea valor);
Tnodo * CrearListaVacia();
void InsertarNodo(Tnodo ** Start , Tarea valor);
void InsertarAlFinal(Tnodo * Start, Tarea valor);
Tnodo * buscarNodo(Tnodo * Start, int IdBuscado);
void EliminarNodo(Tnodo * Start, int dato);


int main(){
    int cant, respuesta;
    Tarea **pendientes, **realizadas, aux;
    Tnodo *nuevo, *Pstart, *Rstart;
    Pstart = CrearListaVacia();
    Rstart = CrearListaVacia();

    printf("Quiere agregar una tarea? (1.SI 0.NO): ");
    fflush(stdin);
    scanf("%d", &respuesta);

    while(respuesta){
        aux = CrearTarea();
        InsertarNodo(&Pstart, aux);
        printf("Quiere agregar una tarea? (1.SI 0.NO): ");
        fflush(stdin);
        scanf("%d", &respuesta);
    }

    
    

    cargarTareas(pendientes, cant);
    listadoRealizadas(pendientes, realizadas, cant);
    mostrarRealizadas(realizadas, cant);
    aux = buscarTareaPorId(realizadas,pendientes,cant);
    printf("Tarea: %s\n", aux.Descripcion);
    aux = buscarTareaPorPalabra(realizadas,pendientes,cant);
    printf("Tarea: %s", aux.Descripcion);

    return 0;
}

void cargarTareas(Tarea **lista, int cant){
    char *buffer = (char *)malloc(sizeof(char)*100);
    printf("============= Cargar datos =============\n");
    for (int i = 0; i < cant; i++)
    {
        printf("-------- Tarea %d --------\n", i+1);
        lista[i] = (Tarea *)malloc(sizeof(Tarea)*1);
        lista[i]->TareaId = i+1;
        printf("Ingrese la descripcion: ");
        fflush(stdin);
        gets(buffer);
        lista[i]->Descripcion = (char *)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(lista[i]->Descripcion, buffer);
        lista[i]->Duracion = rand() % 91 + 10;
    }
    free(buffer);
}

void listadoRealizadas(Tarea **pen, Tarea **real, int cant){
    int check;
    printf("============= Listado de tareas realizadas =============\n");
    for (int i = 0; i < cant; i++)
    {
        printf("La tarea con ID: %d esta realizada? (1.SI / 0.NO)\n", pen[i]->TareaId);
        scanf("%d", &check);
        fflush(stdin);
        if(check){
            real[i] = pen[i];
            pen[i] = NULL;
        }
    }
}

void mostrarRealizadas(Tarea ** real, int cant){
    printf("\n=============== Tareas realizadas ===============\n");
    for (int i = 0; i < cant; i++)
    {
        if(real[i]!=NULL){
            printf("===================\n");
            printf("Tarea ID: %d\n", real[i]->TareaId);
            printf("Descripcion: %s\n", real[i]->Descripcion);
            printf("Duracion: %d\n", real[i]->Duracion);
            printf("===================\n");
        }
    }
}

void mostrarPendientes(Tarea ** pend, int cant){
    printf("\n=============== Tareas pendientes ===============\n");
    for (int i = 0; i < cant; i++)
    {
        if(pend[i]!=NULL){
            printf("===================\n");
            printf("Tarea ID: %d\n", pend[i]->TareaId);
            printf("Descripcion: %s\n", pend[i]->Descripcion);
            printf("Duracion: %d\n", pend[i]->Duracion);
            printf("===================\n");
        }
    }
}

Tarea buscarTareaPorId(Tarea ** real, Tarea ** pen, int cant){
    Tarea aux;
    int id;
    printf("Ingrese el ID de la tarea a buscar: ");
    scanf("%d", &id);
    for (int i = 0; i < cant; i++){
        if(real[i] != NULL && real[i]->TareaId == id){
            aux = *real[i];
        }
        if(pen[i] != NULL && pen[i]->TareaId == id){
            aux = *pen[i];
        }
    }
    return aux;
}

Tarea buscarTareaPorPalabra(Tarea ** real, Tarea ** pen, int cant){
    Tarea aux;
    char palabra[50];
    printf("Ingrese la palabra que quiere buscar: ");
    fflush(stdin);
    gets(palabra);
    for (int i = 0; i < cant; i++){
        if(real[i] != NULL && strstr(real[i]->Descripcion, palabra) != NULL){
            aux = *real[i];
        }
        if(pen[i] != NULL && strstr(pen[i]->Descripcion, palabra) != NULL){
            aux = *pen[i];
        }
    }
    return aux;
}

//LISTA ENLAZADA
Tarea CrearTarea(){
    Tarea aux;
    int i=0;
    char *buffer = (char *)malloc(sizeof(char)*100);
    printf("============= Cargar datos =============\n");
    printf("-------- Tarea --------\n");
    aux.TareaId = i+1;
    printf("Ingrese la descripcion: ");
    fflush(stdin);
    gets(buffer);
    aux.Descripcion = (char *)malloc((strlen(buffer)+1)*sizeof(char));
    strcpy(aux.Descripcion, buffer);
    aux.Duracion = rand() % 91 + 10;

    free(buffer);
    return aux;
}

Tnodo * CrearNodo(Tarea valor){
    Tnodo * NNodo = (Tnodo *) malloc (sizeof(Tnodo));
    NNodo->valor = valor;
    NNodo->siguiente = NULL;
    return NNodo;
}

Tnodo * CrearListaVacia(){
    return NULL;
}

void InsertarNodo(Tnodo ** Start , Tarea valor){
    Tnodo * NuevoNodo = CrearNodo(valor);
    NuevoNodo -> siguiente = *Start;
    *Start = NuevoNodo ;
}

void InsertarAlFinal(Tnodo * Start, Tarea valor){
    Tnodo * NuevoNodo = CrearNodo(valor);
    Tnodo * Aux = Start;
    while(Aux->siguiente) {
        Aux = Aux -> siguiente;
    } 
    Aux -> siguiente = NuevoNodo;
}

Tnodo * buscarNodo(Tnodo * Start, int IdBuscado){
    Tnodo * Aux = Start;
    while(Aux && Aux->valor.TareaId != IdBuscado){
    Aux = Aux -> siguiente;
    }
    return Aux;
}

void EliminarNodo(Tnodo * Start, int id){
    Tnodo * Aux = Start;
    Tnodo * AuxAnterior = Start;
    while (Aux && Aux->valor.TareaId != id){
        AuxAnterior = Aux;
        Aux = Aux->siguiente;
    }
    if(Aux){
        AuxAnterior -> siguiente = Aux -> siguiente;
        free(Aux);
    }
}

void listadoRealizadas(Tnodo * pen, Tnodo * real){
    int check;
    Tnodo * aux = pen, *auxAnt = pen;
    printf("============= Listado de tareas realizadas =============\n");
    while(aux != NULL)
    {
        printf("La tarea con ID: %d esta realizada? (1.SI / 0.NO)\n", pen->valor.TareaId);
        scanf("%d", &check);
        fflush(stdin);
        if(check){
            InsertarNodo(real, aux->valor);
            auxAnt->siguiente = aux->siguiente;
        }
        auxAnt = aux;
        aux = aux->siguiente;
    }
}