#include "agenda.h"
#include <stdio.h>
#include <string.h>

// Hola.

/**
 * Esta función se encarga de iniciar el número de contactos a cero
 */
void iniciar_agenda(Agenda *agenda){
    agenda->num_contactos = 0;
}

// Variable que lleva la cuenta de cuantos contactos hay en la agenda
int num_contactos;

/**
 * Esta función sirve para agregar un contacto nuevo en la agenda
 */
void agregar_contacto(Agenda *agenda, Contacto c){
    if(agenda->num_contactos < MAX_CONTACTOS){
        agenda->contactos[agenda->num_contactos] = c;
        agenda->num_contactos++;
    } else {
        printf("La agenda alcazó la cantidad máxima de contactos que se pueden añadir.\n");
        return;
    }
}


/**
 * Esta función sirve para buscar un contacto por nombre en la agenda
 * Retorna la posición del contacto si existe, si no retorna -1
 */
int buscar_contacto_nombre(Agenda *agenda, char *nombre){
    for(int i = 0; i < agenda->num_contactos; i++){
        if(strcmp(agenda->contactos[i].nombre, nombre) == 0){
            return i;
        }
    }
    return -1;
}


/**
 * Esta función sirve para buscar un contacto por su número de teléfono
 */
int buscar_contacto_number(Agenda *agenda, char telefono[]){
    for(int i = 0; i < agenda->num_contactos; i++){
        if(strcmp(agenda->contactos[i].telefono, telefono) == 0){
            return i;
        }
    }
    return -1;
}


/**
 * Esta función sirve para ordenar los contactos por nombres de forma ascendente
 * (ya estaba completa)
 */
void ordenar_contactos(Agenda *a){
    int i, j;
    Contacto temp;
    for(i = 0; i < a->num_contactos; i++){
        for(j=0; j < a->num_contactos-i-1; j++){
            if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre) > 0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Ordenar contactos de forma descendente
 */
void ordenar_contactos_inv(Agenda *a){
    int i, j;
    Contacto temp;

    for(i = 0; i < a->num_contactos; i++){
        for(j=0; j < a->num_contactos-i-1; j++){
            if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre) < 0){ // inverso
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}


/**
 * Función auxiliar para imprimir un contacto
 */
void mostrar_contacto(Contacto c){
    printf("Nombre: %s %s\n", c.nombre, c.apellido);
    printf("Nacimiento: %d/%d\n", c.birth_day, c.birth_month);
    printf("Telefono: %s\n", c.telefono);
    printf("Tipo: %d\n\n", c.device);
}


/**
 * Función auxiliar para leer un contacto
 */
void leer_contacto(Contacto *c){
    printf("Nombre: ");
    scanf("%s", c -> nombre);

    printf("Apellido: ");
    scanf("%s", c -> apellido);

    printf("Día de nacimiento: ");
    scanf("%d", &c -> birth_day);

    printf("Mes de nacimiento: ");
    scanf("%d", &c -> birth_month);

    printf("Telefono: ");
    scanf("%s", c -> telefono);

    printf("Tipo de telefono (1=Casa, 2=Movil...): ");
    scanf("%d", &c -> device);
}


/**
 * Función que imprime todos los contactos de la agenda
 */
void imprimir_agenda(Agenda agenda){
    if(agenda.num_contactos == 0){
        printf("No hay contactos registrados.\n");
        return;
    }

    for(int i = 0; i < agenda.num_contactos; i++){
        printf("Contacto %d:\n", i + 1);
        mostrar_contacto(agenda.contactos[i]);
    }
}


/**
 * Función que sirve para cargar contactos escritos en un archivo
 */
     cargar_contactos(char *filename, Agenda *agenda){
    FILE *f = fopen(filename, "r");

    if(!f){
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    agenda->num_contactos = 0;

    while(!feof(f)){
        Contacto c;

        if(fscanf(f, "%[^|]|%[^|]|%d|%d|%[^|]|%d\n",
                  c.nombre, c.apellido, &c.birth_day, &c.birth_month,
                  c.telefono, &c.device) == 6){

            agregar_contacto(agenda, c);
        }
    }

    fclose(f);
    printf("Contactos cargados correctamente.\n");
}


/**
 * Función que sirve para guardar todos los contactos en un archivo
 */
void guardar_contactos(char *filename, Agenda agenda){
    FILE *f = fopen(filename, "w");

    if(!f){
        printf("No se pudo guardar el archivo.\n");
        return;
    }

    for(int i = 0; i < agenda.num_contactos; i++){
        Contacto c = agenda.contactos[i];

        fprintf(f, "%s|%s|%d|%d|%s|%d\n",
                c.nombre, c.apellido, c.birth_day, c.birth_month,
                c.telefono , c.device);
    }

    fclose(f);
    printf("Contactos guardados exitosamente.\n");
}


/**
 * Menú sencillo
 */
void menu(){
    printf("Agenda personal, favor de escoger lo que quiere realizar:\n");
    printf("1.- Añadir contacto \n 2.- Busca contacto\n 3.- Mostrar la lista de contactos\n 4.- Guardar lista de contactos \n"); 
    printf("5.- Cargar lista de contactos externa \n 0.- Cerrar agenda");
}
