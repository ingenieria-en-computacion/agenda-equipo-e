#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "agenda.h"

// La función 'menu' está implementada en el archivo fuente de la agenda (agenda.c).
void menu(); 

int main(){
    int menu_opt;
    Agenda agenda;
    
    // Variables auxiliares necesarias
    Contacto new_contact; 
    int pos_contacto;
    char search_name[30];
    char search_phone[15];
    char filename[50];
    
    // Inicialización de la agenda
    iniciar_agenda(&agenda); 

    // Bucle principal para mantener el menú
    do {
        // 1. Mostrar el menú (función definida en agenda.c)
        menu(); 
        
        // 2. Capturar la opción
        printf("\nIngrese su opción: ");
        if (scanf("%d", &menu_opt) != 1) {
            while (getchar() != '\n'); 
            menu_opt = -1; // Opción inválida
        }
        
        printf("\n--- Procesando Opción %d ---\n", menu_opt);
        
        // 3. Procesar la opción
        switch (menu_opt)
        {
            case 1: // Añadir contacto
                printf(">>> Añadir Nuevo Contacto <<<\n");
                leer_contacto(&new_contact);
                
                // Corrección: Se eliminó el 'if' porque la función es void
                agregar_contacto(&agenda, new_contact);
                printf("Contacto añadido de forma exitosa.\n");
                break;
            
            case 2: { // Buscar contacto
                int opt_search;
                printf("Seleccione una de las opciones:\n 1.- Buscar por nombre. \n 2.- Buscar por número telefónico\n");
                printf("Opción de búsqueda: ");
                scanf("%d", &opt_search);
                
                while (getchar() != '\n'); // Limpiar el búfer
                
                switch (opt_search)
                {
                    case 1: // Buscar por nombre
                        printf ("Ingresa el nombre del contacto: ");
                        scanf("%s", search_name); 
                        
                        // Corrección: Nombre de función ajustado a agenda.h
                        pos_contacto = buscar_contacto(&agenda, search_name); 
                        
                        if (pos_contacto != -1) {
                            printf("\n-- Contacto Encontrado --\n");
                            mostrar_contacto(agenda.contactos[pos_contacto]);
                        } else {
                            printf("Contacto no encontrado.\n");
                        }
                        break;
                        
                    case 2: // Buscar por número
                        printf ("Ingresa el número telefónico: ");
                        scanf("%s", search_phone); 
                        
                        // Corrección: Nombre de función ajustado a agenda.h
                        pos_contacto = buscar_contacto_x_telefono(&agenda, search_phone);
                        
                        if (pos_contacto != -1) {
                            printf("\n-- Contacto Encontrado --\n");
                            mostrar_contacto(agenda.contactos[pos_contacto]);
                        } else {
                            printf("Contacto no encontrado.\n");
                        }
                        break;
                        
                    default:
                        printf("Opción de búsqueda no válida.\n");
                        break;
                }
                break;
            }
            
            case 3: { // Mostrar/Imprimir la agenda
                int opt_show;
                printf("Cómo quiere ver la agenda:\n 1.- De forma ascendente. \n 2.- De forma descendente\n");
                printf("Opción: ");
                scanf("%d", &opt_show);
                
                switch (opt_show){ 
                    case 1: // Ascendente
                        ordenar_contactos(&agenda); 
                        printf("\n--- Agenda (Ascendente) ---\n");
                        imprimir_agenda(agenda); 
                        break;
                            
                    case 2: // Descendente
                        ordenar_contactos_inv(&agenda); 
                        printf("\n--- Agenda (Descendente) ---\n");
                        imprimir_agenda(agenda); 
                        break;
                    
                    default:
                        printf("Opción de visualización no válida.\n");
                        break;
                }
                break;
            }
            
            case 4: // Guardar contactos
                printf(">>> Guardar Agenda <<<\n");
                printf("Ingrese el nombre del archivo (ej: datos.txt): ");
                scanf("%s", filename);
                // Corrección: Se pasa 'agenda' por valor (sin &) para coincidir con el prototipo
                guardar_contactos(filename, agenda); 
                break;

            case 5: // Cargar contactos
                printf(">>> Cargar Agenda Externa <<<\n");
                printf("Ingrese el nombre del archivo a importar (ej: datos.txt): ");
                scanf("%s", filename);
                cargar_contactos(filename, &agenda);
                break;

            case 0: // Cerrar agenda (Salida del bucle)
                printf("Cerrando agenda. ¡Hasta pronto!\n");
                break;
            
            default:
                printf("Opción no válida. Por favor, ingrese uno de los valores proporcionados (0-5).\n");
                break;
        }
        
        // Pausa
        if (menu_opt != 0) {
            printf("\nPresione ENTER para continuar...");
            while (getchar() != '\n'); 
            getchar(); 
        }
        
    } while (menu_opt != 0);

    return 0;
}