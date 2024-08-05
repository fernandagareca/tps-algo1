#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "archivo.h"
#include <stdbool.h>
#include <aio.h>
#define MAX_NOMBRE 50
#define ESTADO_VIVO "vivo"
#define ESTADO_MUERTO "muerto"
#define COMANDO_AGREGAR "agregar"
#define COMANDO_MODIFICAR "modificar"
#define COMANDO_CONTACTAR "contactar"
#define COMANDO_LISTAR "listar"
#define COMANDO_AYUDA "ayuda"
#define LEER "r"
#define ESCRIBIR "w"
#define ESCRITURA "%i;%s;%i;%c\n"
#define LECTURA "%i;%[^;];%i;%c\n"
#define MAX_ESTADOS 10
#define ARCHIVO_AUX "aux.csv"

const int ERROR=-1;
const int EDAD_MAXIMA=100;
const int EDAD_MINIMA=1;
const int ID_MINIMO=1;
const char MUERTO ='M';
const char VIVO='V';
const int ARGUMENTOS_PARA_AGREGAR = 7;
const int ARGUMENTOS_PARA_MODIFICAR= 6;
const int ARGUMENTOS_PARA_CONTACTAR = 4;
const int ARGUMENTOS_PARA_LISTAR= 3;
const int ARGUMENTOS_PARA_AYUDA= 2;
const int COINCIDENCIA=0;

int main(int argc ,char* argv[]){
    
    if(strcmp(argv[1],COMANDO_AGREGAR)== COINCIDENCIA){
        if(argc ==  ARGUMENTOS_PARA_AGREGAR){

            FILE* archivo_heroe = fopen(argv[6], LEER);
            if(archivo_heroe == NULL){
                perror("no se pudo abrir el archivo\n");
                return ERROR;
            }
            FILE* archivo_aux = fopen( ARCHIVO_AUX, ESCRIBIR);
            if(archivo_aux == NULL){
                fclose(archivo_heroe);
                perror("no se pudo abrir el archivo\n");
                return ERROR;
            }
        
            superheroe_t superheroe_a_agregar;
            superheroe_a_agregar.id= atoi(argv[2]);
            strcpy(superheroe_a_agregar.nombre,argv[3]);
            superheroe_a_agregar.edad= atoi(argv[4]);
            superheroe_a_agregar.estado= estado(argv[5]);
            
            if(son_los_datos_correctos(superheroe_a_agregar) && estado_correcto(argv[5])){
                agregar_heroe(archivo_heroe, archivo_aux, superheroe_a_agregar);
            }else{
                return ERROR;
            }
            
            fclose(archivo_heroe);
            fclose(archivo_aux);
            rename(ARCHIVO_AUX, argv[6]);

        }else{
            printf("FALTAN DATOS PARA AGREGAR\n");
        }
        
    }else if(strcmp(argv[1],COMANDO_MODIFICAR)==  COINCIDENCIA){
        if(argc == ARGUMENTOS_PARA_MODIFICAR){

            FILE* archivo_heroes= fopen(argv[5], LEER);
            if(archivo_heroes== NULL){
                perror("no se pudo abrir el archivo heroes\n");
                return ERROR;
            }
            FILE* archivo_aux= fopen(ARCHIVO_AUX, ESCRIBIR);
            if(archivo_aux== NULL){
                perror("el archivo aux no pudo abrirse\n");
                fclose(archivo_heroes);
                return ERROR;
            }
        
            superheroe_t superheroe_a_modificar;
            superheroe_a_modificar.id= atoi(argv[2]);
            superheroe_a_modificar.edad= atoi(argv[3]);
            superheroe_a_modificar.estado= estado(argv[4]);
            if(son_los_datos_correctos(superheroe_a_modificar) && estado_correcto(argv[4])){
                modificar_heroe(archivo_heroes, archivo_aux, superheroe_a_modificar);
            }else{
                return ERROR;
            }
            fclose(archivo_aux);
            fclose(archivo_heroes);
            rename(ARCHIVO_AUX, argv[5]);
        }else{
            printf("FALTAN DATOS PARA MODIFICAR\n");
        }
    }else if(strcmp(argv[1], COMANDO_CONTACTAR)==  COINCIDENCIA){
        if(argc ==  ARGUMENTOS_PARA_CONTACTAR){
            FILE* archivo_heroes= fopen(argv[3], LEER);
            if(archivo_heroes== NULL){
                perror("no se pudo abrir el archivo heroes\n");
                return ERROR;
            }
            FILE* archivo_aux= fopen(ARCHIVO_AUX, ESCRIBIR);
            if(archivo_aux== NULL){
                perror("el archivo aux no pudo abrirse\n");
                fclose(archivo_heroes);
                return ERROR;
            }
            if(atoi(argv[2]) < ID_MINIMO){
                printf("EL ID NO ES VALIDO\n");
                return ERROR;
            }
            contactar_heroe(archivo_heroes, archivo_aux, atoi(argv[2]));
            fclose(archivo_heroes);
            fclose(archivo_aux);
            rename(ARCHIVO_AUX, argv[3]);

        }else{
            printf("FALTAN DATOS PARA CONTACTAR\n");
        }
    }else if(strcmp(argv[1], COMANDO_LISTAR)==  COINCIDENCIA){
        if(argc ==  ARGUMENTOS_PARA_LISTAR){

        FILE* archivo_heroes= fopen(argv[2], LEER);
        if(archivo_heroes== NULL){
            perror("no se pudo abrir el archivo de heroes\n");
            return ERROR;
        }
        superheroe_t superheroe;
        int leidos= fscanf( archivo_heroes, LECTURA, &(superheroe.id), superheroe.nombre, &(superheroe.edad), &(superheroe.estado));
        while(leidos != EOF){
            mostrar_heroe(superheroe);
            leidos= fscanf( archivo_heroes, LECTURA, &(superheroe.id), superheroe.nombre, &(superheroe.edad),&(superheroe.estado));
        }
        fclose(archivo_heroes);
        }else{
            printf("FALTAN DATOS PARA LISTAR\n");
        }
    }else if(strcmp(argv[1],COMANDO_AYUDA)==  COINCIDENCIA){
        if(argc ==  ARGUMENTOS_PARA_AYUDA){
            mostrar_informacion();
        }else{
            printf("FALTAN DATOS PARA  PEDIR IMFORMACION\n");
        }
    }

    return 0;
}