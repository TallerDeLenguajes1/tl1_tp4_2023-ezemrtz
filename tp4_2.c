#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct{
    int TareaId; // num en ciclo iterativo
    char *Descripcion;
    int Duracion; // 10 - 100
}typedef Tarea;

void cargarTareas(Tarea **lista, int cant);
void listadoRealizadas(Tarea **pen, Tarea **real, int cant);
void mostrarRealizadas(Tarea ** real, int cant);
Tarea buscarTareaPorId();
Tarea buscarTareaPorPalabra();

int main(){
    int cant;
    Tarea **pendientes, **realizadas;

    //1.
    printf("Ingrese la cantidad de tareas a cargar: ");
    fflush(stdin);
    scanf("%d", &cant);
    pendientes = (Tarea **)malloc(sizeof(Tarea *)*cant);
    realizadas = (Tarea **)malloc(sizeof(Tarea *)*cant);

    for (int i = 0; i < cant; i++){
        pendientes[i] = NULL;
        realizadas[i] = NULL;
    }
    cargarTareas(pendientes, cant);
    listadoRealizadas(pendientes, realizadas, cant);
    mostrarRealizadas(realizadas, cant);

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
