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

void listadoGeneral(Tnodo ** pen, Tnodo ** real, Tnodo ** enProc);

//Funciones lista enlazada
Tarea CrearTarea(int id);
Tnodo * CrearNodo(Tarea valor);
Tnodo * CrearListaVacia();
void Insertar(Tnodo ** start, Tnodo * nodo);
void InsertarAlFinal(Tnodo * Start, Tarea valor);
Tnodo * buscarNodoId(Tnodo * Start, int IdBuscado);
Tnodo * buscarNodoPalabra(Tnodo * PStart, Tnodo * RStart, Tnodo * EPStart);
Tnodo * QuitarNodo(Tnodo **Start, int dato);
void EliminarNodo(Tnodo * nodo);
void mostrarLista(Tnodo *Start);
void mostrarNodo(Tnodo *nodo);
void MostrarDatos(Tnodo *Start);
void MoverTarea(Tnodo **Pen, Tnodo **Real, Tnodo **Proc, Tnodo * Nodo);
void LiberarMemoriaLista(Tnodo *Lista);


int main(){
    int respuesta, i=1, id;
    Tarea aux;
    Tnodo *nuevo, *Pendientes, *Realizadas, *EnProceso, *buscar, ** listaAux;

    srand(time(NULL));

    Pendientes = CrearListaVacia();
    Realizadas = CrearListaVacia();
    EnProceso = CrearListaVacia();

    printf("Quiere agregar una tarea? (1.SI 0.NO): ");
    fflush(stdin);
    scanf("%d", &respuesta);
    while(respuesta){
        aux = CrearTarea(i);
        nuevo = CrearNodo(aux);
        Insertar(&Pendientes, nuevo);
        printf("Quiere agregar una tarea? (1.SI 0.NO): ");
        fflush(stdin);
        scanf("%d", &respuesta);
        i++;
    }

    do
    {
        printf("========== MENU ===========\n");
        printf("1- Listar las tareas por categoria\n");
        printf("2- Mostrar tareas pendientes\n");
        printf("3- Mostrar tareas realizadas\n");
        printf("4- Mostrar tareas en proceso\n");
        printf("5- Buscar tarea por ID\n");
        printf("6- Buscar tarea por palabra\n");
        printf("7- Seleccionar tarea\n");
        printf("8- SALIR\n");
        fflush(stdin);
        scanf("%d", &respuesta);

        switch (respuesta)
        {
        case 1:
            listadoGeneral(&Pendientes, &Realizadas, &EnProceso);
            break;
        case 2:
            printf("========= Mostrar pendientes =========\n");
            mostrarLista(Pendientes);
            break;
        case 3:
            printf("========= Mostrar realizadas =========\n");
            mostrarLista(Realizadas);
            break;
        case 4:
            printf("========= Mostrar en proceso =========\n");
            mostrarLista(EnProceso);
            break;
        case 5:
            printf("Ingrese el ID de la tarea que quiere buscar: ");
            fflush(stdin);
            scanf("%d", &id);
            buscar = buscarNodoId(Pendientes, id);
            if(buscar){
                mostrarNodo(buscar);
            }else{
                buscar = buscarNodoId(Realizadas, id);
                if(buscar){
                    mostrarNodo(buscar);
                }else{
                    buscar = buscarNodoId(EnProceso, id);
                    if(buscar){
                        mostrarNodo(buscar);
                    }else{
                        printf("No se encontro ningun nodo que contenga la tarea solicitada\n");
                    }
                }
            }
            break;
        case 6:
            buscar = buscarNodoPalabra(Pendientes, Realizadas, EnProceso);
            if(buscar){
                mostrarNodo(buscar);
            }else{
                printf("No se encontro ningun nodo que contenga la tarea solicitada\n");
            }
            break;
        case 7:
            printf("Ingrese el ID de la tarea que quiere seleccionar: ");
            fflush(stdin);
            scanf("%d", &id);
            buscar = QuitarNodo(&Pendientes, id);
            listaAux = &Pendientes;
            if(!buscar){
                buscar = QuitarNodo(&Realizadas, id);
                listaAux = &Realizadas;
                if(!buscar){
                    buscar = QuitarNodo(&EnProceso, id);
                    listaAux = &EnProceso;
                    if(!buscar){
                        printf("No se encontro ningun nodo que contenga la tarea solicitada\n");
                    }
                }
            }
            if(buscar){
                printf("========== MENU TAREA ==========\n");
                printf("1- Mover tarea\n");
                printf("2- Eliminar tarea\n");
                printf("3- SALIR\n");
                fflush(stdin);
                scanf("%d", &respuesta);

                switch (respuesta)
                {
                case 1:
                    MoverTarea(&Pendientes, &Realizadas, &EnProceso, buscar);
                    break;
                case 2:
                    EliminarNodo(buscar);
                    break;
                case 3:
                    Insertar(listaAux, buscar);
                    break;
                default:
                    break;
                }
            }
            break;
        case 8:
        default:
            break;
        }
    } while (respuesta != 8);

    printf("---- Datos Tareas Pendientes ----\n");
    MostrarDatos(Pendientes);
    printf("---- Datos Tareas Realizadas ----\n");
    MostrarDatos(Realizadas);
    printf("---- Datos Tareas en Proceso ----\n");
    MostrarDatos(EnProceso);

    LiberarMemoriaLista(Pendientes);
    LiberarMemoriaLista(Realizadas);
    LiberarMemoriaLista(EnProceso);
    
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

void Insertar(Tnodo ** start, Tnodo * nodo){
    nodo->siguiente = *start;
    *start = nodo;
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

Tnodo * buscarNodoPalabra(Tnodo * PStart, Tnodo * RStart, Tnodo * EPStart){
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
        if(!aux){
            aux = EPStart;
            while(aux && strstr(aux->valor.Descripcion, buffer) == NULL){
                aux = aux->siguiente;
            }
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

void listadoGeneral(Tnodo ** pen, Tnodo ** real, Tnodo ** enProc){
    int check;
    Tnodo * aux = *pen, *auxAnt = *pen, *nodo;
    printf("============= Listado de tareas =============\n");
    while(aux != NULL)
    {
        do
        {
            printf("Tarea con ID: %d. Ingrese su estado:\n", aux->valor.TareaId);
            printf("1- Pendiente\n", aux->valor.TareaId);
            printf("2- Realizada\n", aux->valor.TareaId);
            printf("3- En proceso\n", aux->valor.TareaId);
            fflush(stdin);
            scanf("%d", &check);
        } while (check != 1 && check != 2 && check != 3);
        
        switch (check){
        case 2:
            auxAnt = aux;
            aux = aux->siguiente;
            nodo = QuitarNodo(pen, auxAnt->valor.TareaId);
            Insertar(real, nodo);
            break;
        case 3:
            auxAnt = aux;
            aux = aux->siguiente;
            nodo = QuitarNodo(pen, auxAnt->valor.TareaId);
            Insertar(enProc, nodo);
            break;
        case 1:
        default:
            auxAnt = aux;
            aux = aux->siguiente;
            break;
        }
    }
}

void mostrarLista(Tnodo *Start){
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

void MostrarDatos(Tnodo *Start){
    int suma = 0, cant = 0;
    while(Start != NULL){
        suma += Start->valor.Duracion;
        cant++;
        Start = Start->siguiente;
    }
    printf("=====================\n");
    printf("Cantidad de tareas: %d\n", cant);
    printf("Duracion total de todas las tareas: %d\n", suma);
    printf("=====================\n");
}

void MoverTarea(Tnodo **Pen, Tnodo **Real, Tnodo **Proc, Tnodo * Nodo){
    int respuesta;
    printf("A que lista quiere mover la tarea?\n");
    printf("1- Pendiente\n");
    printf("2- Realizada\n");
    printf("3- En Proceso\n");
    fflush(stdin);
    scanf("%d", &respuesta);
    switch (respuesta)
    {
    case 1:
        Insertar(Pen, Nodo);
        break;
    case 2:
        Insertar(Real, Nodo);
        break;
    case 3:
        Insertar(Proc, Nodo);
        break;
    default:
        break;
    }
}

void LiberarMemoriaLista(Tnodo *Lista){
    Tnodo * aux;
    while(Lista != NULL){
        aux = Lista;
        Lista = Lista->siguiente;
        EliminarNodo(aux);
    }
}
