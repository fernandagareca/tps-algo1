#include "restaurante.h"
#include "cocineritos.h"
#include <string.h>

#define ARRIBA  'W'
#define ABAJO  'S'
#define DERECHA 'D'
#define IZQUIERDA 'A'
#define MAX_FILAS 21
#define MAX_COLUMNAS 21 

#define ALIMENTO_LECHUGA "LECHUGA"
#define ALIMENTO_TOMATE "TOMATE"
#define ALIMENTO_MASA "MASA"
#define ALIMENTO_JAMON "JAMON"
#define ALIMENTO_QUESO "QUESO"
#define ALIMENTO_CARNE "CARNE"
#define ALIMENTO_MILANESA "MILANESA"
#define ALIMENTO_PAN "PAN"
#define OBJETO_MATAFUEGO "MATAFUEGO"
#define MANO_VACIA "VACIO"


#define COMIDA_ENSALADA "ENSALADA"
#define COMIDA_PIZZA "PIZZA"
#define COMIDA_HAMBURGUESA "HAMBURGUESA"
#define COMIDA_SANWICH "SANDWICH"
#define PERSONEJE_STITCH "Stitch"
#define PERSONAJE_REUBEN "Reuben"


static const char STITCH  = 'S';
static const char REUBEN = 'R';
static const char AGARRAR  = 'R';
static const char CORTAR  = 'C';
static const char ACTIVAR_MATAFUEGO = 'M';
static const char ENSALADA  = 'E';
static const char PIZZA  = 'P';
static const char HAMBURGUESA  = 'H';
static const char SANDWICH ='S';
static const char CAMBIO_DE_PERSONAJE = 'X';
static const char PASAR_INGREDIENTE ='T';
static const char HORNEAR = 'H';
static const char MATAFUEGO ='M';
static const char HORNO ='H';
static const char FUEGOS ='F';

static const char LECHUGA ='L';
static const char TOMATE = 'T';
static const char MILANESA ='I';
static const char PAN ='N';
static const char JAMON ='J';
static const char QUESO ='Q';
static const char MASA ='O';
static const char CARNE ='B';
static const char VACIO ='V';
static const int PRECIO_MINIMO = 100;
static const int PRECIO_BASICO = 150;
static const int NO_EXISTE = -1;
static const int PRIMERA_FILA = 1;
static const int PRIMERA_COLUMNA = 1;
static const int ULTIMA_FILA = 19;
static const int ULTIMA_COLUMNA = 19;
static const int FILA_CENTRAL_STITCH = 9;
static const int FILA_CENTRAL_REUBEN = 11;
static const int UNA_POSICION = 1;
static const int FILA_CENTRAL = 10;

static const int POSICION_ENSALADA =0;
static const int POSICION_PIZZA = 1;
static const int POSICION_HAMBURGUESA = 2;;
static const int POSICION_SANWICH = 3;
static const int LIMITE_VALORES_POSITIVOS = 0;






bool se_pisan_objetos( objeto_t objeto[MAX_OBJETOS], int tope, int fil ,int col){
    bool se_pisan = false;
    for (int i = 0; i < tope; i++){
        if(fil == objeto[i].posicion.fil && col == objeto[i].posicion.col){
            se_pisan = true;
        }
    }
    return se_pisan;
}

bool se_pisan_ingredientes( ingrediente_t ingredientes[MAX_INGREDIENTES], int tope, int fil, int col){
    bool se_pisan= false;
    for (int i = 0; i < tope ; i++){
        if( fil == ingredientes[i].posicion.fil && col == ingredientes[i].posicion.col){
            se_pisan = true;
        }
    }
    return se_pisan;

}

bool se_pisa_puerta(coordenada_t puerta, int fil, int columna){
    return (fil == puerta.fil && columna == puerta.col);
}
bool se_pisa_personaje(personaje_t personaje, int fil, int col){
    return (fil == personaje.posicion.fil && col == personaje.posicion.col);
}


bool es_movimiento_correcto(char movimiento){
    return( movimiento == ARRIBA || movimiento == ABAJO || movimiento == DERECHA || movimiento == IZQUIERDA  || movimiento == AGARRAR 
            || movimiento == CORTAR || movimiento == ACTIVAR_MATAFUEGO || movimiento == CAMBIO_DE_PERSONAJE || movimiento == PASAR_INGREDIENTE 
            || movimiento == HORNEAR);
    
}

bool pasa_los_limites(char movimiento, personaje_t personaje){


        if(personaje.posicion.fil == PRIMERA_FILA && movimiento == ARRIBA){
            return true;
        }else if(personaje.posicion.col == PRIMERA_COLUMNA && movimiento == IZQUIERDA){
            return true;
        }else if(personaje.posicion.col  == ULTIMA_COLUMNA && movimiento== DERECHA){
            return true;
        }else if(personaje.posicion.fil == FILA_CENTRAL_STITCH && movimiento == ABAJO){
            return true;
        }else if(personaje.posicion.fil == ULTIMA_FILA && movimiento == ABAJO){
            return true;
        }else if(personaje.posicion.fil == FILA_CENTRAL_REUBEN && movimiento == ARRIBA){
            return true;
        }

    return false;
}



bool choca_con_objetos(objeto_t objetos[MAX_OBJETOS], personaje_t personaje, char movimiento, int posicion){

    bool tropieza = false;
    int fila_personaje = personaje.posicion.fil;
    int columna_personaje = personaje.posicion.col;
    int fila_fuego = objetos[posicion].posicion.fil;
    int columna_fuego = objetos[posicion].posicion.col;

    if((fila_fuego == fila_personaje - UNA_POSICION ) && (columna_fuego == columna_personaje) &&(movimiento == ARRIBA)){
        tropieza = true;
    }else if((fila_fuego == fila_personaje + UNA_POSICION) && (columna_fuego == columna_personaje) && movimiento == ABAJO){
        tropieza = true;
    }else if((fila_fuego == fila_personaje) && (columna_fuego == columna_personaje - UNA_POSICION) && movimiento == IZQUIERDA){
        tropieza = true;
    }else if((fila_fuego == fila_personaje) && (columna_fuego == columna_personaje + UNA_POSICION) && movimiento == DERECHA){
        tropieza = true;
    }
    return tropieza;

}

int posicion_fuego(objeto_t obstaculos[MAX_OBSTACULOS], int tope){

    int posicion = NO_EXISTE;

    for (int i = 0; i < tope; i++){
        if(obstaculos[i].tipo == FUEGOS){
            posicion = i;
        }
    }
    return posicion;
}
bool personaje_tiene_fuego(objeto_t obstaculos[MAX_OBSTACULOS], int tope, personaje_t personaje, int* posicion){
    bool tiene_fuego = false;
    *posicion = posicion_fuego(obstaculos, tope);

    if(*posicion != NO_EXISTE && personaje.tipo == STITCH){
        if(obstaculos[*posicion].posicion.fil < FILA_CENTRAL){
            tiene_fuego = true;
        }
    }else if(*posicion != NO_EXISTE && personaje.tipo == REUBEN){
        if(obstaculos[*posicion].posicion.fil > FILA_CENTRAL){
            tiene_fuego = true;
        }
    }

    return tiene_fuego;

}
int posicion_horno(objeto_t herramientas[MAX_HERRAMIENTAS], int tope, int posicion_invalida){
    int posicion = NO_EXISTE;

    for (int i = 0; i < tope; i++){
        if(herramientas[i].tipo == HORNO && i != posicion_invalida){
            posicion = i;
        }
    }
    return posicion;
}

bool objeto_esta_presente(objeto_t objeto[MAX_OBJETOS], int tope, char elemento){

    bool se_encuentra = false;

    for (int i = 0; i < tope; i++){
        if(objeto[i].tipo == elemento){
            se_encuentra = true;
        }
    }
    return se_encuentra;
}
void sumar_movimientos( char movimiento, personaje_t personaje, int* cantidad_movimientos, juego_t juego){

    int primer_horno = posicion_horno(juego.herramientas,juego.tope_herramientas,-1);
    int segundo_horno = posicion_horno(juego.herramientas,juego.tope_herramientas,primer_horno);
    
    if(!objeto_esta_presente(juego.obstaculos, juego.tope_obstaculos,FUEGOS)){
        if((movimiento == ARRIBA || movimiento == ABAJO || movimiento == DERECHA || movimiento == IZQUIERDA) && !pasa_los_limites(movimiento,personaje) &&
            !choca_con_objetos(juego.herramientas, personaje, movimiento, primer_horno) && 
            !choca_con_objetos(juego.herramientas, personaje, movimiento, segundo_horno)){
        
            (*cantidad_movimientos)++;
        }
    }
}

int comida(char comida_actual){
    int comida_en_proceso =0;

    if(comida_actual == ENSALADA){
        comida_en_proceso = POSICION_ENSALADA;

    }else if(comida_actual == PIZZA){
        comida_en_proceso = POSICION_PIZZA;

    }else if(comida_actual == HAMBURGUESA){
        comida_en_proceso = POSICION_HAMBURGUESA;

    }else{
        comida_en_proceso = POSICION_SANWICH;
    }
    return comida_en_proceso;
}

personaje_t personaje_actual(char personaje_activo,personaje_t stitch ,personaje_t reuben ){

    if(personaje_activo == STITCH){
        return stitch;
    }else{
        return reuben;
    }
    
}

personaje_t* personaje(char personaje_activo, personaje_t* stitch, personaje_t* reuben){
    if(personaje_activo == STITCH){
        return stitch;
    }else{
        return reuben;

    }
}

void cambiar_de_personaje(char* personaje_actual, char movimiento){

    if(movimiento == CAMBIO_DE_PERSONAJE && *personaje_actual == STITCH){
        *personaje_actual = REUBEN;

    }else if(movimiento == CAMBIO_DE_PERSONAJE && *personaje_actual == REUBEN){
        *personaje_actual = STITCH;
    }
}
int pos_ingrediente(ingrediente_t ingredientes[MAX_INGREDIENTES], int tope, personaje_t personaje){
    int posicion =-1;
        for (int i = 0; i < tope; i++){
        if(personaje.posicion.fil == ingredientes[i].posicion.fil && personaje.posicion.col == ingredientes[i].posicion.col){
            posicion = i;
        }
    }
    return posicion;
}
int posicion_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, personaje_t personaje){
    int pos = -1;
    for (int i = 0; i < tope; i++){
        if(personaje.objeto_en_mano == ingrediente[i].tipo){
            pos = i;
        }
    }
    return pos;
}
bool estado(bool estado_ingrediente){
    bool precesado = false;
    if(estado_ingrediente){
        precesado = true;
    }
    return precesado;
    
}

int valor_absoluto(int numero){
    if(numero < LIMITE_VALORES_POSITIVOS){
        return (numero*-1);
    }else{
        return numero;
    }
}
int distancia_manhattan(int primera_fila,int primera_columna, int segunda_fila, int segunda_columna){

    int primera_resta = (primera_fila - segunda_fila);
    int segunda_resta = (primera_columna - segunda_columna);

    int primer_valor = valor_absoluto(primera_resta);
    int segundo_valor = valor_absoluto(segunda_resta);

    return (primer_valor + segundo_valor);
}

int posicion_buscada(objeto_t objetos[MAX_OBJETOS], int tope_objetos, personaje_t personaje){

    int posicion=-1;
    for (int i = 0; i < tope_objetos; i++){
        if(personaje.posicion.fil == objetos[i].posicion.fil && personaje.posicion.col == objetos[i].posicion.col){
            posicion = i;
        }
    }
    return posicion;
}
bool esta_mesa_vacia(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, coordenada_t mesa){
    bool esta_vacio = true;

    if(se_pisan_ingredientes(ingrediente, tope, mesa.fil, mesa.col)){
        esta_vacio = false;
    }
    return esta_vacio;
}
int posicion(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, int fil, int col){

    int posicion = NO_EXISTE;
    for (int i = 0; i < tope; i++){
        if(fil == ingrediente[i].posicion.fil && col == ingrediente[i].posicion.col){
            posicion = i;
        }
    }
    return posicion;
}
bool es_ingrediente_para_cocinar(char ingrediente){
    return (ingrediente == MASA || ingrediente == CARNE || ingrediente == MILANESA);

}
bool ingrediente_es_para_cortar(char ingrediente){
    return ( ingrediente == LECHUGA || ingrediente == TOMATE || ingrediente == PAN || ingrediente == JAMON || ingrediente == QUESO);
}
bool esta_procesado(ingrediente_t ingrediente[MAX_INGREDIENTES], int pos_ingrediente){

    bool esta_procesado = false;

    if((ingrediente[pos_ingrediente].tipo == LECHUGA || ingrediente[pos_ingrediente].tipo == TOMATE || ingrediente[pos_ingrediente].tipo == PAN ||
        ingrediente[pos_ingrediente].tipo == JAMON || ingrediente[pos_ingrediente].tipo == QUESO)  && ingrediente[pos_ingrediente].esta_cortado){
        
        esta_procesado = true;

    }else if((ingrediente[pos_ingrediente].tipo == CARNE || ingrediente[pos_ingrediente].tipo == MILANESA || ingrediente[pos_ingrediente].tipo == MASA) && 
        ingrediente[pos_ingrediente].esta_cocinado){
        
        esta_procesado  = true;
    }
    return esta_procesado;

}
bool es_juego_ganado(juego_t juego){

    bool es_ganado = false;

    if(juego.precio_total <= PRECIO_MINIMO && juego.comida_actual == PIZZA && juego.tope_comida_lista == 3){
        es_ganado = true;
    }else if(juego.precio_total > PRECIO_MINIMO && juego.precio_total <= PRECIO_BASICO && juego.comida_actual == HAMBURGUESA && juego.tope_comida_lista == 4){
        es_ganado = true;
    }else if(juego.precio_total > PRECIO_BASICO && juego.comida_actual == SANDWICH && juego.tope_comida_lista == 6){
        es_ganado = true;
    }
    return es_ganado;
}

void tipo_objeto(char objeto_en_mano, char objeto[MAX_NOMBRE]){
    if(objeto_en_mano == LECHUGA){
        strcpy(objeto,ALIMENTO_LECHUGA);
    }else if(objeto_en_mano == TOMATE){
        strcpy(objeto,ALIMENTO_TOMATE);
    }else if(objeto_en_mano == MASA){
        strcpy(objeto,ALIMENTO_MASA);
    }else if(objeto_en_mano == JAMON){
        strcpy(objeto,ALIMENTO_JAMON);
    }else if(objeto_en_mano == QUESO){
        strcpy(objeto,ALIMENTO_QUESO);
    }else if(objeto_en_mano == CARNE){
        strcpy(objeto,ALIMENTO_CARNE);
    }else if(objeto_en_mano == MILANESA){
        strcpy(objeto,ALIMENTO_MILANESA);
    }else if(objeto_en_mano == PAN){
        strcpy(objeto,ALIMENTO_PAN);
    }else if(objeto_en_mano == MATAFUEGO){
        strcpy(objeto, OBJETO_MATAFUEGO);
    }else if(objeto_en_mano == VACIO){
        strcpy(objeto, MANO_VACIA);
    }    
}

void tipo_comida(char tipo, char comida[MAX_NOMBRE]){

    if(tipo == ENSALADA){
        strcpy(comida,COMIDA_ENSALADA);
    }else if(tipo == PIZZA){
        strcpy(comida,COMIDA_PIZZA);
    }else if(tipo == HAMBURGUESA){
        strcpy(comida,COMIDA_HAMBURGUESA);
    }else if(tipo == SANDWICH){
        strcpy(comida, COMIDA_SANWICH);
    }

}

void jugador(char personaje_actual, char nombre[MAX_NOMBRE]){

    if(personaje_actual == STITCH){
        strcpy(nombre,PERSONEJE_STITCH);
    }else{
        strcpy(nombre,PERSONAJE_REUBEN);
    }

}
void pedir_movimientos(char* movimiento, juego_t* juego){

    personaje_t personaje = personaje_actual(juego->personaje_activo, juego->stitch, juego->reuben);
    int pos_comida = comida(juego->comida_actual);
    int pos_ingrediente = posicion_ingrediente(juego->comida[pos_comida].ingrediente, juego->comida[pos_comida].tope_ingredientes,personaje);
    
    char objeto[MAX_NOMBRE];
    char comida[MAX_NOMBRE];
    char nombre[MAX_NOMBRE];
    tipo_objeto(personaje.objeto_en_mano,objeto);
    tipo_comida(juego->comida_actual, comida);
    jugador(juego->personaje_activo,nombre);

    bool estado_cortado = estado(juego->comida[pos_comida].ingrediente[pos_ingrediente].esta_cortado);
    bool estado_cocinado = estado(juego->comida[pos_comida].ingrediente[pos_ingrediente].esta_cocinado);

    printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    printf(" ┃ Seleccione un moviento    ┃                           ┃ Movimientos : %i     \n",juego->movimientos);
    printf(" ┃  (W) Arriba               ┃ (H) Hornear               ┃ Comida actual: %s     \n",comida);
    printf(" ┃  (S) Abajo                ┃ (T) Dejar en la mesa      ┃ Personaje_actual %s   \n",nombre);
    printf(" ┃  (D) Derecha              ┃ (X) Cambio de personaje   ┃ Objeto en mano: %s    \n",objeto);
    printf(" ┃  (A) Izquierda            ┃ (M) Activar el matafuego  ┃  ● cortado : %s        \n",estado_cortado ? "SI": "NO");
    printf(" ┃  (R) Agarrar              ┃ (C) Cortar                ┃  ● cocinado : %s       \n",estado_cocinado ? "SI": "NO");
    printf(" ┃                           ┃                           ┃  Presupuesto : %i      \n",juego->precio_total);
    printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    scanf(" %c",movimiento);

    while(!es_movimiento_correcto(*movimiento)){
    printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    printf(" ┃  El movimiento es incorrecto por favor seleccione:    ┃   \n");
    printf(" ┃  (W) Arriba               ┃ (H) Hornear               ┃  \n");
    printf(" ┃  (S) Abajo                ┃ (T) Dejar en la mesa      ┃  \n");
    printf(" ┃  (D) Derecha              ┃ (X) Cambio de personaje   ┃  \n");
    printf(" ┃  (A) Izquierda            ┃ (M) Activar el matafuego  ┃  \n");
    printf(" ┃  (R) Agarrar              ┃ (C) Cortar                ┃  \n");
    printf(" ┃                           ┃                           ┃  \n");
    printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    scanf(" %c",movimiento);
    }
    sumar_movimientos(*movimiento,personaje, &(juego->movimientos), *juego);

}

