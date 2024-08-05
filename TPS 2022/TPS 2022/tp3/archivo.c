#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include "archivo.h"
#include <string.h>

#define ESTADO_VIVO "vivo"
#define ESTADO_MUERTO "muerto"
#define ESCRITURA "%i;%s;%i;%c\n"
#define ERROR -1
#define EDAD_MAXIMA 100
#define EDAD_MINIMA 1
#define ID_MINIMO 1
#define MUERTO  'M'
#define VIVO 'V'
#define LECTURA "%i;%[^;];%i;%c\n"
#define MAX_ESTADOS 10

void mostrar_heroe(superheroe_t heroe){
    char estado_actual[MAX_ESTADOS]= " ";
    if(heroe.estado == VIVO){
        strcpy(estado_actual,ESTADO_VIVO);
    }else if(heroe.estado == MUERTO){
        strcpy(estado_actual,ESTADO_MUERTO);
    }

    printf("  _________SUPERHEROE________\n |\n");
    printf(" | ID: %i                      \n",heroe.id);
    printf(" | NOMBRE: %s                  \n",heroe.nombre);
    printf(" | EDAD: %i                    \n",heroe.edad);
    printf(" | ESTADO: %s                  \n ",estado_actual);
    printf("|___________________________  \n\n");
}


bool son_los_datos_correctos( superheroe_t superheroe){

    if( superheroe.id < ID_MINIMO){
        printf("El id es invalido\n");
        return false;
    }    
    if(strlen(superheroe.nombre) > MAX_NOMBRE){
        printf("El nombre es muy largo\n");
        return false;
    }          
    if( superheroe.edad > EDAD_MAXIMA || superheroe.edad <  EDAD_MINIMA){
        printf(" La edad no es valida\n");
        return false;
    }
    return true;
}

bool estado_correcto(char estado[MAX_ESTADOS]){
    
    if(strcmp(estado,ESTADO_VIVO) != 0 && strcmp(estado,ESTADO_MUERTO) != 0){
        printf("EL ESTADO NO ES VALIDO\n");
        return false;
    }
    return true;
    
}

char estado(char estado[MAX_ESTADOS]){
    if(strcmp(estado,ESTADO_VIVO) == 0){
        return VIVO;
    }else{
        return MUERTO;
    }
}

void agregar_heroe(FILE* archivo_heroe, FILE* archivo_aux, superheroe_t superheroe_a_agregar){
    superheroe_t superheroe;
    int leidos= fscanf( archivo_heroe, LECTURA, &(superheroe.id), superheroe.nombre, &(superheroe.edad), &(superheroe.estado));
    bool agregado= false;
        

    while( leidos != EOF){

        if(superheroe_a_agregar.id == superheroe.id){
            printf("EXISTE UN HEROE CON EL MISMO ID POR LO CUAL NO ES POSIBLE AGREGAR\n");
            agregado= true;
        }else if(superheroe_a_agregar.id < superheroe.id && agregado == false){
            fprintf( archivo_aux, ESCRITURA, superheroe_a_agregar.id, superheroe_a_agregar.nombre, superheroe_a_agregar.edad, superheroe_a_agregar.estado);
            printf(" EL SUPERHEROE FUE AGREGADO CON EXITO\n");
            agregado= true;
        }    
            fprintf( archivo_aux, ESCRITURA, superheroe.id, superheroe.nombre, superheroe.edad, superheroe.estado);
            leidos= fscanf( archivo_heroe, LECTURA, &(superheroe.id), superheroe.nombre, &(superheroe.edad), &(superheroe.estado));
        }
        if(superheroe_a_agregar.id > superheroe.id ){
            fprintf( archivo_aux, ESCRITURA, superheroe_a_agregar.id, superheroe_a_agregar.nombre, superheroe_a_agregar.edad, superheroe_a_agregar.estado);
            printf(" EL SUPERHEROE FUE AGREGADO CON EXITO\n");
        }
}

void modificar_heroe(FILE* archivo_heroes, FILE* archivo_aux, superheroe_t superheroe_a_modificar){
    superheroe_t superheroe;
    bool modificado= false;
    int leidos= fscanf(archivo_heroes,LECTURA,&(superheroe.id), superheroe.nombre, &(superheroe.edad), &(superheroe.estado));
    

    while( leidos != EOF){
        if(superheroe.id == superheroe_a_modificar.id){
            modificado= true;
            strcpy(superheroe_a_modificar.nombre, superheroe.nombre);
            fprintf(archivo_aux, ESCRITURA,superheroe.id, superheroe.nombre, superheroe_a_modificar.edad, superheroe_a_modificar.estado);
            mostrar_heroe(superheroe_a_modificar);

        }else if(superheroe.id != superheroe_a_modificar.id){
            fprintf(archivo_aux, ESCRITURA,superheroe.id, superheroe.nombre, superheroe.edad, superheroe.estado);
        }
        leidos= fscanf(archivo_heroes,LECTURA,&(superheroe.id), superheroe.nombre, &(superheroe.edad), &(superheroe.estado));
    }
    if(modificado == false){
        printf("EL ID NO EXISTE POR LO QUE NO PUDO MODIFICAR AL SUPERHEROE\n");
    }
}


void contactar_heroe(FILE* archivo_heroes, FILE* archivo_aux,int id){
    superheroe_t superheroe;
    int leidos= fscanf( archivo_heroes, LECTURA, &(superheroe.id), superheroe.nombre, &(superheroe.edad), &(superheroe.estado));
    bool contactado= false;

    while ( leidos == 4){
        if( id == superheroe.id){
            printf(" EL HEROE FUE CONTACTADO CON EXITO\n");
            mostrar_heroe(superheroe);
            contactado= true;
        }else{
            fprintf( archivo_aux, ESCRITURA, superheroe.id, superheroe.nombre, superheroe.edad, superheroe.estado);
        }
        leidos= fscanf( archivo_heroes, LECTURA, &(superheroe.id), superheroe.nombre, &(superheroe.edad), &(superheroe.estado));
    }
    if( contactado == false){
        printf("El ID no existe por lo que no se pudo contactar al Superheroe\n");
    }
} 

void mostrar_informacion(){
    printf("____________________________________________________________________________________________________________________________\n\n");
    printf("  LINEA DE COMANDO PARA LISTAR HEROES:    ./ejecutable listar archivo.csv \n"
        "  Este comando solo recibe el nombre del archivo.cvs y muetra una lista de los superheroes\n");
    printf("____________________________________________________________________________________________________________________________\n\n");
    printf("  LINEA DE COMANDO PARA CONTACTAR HEROES: ./ejecutable contactar ID archivo.csv \n"
        "  Este comando recibe el\n  ID(numero positivo) del superheroe que desea contactar y el archivo.csv\n");
    printf("____________________________________________________________________________________________________________________________\n\n");
    printf("  LINEA DE COMANDO PARA MODIFICAR HEROES: ./ejecutable modificar ID EDAD ESTADO archivo.csv \n"
        "  Este comando recibe el\n  ID(numero positivo)\n  del superheroe que desea modificar\n  EDAD(debe estar dentro del rango 1 a 100 incluidos)\n"
        "a modificar y su estado justo con el nombre del archivo.csv muestrar al superheroe modificado\n");
    printf("____________________________________________________________________________________________________________________________\n\n");
    printf("  LINEA DE COMANDO PARA AGREGAR HEROES:   ./ejecutable agregar ID NOMBRE EDAD ESTADO archivo.csv \n"
        "  Este comando recibe los datos para agregar a un nuevo superheroe \n  ID(debe ser un numero positivo)\n  NOMBRE(no debe ser muy largo)\n"
        "  EDAD(debe estar dentro del rango 1 a 100 incluidos)\n  ESTADO(muerto o vivo)\n  recibe el nombre del archivo.csv agrega al superheroe "
        " dependiendo si se cumplieros las condiciones de los datos del heroe\n");
    printf("____________________________________________________________________________________________________________________________\n\n");
            
}