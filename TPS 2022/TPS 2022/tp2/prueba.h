#ifndef __PRUEBA_H_
#define __PRUEBA_H_
#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include<time.h>
#include "kronos.h"

/*
 *pre_condiciones : Recibe la posicion de las pinzas , un robot y sus lasers.
 *post_condiciones :Comparara si estos se pisaron devolviendo true en caso afirmativo y false en caso contrario.
 */
bool pinzas_pisan_robot(juego_t juego,int posicion_actual,int cuadrante);
/*
 *
 *pre_condiciones : Recibe una posicion de la pinza y los lasers.
 *post_condiciones : Devuelve true si coinciden y false caso contrario.
 * 
 */
bool pinzas_pisan_laser(juego_t juego,int posicion_actual,int cuadrante);
/*
 *
 *pre_condiciones : Recibe la posicion de un traje y un robot con sus lasers.
 *post_condiciones : Comparara si estos se pisaron devolviendo true en caso afirmativo y false en caso contrario.
 * 
 */
bool trajes_pisan_robot(juego_t juego,int posicion_actual,int cuadrante);
/*
 *pre_condiciones :Recibe la posicion de un traje y de las pinzas de su cuadrante.   
 *post_condiciones : Comparara si estos se pisaron devolviendo true en caso afirmativo y false en caso contrario. 
 */
bool trajes_pisan_pinzas( juego_t juego,int posicion_actual);

/*
 *pre_condiciones : Recibe la posicion de personaje y un robot con sus lasers.
 *post_condiciones : Comparara si estos se pisaron devolviendo true en caso afirmativo y false en caso contrario. 
 */
bool personaje_pisa_robot(juego_t juego,int personaje_actual,int cuadrante);
/*
 *pre_condiciones : Recibe la posicion de un personaje y las pinzas de su cuadrante.
 *post_condiciones : Comparara si estos se pisaron devolviendo true en caso afirmativo y false en caso contrario.
 */
bool personaje_pisa_pinzas(juego_t juego ,int personaje_actual);

/*
 *pre_condiciones : Rrecibe la posicion de un personaje y su traje.
 *post_condiciones : Comparara si estos se pisaron devolviendo true en caso afirmativo y false en caso contrario. 
 */
bool personaje_pisa_traje(juego_t juego, int personaje_actual);
/*
 * pre-condiciones: Recibe las posiciones de los lasers y los robots. 
 * post-cndiciones: Rverifica si las posiciones coinciden devolviendo true si es asi o false en caso contrario.
 */
bool laser_pisa_robot(juego_t juego ,int posicion_actual,int posicion);

/*
 *pre_condiciones : Recibe dos laser cargados.
 *post_condiciones :Rota los lasers 45 grados en sentido horario en el primer patron de rotacion.
 */
void primera_rotacion(juego_t* juego ,int personaje_actual);
/*
 *
 *pre_condiciones : Recibe los lasers cargados.
 *post_condiciones : Rota los lasers 45 grados en el segundo patron de rotacion.
 * 
 */
void segunda_rotacion(juego_t* juego ,int personaje_actual);
/*
 *pre_condiciones : Recibe los lasers cargados.
 *post_condiciones : Rota los lasers 45 grados en el tercer patron de rotacion.
 */

void tercera_rotacion(juego_t* juego ,int personaje_actual);
/*
 *pre_condiciones :Recibe los lasers cargados.
 *post_condiciones : Rota los losers 45 grado en el cuarto patro de rotacion.
 */
void cuarta_rotacion(juego_t* juego ,int personaje_actual);

/*
 * pre-condiciones:
 * post-condiciones: Verifica si el personaje actual piso algun robot o laser y si es asi, resta todods sus movimientos a 0.
 */
bool choco_con_robots(juego_t juego ,int personaje_actual);   
/*
 *pre-condiciones: Recibe las posiciones del personaje actual y del siguiente familiar.
 *post-condiciones: Verifica si sus posiciones coinciden ,si es ese el caso devuelve true caso contrario false.
 */
bool encontro_al_familiar(juego_t juego,int personaje_actual);

/*
 *pre-condiciones: Recibe un movimiento (A,W,,S,D o C) y el personaje que este jugando. 
 * pos-condiciones: Resta movimientos al personaje menos si la movimiento es C a exepcion del caso en el que el personaje sea Dash, Tambien se fija si se encontro un robot o
 *                  laser en ese caso resta todos los movimientos: 
 */
void restar_movimientos(juego_t* juego,char movimiento,int personaje_actual);
/*
 *pre-condiciones: Recibe llamadas a patrones de rotacion. 
 * pos-condiciones: Rota todo los laser de los 4 cuadrantes 45 grados .
 */
void primer_orden_de_rotacion(juego_t* juego);
/*
 *pre-condiciones: Recibe llamadas a patrones de rotacion. 
 * pos-condiciones: Rota todo los laser de los 4 cuadrantes 45 grados .
 */
void segundo_orden_de_rotacion(juego_t* juego);
/*
 *pre-condiciones: Recibe llamadas a patrones de rotacion. 
 * pos-condiciones: Rota todo los laser de los 4 cuadrantes 45 grados .
 */
void tercer_orden_de_rotacion(juego_t* juego);
/*
 *pre-condiciones: Recibe llamadas a patrones de rotacion. 
 * pos-condiciones: Rota todo los laser de los 4 cuadrantes 45 grados .
 */
void cuarto_orden_de_rotacion(juego_t* juego);




#endif /*_PRUEBA_H_ */