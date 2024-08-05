#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include"kronos.h"
#include"increidle.h"
#include"prueba.h"
#define MAX_CONTRASENIA 6
#define ARRIBA  'W'
#define ABAJO 'S'
#define DERECHA  'D'
#define IZQUIERDA 'A'
#define MOVIMIENTO_CON_PODER 'C'
#define CONTRASENIA_CORRECTA "KRONOS"

/*
 *pre_condiciones : Recibe la contraseña del tp1 .
 *post_condiciones :Compara la contraseña recibida del tp1 con la contraseña correcta,devolviendo true en caso que sean iguales o false en caso que sean distintas. 
 */
bool es_contrasenia_correcta(char contrasenia_divinada[MAX_CONTRASENIA]){
    if(strcmp(contrasenia_divinada ,CONTRASENIA_CORRECTA )== 0){
        return true;
    }
    return false;
}
/*
 *pre_condiciones : Recibe un movimiento .
 *post_condiciones : devuelve true en caso que estee o false si no esta. 
 */
bool  es_movimiento_correcto(char movimiento){
    return(movimiento  == ARRIBA || movimiento == ABAJO || movimiento == DERECHA || movimiento== IZQUIERDA || movimiento == MOVIMIENTO_CON_PODER);
}
/*
 *pre_condiciones : recibe la verificacion del movimiento ingresado.
 *post_condiciones : Pide un moviento al usuario y verifica si cumple con la verificacion,sino vuelve a pedirla. 
 */
void pedir_movimientos(char* movimiento){
    printf("Seleccione una opcion para moverse :\n W) para arriba\n S) para abajo\n A) para izquierda\n D) para derecha\n C) para activar e poder\n");
    scanf(" %c",movimiento);
    while(es_movimiento_correcto(*movimiento) == false){
        printf("Se equivoco ,Seleccione :\n W) para arriba\n S) para abajo\n A) para izquierda\n D) para derecha\n");
        scanf(" %c",movimiento);
    }
    
}
int main(){ 

    srand((unsigned)time(NULL));
    juego_t juego;
    char contrasenia_adivinada[MAX_CONTRASENIA];
    char movimiento= ' ';
    adivinar_contrasenia(contrasenia_adivinada);
    bool contrasenia_completa= es_contrasenia_correcta(contrasenia_adivinada);
    inicializar_juego(&juego,contrasenia_completa);

    while (estado_juego(juego) == 0){
        imprimir_terreno(juego);
        pedir_movimientos(&movimiento);
        realizar_jugada(&juego, movimiento);            
        primer_orden_de_rotacion(&juego);  
        if(estado_juego(juego) == 0){ 
            imprimir_terreno(juego);
            pedir_movimientos(&movimiento);
            realizar_jugada(&juego, movimiento);            
            segundo_orden_de_rotacion(&juego);  
            if(estado_juego(juego) == 0){
                imprimir_terreno(juego);
                pedir_movimientos(&movimiento);
                realizar_jugada(&juego, movimiento);
                segundo_orden_de_rotacion(&juego);
                if(estado_juego(juego) == 0){
                    imprimir_terreno(juego);
                    pedir_movimientos(&movimiento);
                    realizar_jugada(&juego, movimiento);       
                    tercer_orden_de_rotacion(&juego);   
                    if(estado_juego(juego) == 0){
                        imprimir_terreno(juego);
                        pedir_movimientos(&movimiento);
                        realizar_jugada(&juego, movimiento);
                        tercer_orden_de_rotacion(&juego); 
                        if(estado_juego(juego) == 0){                        
                            imprimir_terreno(juego);
                            pedir_movimientos(&movimiento);
                            realizar_jugada(&juego, movimiento);               
                            cuarto_orden_de_rotacion(&juego); 
                            if(estado_juego(juego) == 0){                                         
                                imprimir_terreno(juego);
                                pedir_movimientos(&movimiento);
                                realizar_jugada(&juego, movimiento);         
                                cuarto_orden_de_rotacion(&juego); 
                                if(estado_juego(juego) == 0){  
                                    imprimir_terreno(juego);
                                    pedir_movimientos(&movimiento);
                                    realizar_jugada(&juego, movimiento);   
                                    primer_orden_de_rotacion(&juego);  
                                }    
                            }
                        }
                    }
                }                            
            }
        }    
    }
    return 0;
}
