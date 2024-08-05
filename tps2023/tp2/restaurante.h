#ifndef __RESTAURANTE_H__
#define __RESTAURANTE_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cocineritos.h"
#define MAX_OBJETOS 50
#define MAX_NOMBRE 30


/*
 *pre: Recibe un unn vector de objetos con su tope definido y la fila y columna a verificar.
 *post: Recorre el vector buscando si se repiten las coordenadas en ese caso devuelve true caso contrario false.
 */
bool se_pisan_objetos(objeto_t objeto[MAX_OBJETOS], int tope, int fil ,int col);
/*
 *pre: Recibe in vector de ingredientes con su tope definido y una fila y columna a verificar.
 *post:Recorre el vector de ingredientes verificando si si se repiten las coordenadas ,devolviendo true en caso afirmativo o false en caso contrario.
 */
bool se_pisan_ingredientes(ingrediente_t ingredientes[MAX_INGREDIENTES], int tope, int fil, int col);
/*
 *pre: Recibe las coordenadas de la puerta y una fila y columna.
 *post:Compara las coordenadas de la puerta con la fila y columna recibidas ,devolviendo true si coinciden.
 */
bool se_pisa_puerta(coordenada_t puerta, int fil, int columna);
/*
 *pre: Recibe un personaje y la fila y la columna.
 *post: Devuelve true si las coordenadas del personaje coinciden con la fila y columna recibidas.
 */
bool se_pisa_personaje(personaje_t personaje, int fil, int col);

/*
 *pre: Recibe el movimiento ingresado por el usuario.
 *post:verifica si el movimiento es una opcion valida (W ,S,,D,A,C,T,X,R,M o H) de ser el caso devuelve true.
 */
bool es_movimiento_correcto(char movimiento);
/*
 *pre: Recibe el movimiento ingresado por el usuario y el personaje actual.
 *post: Verifica si el personaje va a pisar alguna pared en su movimiento y devuelve true si es el caso o false caso contrario.
 */
bool pasa_los_limites(char movimiento, personaje_t personaje);

/*
 *pre: Recibe un vector de objetos el personaje actual el movimiento ingresado por el usuario y la posicion del objeto.
 *post:Verifica si el personaje va a pisar al objeto en su siguiente movimiento devuelve true en caso afirmativo o false caso contrario.
 */
bool choca_con_objetos(objeto_t objetos[MAX_OBJETOS], personaje_t personaje, char movimiento, int posicion);
/*
 *pre: recibe el vectopr de obstaculos cargado con su topr definido.
 *post:busca la posicion del Fuego y la devuelve o devuleve -1 si no se encuentra.
 */
int posicion_fuego(objeto_t obstaculos[MAX_OBSTACULOS], int tope);

/*
 *pre: Recibe el personaje actual el juego el vector de obstaculos cargado  y su tope definido.
 *post:Busta la posicion del fuego si existe en el vector devuelve true si esta en el cuadrante del personaje actual y tambien la posicion en el vector.
 */
bool personaje_tiene_fuego(objeto_t obstaculos[MAX_OBSTACULOS], int tope, personaje_t personaje, int* posicion);


/*
 *pre: Recibe el vector de herramientas con su tope y una posicion.
 *post: busca en el vector del horno distnta de la posicion invalida.
 */
int posicion_horno(objeto_t herramientas[MAX_HERRAMIENTAS], int tope, int posicion_invalida);

/*
 *pre: Recibe un vector de objeto con su tope y un elemento.
 *post: busca en el vector ingresado si el elemento se encuentra si es asi devuelve true caso contrario devuelve false.
 */
bool objeto_esta_presente(objeto_t objeto[MAX_OBJETOS], int tope, char elemento);
/*
 *pre: Resive un movimiento valido (W ,S,D,A,C,T,X,R,M o H) el personaje actual un contador para los movimientos y el juego.
 *post:aumenta el contador cuando sea (W ,S,D o A) y no haya fuego en el terreno.
 */
void sumar_movimientos(char movimiento, personaje_t personaje, int* cantidad_movimientos, juego_t juego);
/*
 *pre: Recibe la comida actual.
 *post: Dvuelve la posicion en el vector de comidas dependiendo la comida recibida.
 */
int comida(char comida_actual);
/*
 *pre: Recibe el personaje actual el personaje activo (S o R) a stitch y reuben.
 * post:Devuleve el personeje que esta jugando segun el personaje activo.
 */
personaje_t personaje_actual(char personaje_activo,personaje_t stitch ,personaje_t reuben);
/*
 *pre: Recibe el personaje actual el personaje activo (S o R) a stitch y reuben.
 * post:Devuleve el personeje que esta jugando segun el personaje activo.
 */
personaje_t* personaje(char personaje_activo, personaje_t* stitch, personaje_t* reuben);
/*
 *pre: Recibe un movimiento ingresado por el usuario valido(W ,S,D,A,C,T,X,R,M o H) y el persoanje actual.
 * post: En el caso que el movimiento sea X cambia de jugador.
 */
void cambiar_de_personaje(char* personaje_actual, char movimiento);


/*
 *pre: Recibe un vector de ingredientes cargado con su tope definido y el personaje actual.
 * post:Busca y devuelve la posicion del ingrediente que esta pisando el personaje.
 */
int pos_ingrediente(ingrediente_t ingredientes[MAX_INGREDIENTES], int tope, personaje_t personaje);

/*
 *pre: Recibe un vector de ingredientes cargado con su tope definido y el personaje actual.
 * post: Busca y devuleve la posicion del ingrediente que el personaje tiene en la mano.
 */
int posicion_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, personaje_t personaje);
/*
 *pre: Recibe el estado de un ingrediente (cocinado o cortado).
 * post: en caso que este (cortado o cocinado) devuelve true y en caso contrario false.
 */
bool estado( bool estado_ingrediente);


/*
 *pre:Recibe un numero.
 * post:Devuelve el valor absoluto si es negativo le cambia el signo o caso contrario devuelve ese mismo numero.
 */
int valor_absoluto(int numero);

/*
 *pre: Recibe dos coordenadas de fila y columna definidas.
 * post:Calcula la distancia manhatan de la primera coordeana con la segunda.
 */
int distancia_manhattan(int primera_fila,int primera_columna, int segunda_fila, int segunda_columna);


/*
 *pre: Recibe un vector de objetos cargado con su tope definido y el personaje actual.
 * post:busca la posicion en el vector de objetos de lo que este pisando el personaje.
 */
int posicion_buscada(objeto_t objetos[MAX_OBJETOS], int tope_objetos, personaje_t personaje);
/*
 *pre: Recibe un vector de ingredientes cargado con su tope definido y la coordenada de la mesa.
 * post:Verifica si hay algun ingredinete en la mea devolviendo true o false en caso contrario.
 */
bool esta_mesa_vacia(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, coordenada_t mesa);

/*
 *pre: Recibe un vector de ingredientes cargado con su tope una fila y una columna.
 * post:Devuelve true si las coordenas coiciden o false caso contrario.
 */
int posicion(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, int fil, int col);

/*
 *pre: Recibe un tipo de ingrediente valido (T,L,I,N,J,Q,O o B).
 * post: Dbuelve true si el ingredientes es (O,I o B).
 */
bool es_ingrediente_para_cocinar(char ingrediente);
/*
 *pre:  Recibe un tipo de ingrediente valido (T,L,I,N,J,Q,O o B).
 * post: Devuelve true si el ingredientes es (T,L,M,N,J o Q).
 */
bool ingrediente_es_para_cortar(char ingrediente);

/*
 *pre: Recibe un vector de ingredientes cargado con una posicion.
 * post: devuelve true si los ingredientes (O,I o B) estas cocinado o (T,L,M,N,J o Q). estan cortados.
 */
bool esta_procesado(ingrediente_t ingrediente[MAX_INGREDIENTES], int pos_ingrediente);

/*
 *pre: Recibe el juego.
 * post: Verifica si segun el precio recibido y la comida actual los ingredientes fueron entregados y si es el caso devuelve true o false caso contarrio.
 */
bool es_juego_ganado(juego_t juego);
/*
 *pre: Recibe el objeto que tiene el perosnje en la mano y un string vacio.
 * post:Segun el tipo de objeto que tenga el perosnje en la mano carga el string con el nombre de ese objeto.
 */
void tipo_objeto(char objeto_en_mano, char objeto[MAX_NOMBRE]);
/*
 *pre: Recibe el tipo de comida actual y un vector stribg vacio.
 * post:segun el tipo de comida recibida carga el stribg con su nombre.
 */
void tipo_comida(char tipo, char comida[MAX_NOMBRE]);
/*
 *pre: recibe el personaje actual y un string vacio.
 * post:carga el string con el nombre del perosonaje actual.
 */
void jugador(char personaje_actual, char nombre[MAX_NOMBRE]);
/*
 *pre: Recibe el juego y una variable para cargar.
 * post: Pide al usuario un movimiento y verifica que sea valido o vuelve a preguntar ,muetra informacion al usuario sobre el juego.
 */
void pedir_movimientos(char* movimiento, juego_t* juego);

#endif /* __RESTAURANTE_H__ */