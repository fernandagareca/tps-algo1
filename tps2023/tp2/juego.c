#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chambuchito.h"
#include "cocineritos.h"
#include "restaurante.h"

int main(){

    srand ((unsigned)time(NULL));
    int precio = 0;
    char movimiento = ' ';
    juego_t juego;
    calcular_precio_chambuchito(&precio);
    inicializar_juego(&juego,precio);

    while(estado_juego(juego) == 0){
        imprimir_terreno(juego);
        pedir_movimientos(&movimiento, &juego);
        realizar_jugada(&juego,movimiento);
        system("clear");
    }
    return 0;
}

