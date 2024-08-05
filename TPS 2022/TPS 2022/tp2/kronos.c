#include<stdio.h>
#include"kronos.h"
#include<stdbool.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#include "increidle.h"
#include "prueba.h"

#define MAX_CONTRASENIA 6
#define MAX_FILAS 20
#define MAX_COLUMNAS 20
const char VACIO=' ';
const char SALIDA='S';
const char ROBOTS='R';
const char LASER='L';
const char PINZAS='P';
const char TRAJE='T';
const char ELASTIGERD='E';
const char VIOLETA='V';
const char DASH='D';
const char MR_INCREIBLE='I';
const char LONGITUD_MAXIMA_LASER=5;
const char LONGITUD_MINIMA_LASER=3;
const int LIMITE_CUADRANTE=10;
const char ARRIBA ='W';
const char ABAJO='S';
const char DERECHA ='D';
const char IZQUIERDA='A';
const char MOVIMIENTOS_CON_PODER= 'C';
const int CUADRANTE_ELASTIGER=0;
const int CUADRANTE_VIOLETA=1;
const int CUADRANTE_DASH=2;
const int CUADRANTE_INCREIBLE=3;
const int POS_ELASTIGER=0;
const int POS_VIOLETA=1;
const int POS_DASH=2;
const int POS_INCREIBLE=3;
const int FILA_GANADORA=0;
const int COLUMNA_GANADORA=19;
const int PINZAS_DEL_PRIMER_CUADRANTE=4;
const int PINZAS_DEL_SEGUNDO_CUADRANTE=8;
const int PINZAS_DEL_TERCER_CUADRANTE=12;
const int PINZAS_DEL_CUARTO_CUADRANTE=16;
 
/*
 *pre-condiciones: 
 * post-condiciones: carga la matriz de espacio vacio.
 */
void rellenar_matriz( char ciudad[MAX_FILAS][MAX_COLUMNAS]){
    for(int  i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){
        ciudad[i][j]= VACIO;
        }
    }
}

/*
 *pre_condiciones : Recibe la verificacion de la contraseña recibida.
 *post_condiciones : Asigna un valor a la longitud del laser dependiendo de la validez de la contraseña.
 */
int calcular_longitud_laser(juego_t* juego ,bool contrasenia_completa){
    if(contrasenia_completa == true){
        juego->longitud_laser= LONGITUD_MINIMA_LASER;
    }else{
        juego->longitud_laser=LONGITUD_MAXIMA_LASER;
    }
    return juego->longitud_laser;
}
/*
 *pre-condiciones: Recibe el vector de robots. 
 * pos-condiciones: Posiciona al los 4 robots en sus cuadrantes ,verificando que no se pasen los limites.
 */
void cargar_robots(juego_t* juego){
    juego->robots[CUADRANTE_ELASTIGER].posicion.fila= rand() % 10;
    juego->robots[CUADRANTE_ELASTIGER].posicion.columna=  rand() % 10;

    juego->robots[CUADRANTE_VIOLETA].posicion.fila=   rand() % 20 +10 ;
    juego->robots[CUADRANTE_VIOLETA].posicion.columna=  rand() % 20 +10 ;
    while ( juego->robots[CUADRANTE_VIOLETA].posicion.fila >= MAX_FILAS ||  juego->robots[CUADRANTE_VIOLETA].posicion.columna >= MAX_COLUMNAS){
        juego->robots[CUADRANTE_VIOLETA].posicion.fila= rand() % 20 + 10;
        juego->robots[CUADRANTE_VIOLETA].posicion.columna= rand() % 20 + 10;
    } 

    juego->robots[CUADRANTE_DASH].posicion.fila= rand()  % 20 +10;
    juego->robots[CUADRANTE_DASH].posicion.columna= rand() % 10;
    while (juego->robots[CUADRANTE_DASH].posicion.fila >= MAX_FILAS ){
        juego->robots[CUADRANTE_DASH].posicion.fila= rand() % 20 + 10;
    }       

    juego->robots[CUADRANTE_INCREIBLE].posicion.fila= rand() % 10;
    juego->robots[CUADRANTE_INCREIBLE].posicion.columna= rand() % 20 + 10;
    while (juego->robots[CUADRANTE_INCREIBLE].posicion.columna >= MAX_COLUMNAS ){
        juego->robots[CUADRANTE_INCREIBLE].posicion.columna= rand() % 20 + 10;
    }      

}
/*
 *pre_condiciones : Recibe un robot .
 *post_condiciones : Icicializa al robot del primer cuadrante con sus dos lasers.
 */
void cargar_laser_primer_cuadrante( juego_t* juego,int robot_actual){

    int contador=0;
    for (int i = 0; i < juego->longitud_laser; i++){
        contador++;
        juego->robots[robot_actual].lasers[i].fila =juego->robots[robot_actual].posicion.fila ;
        juego->robots[robot_actual].lasers[i].columna = juego->robots[robot_actual].posicion.columna + contador;  
    }
    contador=0;
    for (int j = juego->longitud_laser; j < juego->robots[robot_actual].tope_lasers; j++){
        contador++;
        juego->robots[robot_actual].lasers[j].columna =  juego->robots[robot_actual].posicion.columna ;
        juego->robots[robot_actual].lasers[j].fila =  juego->robots[robot_actual].posicion.fila + contador;
    }
}
/*
 *pre_condiciones : Recibe un robot .
 *post_condiciones : Icicializa al robot del segundo cuadrante con sus dos lasers.
 */
void cargar_laser_segundo_cuadrante( juego_t* juego,int robot_actual){   
    
    int contador=0;
    for (int i = 0; i < juego->longitud_laser; i++){
        contador++;
            juego->robots[robot_actual].lasers[i].fila = juego->robots[robot_actual].posicion.fila ;
            juego->robots[robot_actual].lasers[i].columna = juego->robots[robot_actual].posicion.columna - contador;  
    }
    contador=0;
    for (int j = juego->longitud_laser; j < juego->robots[robot_actual].tope_lasers; j++){
            contador++;
            juego->robots[robot_actual].lasers[j].fila =  juego->robots[robot_actual].posicion.fila - contador;
            juego->robots[robot_actual].lasers[j].columna =  juego->robots[robot_actual].posicion.columna;
    }
}
/*
 *pre_condiciones : Recibe un robot .
 *post_condiciones : Icicializa al robot del tercer cuadrante con sus dos lasers.
 */
void cargar_laser_tercer_cuadrante( juego_t* juego,int robot_actual){ 
    
    int contador=0;
    for (int i = 0; i < juego->longitud_laser; i++){
        contador++;
            juego->robots[robot_actual].lasers[i].fila = juego->robots[robot_actual].posicion.fila - contador ;
            juego->robots[robot_actual].lasers[i].columna = juego->robots[robot_actual].posicion.columna ;
    }
    contador=0;
    for (int j = juego->longitud_laser; j < juego->robots[robot_actual].tope_lasers; j++){
            contador++;
            juego->robots[robot_actual].lasers[j].columna =  juego->robots[robot_actual].posicion.columna + contador;
            juego->robots[robot_actual].lasers[j].fila =  juego->robots[robot_actual].posicion.fila ;
    }
}
/*
 *pre_condiciones : Recibe un robot .
 *post_condiciones : Icicializa al robot del cuarto cuadrante con sus dos lasers.
 */
void cargar_laser_cuarto_cuadrante( juego_t* juego,int robot_actual){
    
    int contador=0;
    for (int i = 0; i < juego->longitud_laser; i++){
        contador++;
            juego->robots[robot_actual].lasers[i].fila = juego->robots[robot_actual].posicion.fila + contador;
            juego->robots[robot_actual].lasers[i].columna = juego->robots[robot_actual].posicion.columna ;   
    }
    contador=0;
    for (int j = juego->longitud_laser; j < juego->robots[robot_actual].tope_lasers; j++){
            contador++;
            juego->robots[robot_actual].lasers[j].fila =  juego->robots[robot_actual].posicion.fila ;
            juego->robots[robot_actual].lasers[j].columna =  juego->robots[robot_actual].posicion.columna - contador;    
    }
}
/*
 *pre_condiciones : Recibe el vector de pinzas y su tope.
 *post_condiciones : Carga el vector de pinzas en sus correspondientes cuadrantes retringiendolos.
 */
void cargar_pinzas(juego_t* juego){
    for (int i = 0; i <juego->tope_pinzas; i++){
        if(i< PINZAS_DEL_PRIMER_CUADRANTE){
            juego->pinzas[i].fila= rand() % 10;
            juego->pinzas[i].columna= rand() % 10;
            while((juego->pinzas[i].fila ==  juego->pinzas[i-1].fila && juego->pinzas[i].columna ==  juego->pinzas[i-1].columna) || pinzas_pisan_robot(*juego,i,0) || pinzas_pisan_robot(*juego,i,2)  ||
                    pinzas_pisan_robot(*juego,i,3)){
                juego->pinzas[i].fila= rand() % 10 ;
                juego->pinzas[i].columna= rand() % 10 ;
            }
        }else if(i < PINZAS_DEL_SEGUNDO_CUADRANTE){
            juego->pinzas[i].fila= rand() % 20 ;
            juego->pinzas[i].columna= rand() % 20 ;
            while(juego->pinzas[i].fila < LIMITE_CUADRANTE || juego->pinzas[i].columna < LIMITE_CUADRANTE   || pinzas_pisan_robot(*juego,i,1) || pinzas_pisan_robot(*juego,i,2) ||
                pinzas_pisan_robot(*juego,i,3)){
                juego->pinzas[i].fila= rand() % 20 ;
                juego->pinzas[i].columna= rand() % 20 ;
            }
        }else if(i < PINZAS_DEL_TERCER_CUADRANTE){ 
            juego->pinzas[i].fila= rand() % 20 ;
            juego->pinzas[i].columna= rand() % 20 ;
            while(juego->pinzas[i].fila < LIMITE_CUADRANTE ||juego->pinzas[i].columna >= LIMITE_CUADRANTE || pinzas_pisan_robot(*juego,i,2) || pinzas_pisan_robot(*juego,i,0) ||
                pinzas_pisan_robot(*juego,i,1)){
                juego->pinzas[i].fila= rand() % 20 ;
                juego->pinzas[i].columna= rand() % 20;
            }    
        }else if(i< PINZAS_DEL_CUARTO_CUADRANTE){
            juego->pinzas[i].fila= rand() % 20 ;
            juego->pinzas[i].columna= rand() % 20 ;
            while(juego->pinzas[i].fila >= LIMITE_CUADRANTE ||juego->pinzas[i].columna < LIMITE_CUADRANTE  || pinzas_pisan_robot(*juego,i,3) || pinzas_pisan_robot(*juego,i,0)  ||
                pinzas_pisan_robot(*juego,i,1) ){
                juego->pinzas[i].fila= rand() % 20 ;
                juego->pinzas[i].columna= rand() % 20 ;
            }
        }
        while(juego->pinzas[i].fila == juego->pinzas[i-1].fila && juego->pinzas[i].columna ==  juego->pinzas[i-1].columna){
            juego->pinzas[i].fila= rand() % 20 ;
            juego->pinzas[i].columna= rand() % 20 ;
        }
    }  
}
/*
 *pre_condiciones : Recibe el vector de trajes y su tope.
 *post_condiciones : Carga el vector trajes y les asigna posiciones en sus respectivos cuadrantes restringiendolos.
 */
void cargar_supertrajes(juego_t* juego){
        
    juego->supertrajes[POS_ELASTIGER].posicion.fila= rand() % 10;
    juego->supertrajes[POS_ELASTIGER].posicion.columna= rand() % 10;
    while (trajes_pisan_robot(*juego,0,0) || trajes_pisan_robot(*juego,0,2) || trajes_pisan_robot(*juego,0,3) || trajes_pisan_pinzas(*juego,0)){
        juego->supertrajes[POS_ELASTIGER].posicion.fila= rand() % 10;
        juego->supertrajes[POS_ELASTIGER].posicion.columna= rand() % 10;
    } 
    
    juego->supertrajes[POS_VIOLETA].posicion.fila= rand() % 20;
    juego->supertrajes[POS_VIOLETA].posicion.columna= rand() % 20;
    while (juego->supertrajes[POS_VIOLETA].posicion.fila < LIMITE_CUADRANTE ||juego->supertrajes[POS_VIOLETA].posicion.columna < LIMITE_CUADRANTE || trajes_pisan_robot(*juego,1,1)  || 
            trajes_pisan_robot(*juego,1,2) || trajes_pisan_robot(*juego,1,3) || trajes_pisan_pinzas(*juego,1)){
        juego->supertrajes[POS_VIOLETA].posicion.fila= rand() % 20;
        juego->supertrajes[POS_VIOLETA].posicion.columna= rand() % 20;
    }
    
    juego->supertrajes[POS_DASH].posicion.fila= rand() % 20;
    juego->supertrajes[POS_DASH].posicion.columna= rand() % 20;
    while (juego->supertrajes[POS_DASH].posicion.fila < LIMITE_CUADRANTE  ||juego->supertrajes[POS_DASH].posicion.columna >= LIMITE_CUADRANTE || trajes_pisan_robot(*juego,2,2)  || 
            trajes_pisan_robot(*juego,2,0)  ||  trajes_pisan_robot(*juego,2,1) || trajes_pisan_pinzas(*juego,2)){
        juego->supertrajes[POS_DASH].posicion.fila= rand() % 20;
        juego->supertrajes[POS_DASH].posicion.columna= rand() % 20;
    }
    
    juego->supertrajes[POS_INCREIBLE].posicion.fila= rand() % 20;
    juego->supertrajes[POS_INCREIBLE].posicion.columna= rand() % 20;
    while (juego->supertrajes[POS_INCREIBLE].posicion.fila >= LIMITE_CUADRANTE  || juego->supertrajes[POS_INCREIBLE].posicion.columna < LIMITE_CUADRANTE || trajes_pisan_pinzas(*juego,3) ||
            trajes_pisan_robot(*juego,3,3) || trajes_pisan_robot(*juego,3,0) ||  trajes_pisan_robot(*juego,3,1) ){
        juego->supertrajes[POS_INCREIBLE].posicion.fila= rand() % 20;
        juego->supertrajes[POS_INCREIBLE].posicion.columna= rand() % 20;
    }
        for (int i = 0; i < juego->tope_supertraje; i++){
            juego->supertrajes[i].cuadrante=i;
            juego->supertrajes[i].recolectado=false;
            juego->supertrajes[i].usado=false;
        }
    
}
/*
 *pre_condiciones : Recibe el juego.
 *post_condiciones : Carga el vector de personajes posicionando a los personajes en sus respectivos cuadrantes restringiendolos.
 */
void posicionar_personajes(juego_t* juego){
            juego->personajes[POS_ELASTIGER].posicion.fila= rand() % 10 ;
            juego->personajes[POS_ELASTIGER].posicion.columna= rand() % 10;
            juego->personajes[POS_ELASTIGER].movimientos=25;
            juego->personajes[POS_ELASTIGER].movimientos_con_poder=5;
            while(personaje_pisa_robot(*juego,0,0) || personaje_pisa_robot(*juego,0,2)  ||personaje_pisa_robot(*juego,0,3) || personaje_pisa_traje(*juego,0) || personaje_pisa_pinzas(*juego,0)){
                juego->personajes[POS_ELASTIGER].posicion.fila= rand() % 10 ;
                juego->personajes[POS_ELASTIGER].posicion.columna= rand() % 10;
            }
        
                juego->personajes[POS_VIOLETA].posicion.fila= rand() % 20;
                juego->personajes[POS_VIOLETA].posicion.columna= rand() % 20;
                juego->personajes[POS_VIOLETA].movimientos=30;
                juego->personajes[POS_VIOLETA].movimientos_con_poder=5;
            while ( juego->personajes[POS_VIOLETA].posicion.fila < LIMITE_CUADRANTE|| juego->personajes[POS_VIOLETA].posicion.columna < LIMITE_CUADRANTE || personaje_pisa_robot(*juego,1,1) || 
                personaje_pisa_robot(*juego,1,2) || personaje_pisa_robot(*juego,1,3) || personaje_pisa_traje(*juego,1) || personaje_pisa_pinzas(*juego,1)){
                juego->personajes[POS_VIOLETA].posicion.fila= rand() % 20;
                juego->personajes[POS_VIOLETA].posicion.columna= rand() % 20;
            }
        
                juego->personajes[POS_DASH].posicion.fila= rand() % 20;
                juego->personajes[POS_DASH].posicion.columna= rand() % 20;
                juego->personajes[POS_DASH].movimientos=20;
                juego->personajes[POS_DASH].movimientos_con_poder=1;
            while (juego->personajes[POS_DASH].posicion.fila < LIMITE_CUADRANTE|| juego->personajes[POS_DASH].posicion.columna >= LIMITE_CUADRANTE || personaje_pisa_robot(*juego,2,2) || 
            personaje_pisa_robot(*juego,2,0) ||  personaje_pisa_robot(*juego,2,1) || personaje_pisa_traje(*juego,2) || personaje_pisa_pinzas(*juego,2) ){
                juego->personajes[POS_DASH].posicion.fila= rand() % 20;
                juego->personajes[POS_DASH].posicion.columna= rand() % 20;
            }
        
                juego->personajes[POS_INCREIBLE].posicion.fila= rand() % 20;
                juego->personajes[POS_INCREIBLE].posicion.columna= rand() % 20;
                juego->personajes[POS_INCREIBLE].movimientos=15;
                juego->personajes[POS_INCREIBLE].movimientos_con_poder=5;
            while (juego->personajes[POS_INCREIBLE].posicion.fila >= LIMITE_CUADRANTE || juego->personajes[POS_INCREIBLE].posicion.columna < LIMITE_CUADRANTE || personaje_pisa_robot(*juego,3,3) || 
            personaje_pisa_robot(*juego,3,0) ||  personaje_pisa_robot(*juego,3,1) || personaje_pisa_traje(*juego,3) || personaje_pisa_pinzas(*juego,3)){
                juego->personajes[POS_INCREIBLE].posicion.fila= rand() % 20;
                juego->personajes[POS_INCREIBLE].posicion.columna= rand() % 20;
            }
        
        for (int i = 0; i < juego->tope_personajes; i++){
            juego->personajes[i].poder_activado=false;
            juego->personajes[i].tiene_supertraje=false;
            juego->personajes[i].cuadrante_inicial=i;
        }
    
}   

void inicializar_juego(juego_t* juego, bool contrasenia_completa){
    juego->tope_robots=4;
    juego->tope_personajes=4;
    juego->tope_supertraje=4;
    juego->tope_pinzas=16;
    for (int i = 0; i < juego->tope_robots; i++){
        juego->robots[i].tope_lasers=2*calcular_longitud_laser(juego,contrasenia_completa);
    }
    juego->id_personaje_actual=1;
    cargar_robots(juego);
    cargar_laser_primer_cuadrante(juego,0);
    cargar_laser_segundo_cuadrante(juego,1);
    cargar_laser_tercer_cuadrante(juego,2);
    cargar_laser_cuarto_cuadrante(juego,3);
    cargar_pinzas(juego);
    cargar_supertrajes(juego);
    posicionar_personajes(juego);
}
/*
 *pre_condiciones : Recibe todas las posiciones de los objetos del juego.
 *post_condiciones : Carga todas las posiciones priorizando a los lasers y robots.
 */
void cargar_campo_de_juego(juego_t juego,char ciudad[MAX_FILAS][MAX_COLUMNAS]){ 
    for (int i = 0; i < juego.tope_robots; i++){
        ciudad[juego.robots[i].posicion.fila][juego.robots[i].posicion.columna]= ROBOTS;  
    }
    
    for (int i = 0; i < juego.robots[CUADRANTE_ELASTIGER].tope_lasers; i++){
        if(juego.robots[CUADRANTE_ELASTIGER].lasers[i].fila >=0 && juego.robots[CUADRANTE_ELASTIGER].lasers[i].columna >=0 && !laser_pisa_robot(juego,0,i)){
            ciudad[juego.robots[CUADRANTE_ELASTIGER].lasers[i].fila][juego.robots[CUADRANTE_ELASTIGER].lasers[i].columna]= LASER;
        } 
    }
    for (int i = 0; i < juego.robots[CUADRANTE_VIOLETA].tope_lasers; i++){
        if(juego.robots[CUADRANTE_VIOLETA].lasers[i].fila < MAX_FILAS && juego.robots[CUADRANTE_VIOLETA].lasers[i].columna < MAX_COLUMNAS && !laser_pisa_robot(juego,1,i)){
            ciudad[juego.robots[CUADRANTE_VIOLETA].lasers[i].fila][juego.robots[CUADRANTE_VIOLETA].lasers[i].columna]= LASER;
        }
    }
    for (int i = 0; i < juego.robots[CUADRANTE_DASH].tope_lasers; i++){
        if(juego.robots[CUADRANTE_DASH].lasers[i].fila < MAX_FILAS && juego.robots[CUADRANTE_DASH].lasers[i].columna >=0 && !laser_pisa_robot(juego,2,i)){
            ciudad[juego.robots[CUADRANTE_DASH].lasers[i].fila][juego.robots[CUADRANTE_DASH].lasers[i].columna]= LASER;
        } 
    }
    for (int i = 0; i < juego.robots[CUADRANTE_INCREIBLE].tope_lasers; i++){
        if(juego.robots[CUADRANTE_INCREIBLE].lasers[i].fila >=0  && juego.robots[CUADRANTE_INCREIBLE].lasers[i].columna < MAX_COLUMNAS && !laser_pisa_robot(juego,3,i)){
            ciudad[juego.robots[CUADRANTE_INCREIBLE].lasers[i].fila][juego.robots[CUADRANTE_INCREIBLE].lasers[i].columna]= LASER;
        }
    }
    int personaje_actual=0;
    if(juego.id_personaje_actual == 1){
        personaje_actual= POS_ELASTIGER;
    }else if(juego.id_personaje_actual==2){
        personaje_actual= POS_VIOLETA;
    }else if(juego.id_personaje_actual==3){
        personaje_actual= POS_DASH;
    }else{
        personaje_actual= POS_INCREIBLE;
    }
    for (int i = 0; i < juego.tope_personajes; i++){
        if( !personaje_pisa_robot(juego,i,i) && i >= personaje_actual){
            if (i==0){
                ciudad[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna]= ELASTIGERD;
            }else if(i==1){
                ciudad[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna]= VIOLETA;  
            }else if(i==2){
                ciudad[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna]= DASH;  
            }else{
                ciudad[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna]= MR_INCREIBLE;  
            }
        }    
    }
    for (int i = 0; i < juego.tope_supertraje; i++){
        if(juego.supertrajes[i].recolectado== false && !trajes_pisan_robot(juego,i,i)){
        ciudad[juego.supertrajes[i].posicion.fila][juego.supertrajes[i].posicion.columna]= TRAJE;  
        }
    }  
    for (int i = 0; i < juego.tope_pinzas; i++){
        if(!pinzas_pisan_robot(juego,i,CUADRANTE_ELASTIGER) && !pinzas_pisan_robot(juego,i,CUADRANTE_VIOLETA) && !pinzas_pisan_robot(juego,i,CUADRANTE_DASH) && 
            !pinzas_pisan_robot(juego,i,CUADRANTE_INCREIBLE)){
            ciudad[juego.pinzas[i].fila][juego.pinzas[i].columna]=PINZAS;
        }
    }
}

void imprimir_terreno(juego_t juego){
    char ciudad[MAX_FILAS][MAX_COLUMNAS];
    rellenar_matriz(ciudad);
    cargar_campo_de_juego(juego,ciudad);
    ciudad[0][19]=SALIDA;
    printf("     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14| 15| 16| 17| 18| 19|   |\n");
    for(int  i = 0; i < MAX_FILAS; i++){ 
        if (i<10){
        printf("|  %i |",i);
        }else{
        printf("| %i |",i);
        }
        for (int j = 0; j < MAX_COLUMNAS; j++){
            printf(" %c |", ciudad[i][j]);
        }
        if (i<10){
        printf(" %i  |",i);
        }else{
        printf(" %i |",i);
        }
        printf("\n");
    }
    printf("     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14| 15| 16| 17| 18| 19|   |\n");
} 
/*
 *pre_condiciones : Recibe el movimiento.
 *post_condiciones : Mueve al personaje restringiendolo para que no se salga de la matriz. 
 */
bool restringir_movimientos(juego_t juego, char movimiento,int posicion_actual){
    if(juego.personajes[posicion_actual].posicion.fila ==0 && movimiento == ARRIBA){
        return true;
    }else if(juego.personajes[posicion_actual].posicion.columna ==0 && movimiento == IZQUIERDA){
        return true;
    }else if(juego.personajes[posicion_actual].posicion.fila == 19 && movimiento == ABAJO){
        return true;
    }else if(juego.personajes[posicion_actual].posicion.columna  == 19 && movimiento== DERECHA){
        return true;
    }
    return false;
}
/*
 *pre_condiciones : Recibe el movimiento.
 *post_condiciones : Mueve al personaje.
 */
void mover_personaje(juego_t* juego,char movimiento,int posicion_actual,int sumador){
    if(restringir_movimientos(*juego,movimiento,posicion_actual)){
        printf("NO PUEDES PASAR LOS LIMITES DE LA MATRIZ\n");
        return;
    }
    if(movimiento== ARRIBA){
        juego->personajes[posicion_actual].posicion.fila -= sumador;
        juego->personajes[posicion_actual].posicion.columna= juego->personajes[posicion_actual].posicion.columna;
    }else if(movimiento== ABAJO){
        juego->personajes[posicion_actual].posicion.fila += sumador;
        juego->personajes[posicion_actual].posicion.columna= juego->personajes[posicion_actual].posicion.columna;
    }else if(movimiento == DERECHA){
        juego->personajes[posicion_actual].posicion.fila = juego->personajes[posicion_actual].posicion.fila;
        juego->personajes[posicion_actual].posicion.columna +=sumador;
    }else if(movimiento == IZQUIERDA){
        juego->personajes[posicion_actual].posicion.fila = juego->personajes[posicion_actual].posicion.fila;
        juego->personajes[posicion_actual].posicion.columna -= sumador;
    }else if(movimiento == MOVIMIENTOS_CON_PODER && juego->supertrajes[posicion_actual].usado== false && juego->supertrajes[posicion_actual].recolectado== true){
        printf("ACTIVADO\n");
        juego->personajes[posicion_actual].poder_activado=true;
    }
}
/*
 *pre-condiciones:Recibe el cuadrante del traje y el personaje .
 *post-condiciones: Devuelve true en cas que sean iguales o false en caso contrario. 
 */
void recolectar_traje(juego_t* juego,int personaje_actual){
    
    if( juego->personajes[personaje_actual].cuadrante_inicial == juego->supertrajes[personaje_actual].cuadrante && personaje_pisa_traje(*juego,personaje_actual)){
        juego->supertrajes[personaje_actual].recolectado = true;
        printf("RECOLECTADO\n");
        juego->personajes[personaje_actual].tiene_supertraje=true;
    }
}
/*
 *pre-condiciones:  Recibe la posicion de dash.
 * post-condiciones:traslada a dash a una posicion alertoria dentro del cuadrantte de Mr Increible.
 */
void poder_dash(juego_t* juego){
    juego->personajes[POS_DASH].posicion.fila= rand() % 20;
    juego->personajes[POS_DASH].posicion.columna= rand() % 20;
    while(juego->personajes[POS_DASH].posicion.fila >= LIMITE_CUADRANTE || juego->personajes[POS_DASH].posicion.columna < LIMITE_CUADRANTE ){
        juego->personajes[POS_DASH].posicion.fila= rand() % 20;
        juego->personajes[POS_DASH].posicion.columna= rand() % 20;
    }
}
/*
 *pre-condiciones: Recibe el personaje que esta jugando y la posicion del robot.
 * pos-condiciones: Verifica si la posicion del personaje coincide con la posicion 
 */
bool personaje_tropezo_con_robot(juego_t juego,int personaje_actual){
    if(juego.personajes[personaje_actual].posicion.fila ==  juego.robots[personaje_actual].posicion.fila && 
        juego.personajes[personaje_actual].posicion.columna== juego.robots[personaje_actual].posicion.columna){
            return true;
        }
    return false;
}
bool personaje_pasa_los_limites(juego_t juego, int personaje_actual){
    if(juego.personajes[personaje_actual].posicion.fila < 0 || juego.personajes[personaje_actual].posicion.fila > MAX_FILAS || juego.personajes[personaje_actual].posicion.columna <0 || 
        juego.personajes[personaje_actual].posicion.columna > MAX_COLUMNAS){
        return true;
    }
        return false;
}
/*
 *pre-condiciones: Recibe la posicion del personaje actual.
 *post-condiciones: Verifica si se el personaje pizo la pinza y si ese es el caso lo manda a una posicion alertoria alado del robot de su cuadrante.
 */
void chocar_con_pinzas(juego_t* juego,int personaje_actual){
    if(personaje_pisa_pinzas(*juego,personaje_actual) && juego->personajes[POS_INCREIBLE].poder_activado== false){
        int fila_robot= juego->robots[personaje_actual].posicion.fila  ;
        int coluna_robot= juego->robots[personaje_actual].posicion.columna  ;

        juego->personajes[personaje_actual].posicion.fila=  rand() % (fila_robot +2) ;
        juego->personajes[personaje_actual].posicion.columna= rand() % (coluna_robot +2);
        while(personaje_tropezo_con_robot(*juego,personaje_actual) || personaje_pasa_los_limites(*juego,personaje_actual) ||
                juego->personajes[personaje_actual].posicion.fila < fila_robot -1 ||  juego->personajes[personaje_actual].posicion.columna < coluna_robot -1){

            juego->personajes[personaje_actual].posicion.fila=  rand() % (fila_robot +2) ;
            juego->personajes[personaje_actual].posicion.columna= rand() % (coluna_robot +2);

        }       
    }              
}
/*
 *pre-condiciones:Recibe la posicon de increible. 
 * pos-condiciones:Verifica si llsego a la salida.
 */
bool gano(juego_t juego){
    if(juego.personajes[POS_INCREIBLE].posicion.fila== FILA_GANADORA && juego.personajes[POS_INCREIBLE].posicion.columna== COLUMNA_GANADORA){
        return true;
    }
    return false;
}

void realizar_jugada(juego_t* juego, char movimiento){
    
    if (juego->id_personaje_actual== 1){  
        if(juego->personajes[POS_ELASTIGER].poder_activado == true){
            mover_personaje(juego,movimiento,POS_ELASTIGER,3);
            chocar_con_pinzas(juego,POS_ELASTIGER);
            restar_movimientos(juego,movimiento,POS_ELASTIGER);
            juego->personajes[POS_ELASTIGER].movimientos_con_poder--;
            if(juego->personajes[POS_ELASTIGER].movimientos_con_poder==0){
                juego->personajes[POS_ELASTIGER].poder_activado=false;
                juego->personajes[POS_ELASTIGER].tiene_supertraje= false;
                juego->supertrajes[POS_ELASTIGER].usado=true;
            }    
        }else{
            mover_personaje(juego,movimiento,POS_ELASTIGER,1);
            recolectar_traje(juego,POS_ELASTIGER);
            chocar_con_pinzas(juego,POS_ELASTIGER);
            restar_movimientos(juego,movimiento,POS_ELASTIGER);
            if(encontro_al_familiar(*juego,POS_ELASTIGER)){
                juego->id_personaje_actual=2;
            }    
        
        }
    }else if(juego->id_personaje_actual== 2){

        if(juego->personajes[POS_VIOLETA].poder_activado == true){
            mover_personaje(juego,movimiento,POS_VIOLETA,1);
            chocar_con_pinzas(juego,POS_VIOLETA);
            restar_movimientos(juego,movimiento,POS_VIOLETA);
            juego->personajes[POS_VIOLETA].movimientos_con_poder--;
            if(juego->personajes[POS_VIOLETA].movimientos_con_poder==0){
                juego->personajes[POS_VIOLETA].poder_activado=false;
                juego->personajes[POS_VIOLETA].tiene_supertraje= false;
                juego->supertrajes[POS_VIOLETA].usado=true;
            }    
        }else{
            mover_personaje(juego,movimiento,POS_VIOLETA,1);
            recolectar_traje(juego,POS_VIOLETA);
            chocar_con_pinzas(juego,POS_VIOLETA);
            restar_movimientos(juego,movimiento,POS_VIOLETA);
            if(encontro_al_familiar(*juego,POS_VIOLETA)){
                juego->id_personaje_actual=3;
            }    
        }
    }else if(juego->id_personaje_actual==  3){

        mover_personaje(juego,movimiento,POS_DASH,1);
        recolectar_traje(juego,POS_DASH);
        chocar_con_pinzas(juego,POS_DASH);
        restar_movimientos(juego,movimiento,POS_DASH);
        if(juego->personajes[POS_DASH].poder_activado == true){
            poder_dash(juego);
            chocar_con_pinzas(juego,POS_DASH);
            juego->personajes[POS_DASH].movimientos_con_poder--;
            if(juego->personajes[POS_DASH].movimientos_con_poder==0){
                juego->personajes[POS_DASH].poder_activado=false;
                juego->personajes[POS_DASH].tiene_supertraje= false;
                juego->supertrajes[POS_DASH].usado=true;
            }  
        }  
            if(encontro_al_familiar(*juego,POS_DASH)){
                juego->id_personaje_actual=4;
            }    
    }else if(juego->id_personaje_actual== 4){

        if(juego->personajes[POS_INCREIBLE].poder_activado == true){
            mover_personaje(juego,movimiento,POS_INCREIBLE,1);
            chocar_con_pinzas(juego,POS_INCREIBLE);
            restar_movimientos(juego,movimiento,POS_INCREIBLE);
            juego->personajes[POS_INCREIBLE].movimientos_con_poder--;

            if(juego->personajes[POS_INCREIBLE].movimientos_con_poder==0){
                juego->personajes[POS_INCREIBLE].poder_activado=false;
                juego->personajes[POS_INCREIBLE].tiene_supertraje= false;
                juego->supertrajes[POS_INCREIBLE].usado=true;
            }    
        }else{
            mover_personaje(juego,movimiento,POS_INCREIBLE,1);
            recolectar_traje(juego,POS_INCREIBLE);
            chocar_con_pinzas(juego,POS_INCREIBLE);
            restar_movimientos(juego,movimiento,POS_INCREIBLE);
        }     
        
    }    
}

int estado_juego(juego_t juego){

    int personaje_actual=0;
    if(juego.id_personaje_actual == 1){
        personaje_actual=0;
    }else if(juego.id_personaje_actual==2){
        personaje_actual=1;
    }else if(juego.id_personaje_actual==3){
        personaje_actual=2;
    }else{
        personaje_actual=3;
    }
    if( gano(juego)){
        return 1;
    }else if(juego.personajes[personaje_actual].movimientos == 0){
        return -1;
    }else{
        return 0;
    }
}