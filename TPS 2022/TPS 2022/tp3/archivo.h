#ifndef __ARCHIVO_H_
#define __ARCHIVO_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NOMBRE 50
#define MAX_ESTADOS 10

typedef struct superheroe{
    int id;
    char nombre[MAX_NOMBRE];
    int edad;
    char estado;
}superheroe_t;

/*
 *pre-condiciones: Recibe el heroe con todos los campos verificados previamente.
 * pos-condiciones: Muestra al heroe por pantalla con sus datos.
 */
void mostrar_heroe(superheroe_t heroe);

/*
 *pre-condiciones: Recibe al heroe.
 *pos-condiciones: Verifica que el ID sea positivo ,que el NOMBRE no tenga mas de 50 caracteres y que la edad se encuentre dentro del rango 1 a 100,
 *                  devolviendo true si se cumple todos las condiciones o false en caso contrario.
 */
bool son_los_datos_correctos( superheroe_t superheroe);

/*
 *pre-condiciones: Recibe el estado del heroe.
 *pos-condiciones: verifica si el ESTADO es una de las opciones validas (vivo o muerto) ,Devolviendo true en caso afirmativo o false en caso contrario.
 */
bool estado_correcto(char estado[MAX_ESTADOS]);

/*
 *pre-condiciones: Recibe el estado del heroe validado entre (vivo o muerto).
 *pos-condiciones: Devuelve el caracter correspondiente al estado ingresado,si es vivo devuelve (V) o muerto devuelve (M).
 */
char estado(char estado[MAX_ESTADOS]);

/* 
 *pre-condiciones:Recibe el archivo de heroes en formato de lectura, recibe un archivo auxiliar en formato de escritura y el heroe a cargar con los datos validados.
 *pos-condiciones:Agrega al heroe al archivo.csv en la posicion que le corresponde por id mostrando por pantalla la confirmacion a exepcion que el id se encuentre
 *                 en el archivo en ese caso no lo agrega y avisa porque.
 */
void agregar_heroe(FILE* archivo_heroe, FILE* archivo_aux, superheroe_t superheroe_a_agregar);

/*
 *pre-condiciones: Recibe el archivo de heroes.csv en fortado de lectura , un archivo auxiliar en formato de estritura y el superheroe a modificar con todos
 *                 sus campos validados.
 *pos-condiciones: Modifica la EDAD y el ESTADO del heroe correspondiente al id recibido y lo muetra pos pantalla.
 */
void modificar_heroe(FILE* archivo_heroes, FILE* archivo_aux, superheroe_t superheroe_a_modificar);

/*
 *pre-condiciones: Recibe el archivo de heroes.csv en formato de lectura y un archivo auxiliar en formato de escritura,tambien el id validado 
 *               del heroe a contactar.
 *pos-condiciones: Muestra pos pantalla al heroe correspondiente a al id recibido en caso que no exista el id muestra un mensaje que lo indica.
 */
void contactar_heroe(FILE* archivo_heroes, FILE* archivo_aux,int id);

/*
 *pre-condiciones: 
 *pos-condiciones: Muestra por pantalla indicaciones del modo de uso de las lianeas de comando.
 */
void mostrar_informacion();

#endif /*_ARCHIVO_H_ */