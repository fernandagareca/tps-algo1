#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include<time.h>
#include "kronos.h"
#include "prueba.h"
#define VACIO ' '
#define SALIDA 'S'
#define ROBOTS 'R'
#define LASER 'L'
#define PINZAS 'P'
#define TRAJE 'T'
#define ELASTIGERD 'E'
#define VIOLETA 'V'
#define DASH 'D'
#define MR_INCREIBLE 'I'
#define LONGITUD_MAXIMA_LASER 5
#define LONGITUD_MINIMA_LASER 3
#define LIMITE_CUADRANTE 10
#define ARRIBA  'W'
#define ABAJO 'S'
#define DERECHA  'D'
#define IZQUIERDA 'A'
#define MOVIMIENTO_CON_PODER 'C'
#define POS_ELASTIGER 0
#define POS_VIOLETA 1
#define POS_DASH 3
#define POS_INCREIBLE 4
#define MAX_FILAS 20
#define MAX_COLUMNAS 20


bool pinzas_pisan_robot(juego_t juego,int posicion_actual,int cuadrante){
    bool pisa_robot=false;
    bool pisa_laser=false;
    if(juego.pinzas[posicion_actual].fila == juego.robots[cuadrante].posicion.fila &&
        juego.pinzas[posicion_actual].columna == juego.robots[cuadrante].posicion.columna){
            pisa_robot = true;
        }
    for (int i = 0; i < juego.tope_pinzas; i++){
        if(juego.pinzas[posicion_actual].fila == juego.robots[cuadrante].lasers[i].fila &&
        juego.pinzas[posicion_actual].columna ==juego.robots[cuadrante].lasers[i].columna){
            pisa_laser= true;
        }
    }
    if(pisa_robot == true || pisa_laser== true){
        return true;
    }
    return false;
}

bool pinzas_pisan_laser(juego_t juego,int posicion_actual,int cuadrante){ 
    for( int i=0 ;i < juego.tope_pinzas; i++){
        if(juego.pinzas[posicion_actual].fila == juego.robots[cuadrante].lasers[i].fila &&
            juego.pinzas[posicion_actual].columna== juego.robots[cuadrante].lasers[i].columna){
            return true;  
        }
    } 
    return false;
}
bool trajes_pisan_robot(juego_t juego,int posicion_actual,int cuadrante){
    bool pisa_robot= false;
    bool pisa_laser=false;
    if(juego.supertrajes[posicion_actual].posicion.fila == juego.robots[cuadrante].posicion.fila &&
        juego.supertrajes[posicion_actual].posicion.columna== juego.robots[cuadrante].posicion.columna){
            pisa_robot= true;
        }
    for (int i = 0; i < juego.robots[posicion_actual].tope_lasers; i++){
        if(juego.supertrajes[posicion_actual].posicion.fila == juego.robots[cuadrante].lasers[i].fila &&
        juego.supertrajes[posicion_actual].posicion.columna ==juego.robots[cuadrante].lasers[i].columna){
            pisa_laser= true;
        }
    }
    if(pisa_robot==true || pisa_laser== true){
        return true;
    }
    return false;
}
bool trajes_pisan_pinzas( juego_t juego,int posicion_actual){
    for (int i = 0; i < juego.tope_pinzas; i++){
        if(juego.supertrajes[posicion_actual].posicion.fila == juego.pinzas[i].fila &&
        juego.supertrajes[posicion_actual].posicion.columna ==juego.pinzas[i].columna){
            return true;
        }
    }
    return false;
}
bool personaje_pisa_robot(juego_t juego,int personaje_actual,int cuadrante){
    bool pisa_robot=false;
    bool pisa_laser=false;
    if(juego.personajes[personaje_actual].posicion.fila == juego.robots[cuadrante].posicion.fila &&
        juego.personajes[personaje_actual].posicion.columna == juego.robots[cuadrante].posicion.columna){
            pisa_robot= true;
        }
    for (int i = 0; i < juego.robots[personaje_actual].tope_lasers; i++){
        if(juego.personajes[personaje_actual].posicion.fila == juego.robots[cuadrante].lasers[i].fila &&
        juego.personajes[personaje_actual].posicion.columna ==juego.robots[cuadrante].lasers[i].columna){
            pisa_laser= true;
        }
    }
    if(pisa_robot== true || pisa_laser== true){
        return true;
    }
    return false;
}
bool personaje_pisa_pinzas(juego_t juego ,int personaje_actual){
    for (int i = 0; i < juego.tope_pinzas; i++){
        if(juego.personajes[personaje_actual].posicion.fila == juego.pinzas[i].fila &&
        juego.personajes[personaje_actual].posicion.columna ==juego.pinzas[i].columna){
            return true;
        }
    }
    return false;

}
bool personaje_pisa_traje(juego_t juego, int personaje_actual){
    if(juego.personajes[personaje_actual].posicion.fila == juego.supertrajes[personaje_actual].posicion.fila && 
        juego.personajes[personaje_actual].posicion.columna == juego.supertrajes[personaje_actual].posicion.columna){
            return true;
        }
    return false;
}
bool laser_pisa_robot(juego_t juego ,int posicion_actual,int posicion){
    for (int i = 0; i < juego.tope_robots; i++){
        if(juego.robots[posicion_actual].lasers[posicion].fila == juego.robots[i].posicion.fila &&
            juego.robots[posicion_actual].lasers[posicion].columna == juego.robots[i].posicion.columna){
            return true;
        }
    }
    return false;
}
void primera_rotacion(juego_t* juego ,int personaje_actual){
    int contador=0;
    for (int i = 0; i < juego->longitud_laser; i++){
        contador++;
        juego->robots[personaje_actual].lasers[i].fila += contador;
        juego->robots[personaje_actual].lasers[i].columna = juego->robots[personaje_actual].lasers[i].columna;
    }
    contador=0;
    for (int j = juego->longitud_laser; j < juego->robots[personaje_actual].tope_lasers ; j++){
        contador++;
        juego->robots[personaje_actual].lasers[j].fila = juego->robots[personaje_actual].lasers[j].fila;
        juego->robots[personaje_actual].lasers[j].columna -= contador;    
    }
}

void segunda_rotacion(juego_t* juego ,int personaje_actual){
    int contador=0;
    for (int i = 0; i < juego->longitud_laser; i++){
        contador++;
        juego->robots[personaje_actual].lasers[i].fila =juego->robots[personaje_actual].lasers[i].fila;
        juego->robots[personaje_actual].lasers[i].columna -= contador;     
    }
    contador=0;
    for(int j = juego->longitud_laser; j < juego->robots[personaje_actual].tope_lasers ; j++){
        contador++;
        juego->robots[personaje_actual].lasers[j].fila -= contador;
        juego->robots[personaje_actual].lasers[j].columna=juego->robots[personaje_actual].lasers[j].columna;    
    } 
}
void tercera_rotacion(juego_t* juego ,int personaje_actual){
    int contador=0;
    for (int i = 0; i < juego->longitud_laser; i++){
        contador++;
        juego->robots[personaje_actual].lasers[i].fila -= contador;
        juego->robots[personaje_actual].lasers[i].columna = juego->robots[personaje_actual].lasers[i].columna;  
    }
    contador=0;
    for (int j = juego->longitud_laser; j < juego->robots[personaje_actual].tope_lasers ; j++){
        contador++;
        juego->robots[personaje_actual].lasers[j].fila = juego->robots[personaje_actual].lasers[j].fila;
        juego->robots[personaje_actual].lasers[j].columna += contador;      
    }
}
void cuarta_rotacion(juego_t* juego ,int personaje_actual){
    int contador=0;
    for (int i = 0; i < juego->longitud_laser; i++){
        contador++;
        juego->robots[personaje_actual].lasers[i].fila = juego->robots[personaje_actual].lasers[i].fila;
        juego->robots[personaje_actual].lasers[i].columna += contador;   
    }
    contador=0;
    for (int j = juego->longitud_laser; j < juego->robots[personaje_actual].tope_lasers ; j++){
        contador++;
        juego->robots[personaje_actual].lasers[j].fila += contador;
        juego->robots[personaje_actual].lasers[j].columna = juego->robots[personaje_actual].lasers[j].columna;  
    }
}
bool choco_con_robots(juego_t juego ,int personaje_actual){
    if(personaje_pisa_robot(juego,personaje_actual,0) || personaje_pisa_robot(juego,personaje_actual,1) || personaje_pisa_robot(juego,personaje_actual,2) ||
        personaje_pisa_robot(juego,personaje_actual,3)){ 
        return true;
    }
    return false;
} 
bool encontro_al_familiar(juego_t juego, int personaje_actual){
    if(juego.personajes[personaje_actual].posicion.fila == juego.personajes[personaje_actual +1].posicion.fila &&
        juego.personajes[personaje_actual].posicion.columna == juego.personajes[personaje_actual +1].posicion.columna ){
            return true;
        }
        return false;
}
void restar_movimientos(juego_t* juego,char movimiento,int personaje_actual){
    if(movimiento == ARRIBA || movimiento == ABAJO || movimiento== DERECHA || movimiento == IZQUIERDA ){
        juego->personajes[personaje_actual].movimientos--;
            printf("movimientos %i\n",  juego->personajes[personaje_actual].movimientos);
    }else if(movimiento == MOVIMIENTO_CON_PODER && juego->id_personaje_actual== 3 && juego->supertrajes[POS_DASH].usado== false){
        juego->personajes[personaje_actual].movimientos--;
            printf("movimientos %i\n",  juego->personajes[personaje_actual].movimientos);

    }

    if(choco_con_robots(*juego,personaje_actual) && juego->personajes[POS_VIOLETA].poder_activado== false){
        juego->personajes[personaje_actual].movimientos=0;
    }
}
void primer_orden_de_rotacion(juego_t* juego){
   
    printf("estado %i\n",estado_juego(*juego));
    primera_rotacion(juego,0);
    tercera_rotacion(juego,1);
    cuarta_rotacion(juego,2);
    segunda_rotacion(juego,3); 
}
void segundo_orden_de_rotacion(juego_t* juego){
   
    printf("estado %i\n",estado_juego(*juego));
    segunda_rotacion(juego,0);
    cuarta_rotacion(juego,1);
    primera_rotacion(juego,2);
    tercera_rotacion(juego,3);
}
void tercer_orden_de_rotacion(juego_t* juego){
   
    printf("estado %i\n",estado_juego(*juego));
    tercera_rotacion(juego,0);
    primera_rotacion(juego,1);
    segunda_rotacion(juego,2);
    cuarta_rotacion(juego,3);   
}   
void cuarto_orden_de_rotacion(juego_t* juego){ 
   
    printf("estado %i\n",estado_juego(*juego));
    cuarta_rotacion(juego,0);
    segunda_rotacion(juego,1);
    tercera_rotacion(juego,2);
    primera_rotacion(juego,3);   
}