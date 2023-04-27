#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct{
    int TareaId; // num en ciclo iterativo
    char *Descripcion;
    int Duracion; // 10 - 100
}typedef Tarea;

typedef struct Tnodo{
    Tarea valor; //dato
    struct Tnodo * siguiente; //puntero al siguiente
}Tnodo;

/* void cargarTareas(Tarea **lista, int cant);
void mostrarRealizadas(Tarea ** real, int cant);
void mostrarPendientes(Tarea ** pend, int cant);
Tarea buscarTareaPorId(Tarea ** real, Tarea ** pen, int cant);
Tarea buscarTareaPorPalabra(Tarea ** real, Tarea ** pen, int cant); */

void listadoRealizadas(Tnodo ** pen, Tnodo ** real);

//Funciones lista enlazada
Tarea CrearTarea(int id);
Tnodo * CrearNodo(Tarea valor);
Tnodo * CrearListaVacia();
void InsertarNodo(Tnodo ** Start , Tarea valor);
void InsertarAlFinal(Tnodo * Start, Tarea valor);
Tnodo * buscarNodoId(Tnodo * Start, int IdBuscado);
Tnodo * buscarNodoPalabra(Tnodo * PStart, Tnodo * RStart);
void EliminarNodo(Tnodo * nodo);
void mostrar(Tnodo *Start);
void mostrarNodo(Tnodo *nodo);
Tnodo * QuitarNodo(Tnodo **Start, int dato);

int main(){
    int respuesta, i=1, id;
    Tarea aux;
    Tnodo *nuevo, *Pstart, *Rstart, *buscar;

    srand(time(NULL));

    Pstart = CrearListaVacia();
    Rstart = CrearListaVacia();

    printf("Quiere agregar una tarea? (1.SI 0.NO): ");
    fflush(stdin);
    scanf("%d", &respuesta);
    while(respuesta){
        aux = CrearTarea(i);
        InsertarNodo(&Pstart, aux);
        printf("Quiere agregar una tarea? (1.SI 0.NO): ");
        fflush(stdin);
        scanf("%d", &respuesta);
        i++;
    }

    do
    {
        printf("========== MENU ===========\n");
        printf("1- Listar las tareas realizadas\n");
        printf("2- Mostrar tareas pendientes\n");
        printf("3- Mostrar tareas realizadas\n");
        printf("4- Buscar tarea por ID\n");
        printf("5- Buscar tarea por palabra\n");
        printf("6- SALIR\n");
        fflush(stdin);
        scanf("%d", &respuesta);

        switch (respuesta)
        {
        case 1:
            listadoRealizadas(&Pstart, &Rstart);
            break;
        case 2:
            printf("========= Mostrar pendientes =========\n");
            mostrar(Pstart);
            break;
        case 3:
            printf("========= Mostrar realizadas =========\n");
            mostrar(Rstart);
            break;
        case 4:
            printf("Ingrese el ID de la tarea que quiere buscar: ");
            fflush(stdin);
            scanf("%d", &id);
            buscar = buscarNodoId(Pstart, id);
            if(buscar){
                mostrarNodo(buscar);
            }else{
                buscar = buscarNodoId(Rstart, id);
                if(buscar){
                    mostrarNodo(buscar);
                }else{
                    printf("No se encontro ningun nodo que contenga la tarea solicitada\n");
                }
            }
            break;
        case 5:
            buscar = buscarNodoPalabra(Pstart, Rstart);
            if(buscar){
                mostrarNodo(buscar);
            }else{
                printf("No se encontro ningun nodo que contenga la tarea solicitada\n");
            }
            break;
        case 6:
        default:
            break;
        }
    } while (respuesta != 6);
    
    return 0;
}

//LISTA ENLAZADA
Tarea CrearTarea(int id){
    Tarea aux;
    char *buffer = (char *)malloc(sizeof(char)*100);
    printf("============= Cargar datos =============\n");
    printf("-------- Tarea --------\n");
    aux.TareaId = id;
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

Tnodo * buscarNodoId(Tnodo * Start, int IdBuscado){
    Tnodo * Aux = Start;
    while(Aux && Aux->valor.TareaId != IdBuscado){
        Aux = Aux -> siguiente;
    }
    return Aux;
}

Tnodo * buscarNodoPalabra(Tnodo * PStart, Tnodo * RStart){
    Tnodo * aux  = PStart;
    char buffer[50];
    printf("Ingrese la palabra que quiere buscar: ");
    fflush(stdin);
    gets(buffer);
    while(aux && strstr(aux->valor.Descripcion, buffer) == NULL){
        aux = aux->siguiente;
    }
    if(!aux){
        aux = RStart;
        while(aux && strstr(aux->valor.Descripcion, buffer) == NULL){
            aux = aux->siguiente;
        }
    }
    return aux;
}

void EliminarNodo(Tnodo * nodo){
    free(nodo->valor.Descripcion);
    free(nodo);
}

Tnodo * QuitarNodo(Tnodo **Start, int dato){
    Tnodo * Aux = *Start;
    Tnodo * AuxAnterior = *Start;
    while (Aux && Aux->valor.TareaId != dato){
        AuxAnterior = Aux;
        Aux = Aux->siguiente;
    }
    if(Aux){
        if(AuxAnterior == Aux){
            *Start = (*Start)->siguiente; 
        }else{
            AuxAnterior -> siguiente = Aux -> siguiente;
        }
    }
    return Aux;
}

void listadoRealizadas(Tnodo ** pen, Tnodo ** real){
    int check;
    Tnodo * aux = *pen, *auxAnt = *pen, *nodo;
    printf("============= Listado de tareas realizadas =============\n");
    while(aux != NULL)
    {
        do
        {
            printf("La tarea con ID: %d esta realizada? (1.SI / 0.NO)\n", aux->valor.TareaId);
            fflush(stdin);
            scanf("%d", &check);
        } while (check != 1 && check != 0);
        
        if(check){
            auxAnt = aux;
            aux = aux->siguiente;
            nodo = QuitarNodo(pen, auxAnt->valor.TareaId);
            nodo->siguiente = *real;
            *real = nodo;
            /* InsertarNodo(real, aux->valor);
            EliminarNodo(pen, auxAnt->valor.TareaId); */
        }else{
            auxAnt = aux;
            aux = aux->siguiente;
        }
    }
}

void mostrar(Tnodo *Start){
    while (Start != NULL){
        printf("===================\n");
        printf("Tarea ID: %d\n", Start->valor.TareaId);
        printf("Descripcion: %s\n", Start->valor.Descripcion);
        printf("Duracion: %d\n", Start->valor.Duracion);
        printf("===================\n");
        Start = Start->siguiente;
    }
}

void mostrarNodo(Tnodo *nodo){
    printf("===================\n");
    printf("Tarea ID: %d\n", nodo->valor.TareaId);
    printf("Descripcion: %s\n", nodo->valor.Descripcion);
    printf("Duracion: %d\n", nodo->valor.Duracion);
    printf("===================\n");
}