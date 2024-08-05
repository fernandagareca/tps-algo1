#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "cocineritos.h"
#include "restaurante.h"

const char ESPACIO ='_';
#define MAX_FILAS 21
#define MAX_COLUMNAS 21
#define ARRIBA  'W'
#define ABAJO  'S'
#define DERECHA 'D'
#define IZQUIERDA 'A'
static const char ACTIVAR_MATAFUEGO ='M';
static const char PASAR_INGREDIENTE ='T';
static const char HORNEAR = 'H';
const char NADA ='V';
const char VACIO = ' ';
const char STITCH = 'S';
const char REUBEN = 'R';
const char PAREDES ='#';
const char AGUJEROS ='A';
const char FUEGOS ='F';
const char CUCHILLO = 'C';
const char HORNO = 'H';
const char MATAFUEGOS = 'M';
const int PRECIO_MINIMO= 100;
static const int PRECIO_BASICO  = 150;
const char LECHUGA ='L';
const char TOMATE = 'T';
const char MILANESA ='I';
const char PAN ='N';
const char JAMON ='J';
const char QUESO ='Q';
const char MASA ='O';
const char MESA ='_';
const char CARNE ='B';


const int FILA_INICIAL =0;
const int COLUMNA_INICIAL =0;
const int COLUMNA_FINAL =20;
const int FILA_FINAL =20;
const int FILA_CENTRAL =10;
const int LIMITE_PARED_SUPERIOR = 20;
const int LIMITE_PARED_DERECHO = 40;
const int LIMITE_PARED_IMFERIOR = 60;
const int LIMITE_PARED_IZQIERDO = 80;
const int LIMITE_MESA = 89;
const int MAX_OBSTACULOS_STITCH = 10;
const int LIMITE_HERRAMIENTAS_STITCH = 2;
const char ENSALADA ='E';
const char PIZZA ='P';
const char HAMBURGUESA ='H';
const char SANDWICH ='S';
const char PUERTA_DE_SALIDA ='P';

const char AGARAR ='R';
const char CORTAR ='C';
const int COMIDA_ENSALADA = 0;
const int COMIDA_PIZZA = 1;
const int COMIDA_HAMBURGUESA =2;
const int COMIDA_SANWICH = 3;
const int FILA_PARED = 10;

const int MAX_FILA_STITCH = 9;
const int MIN_FILA_STITCH = 1;
const int MAX_FILA_REUBEN = 9;
const int MIN_FILA_REUBEN = 11;

const int MAX_COLUMNA_JUGADOR = 19;
const int MIN_COLUMNA_JUGADOR = 1;
const int NO_EXISTE = -1;
const int MOVIMIENTOS_NECESARIOS = 15;
const int DISNTANCIA_VALIDA_HORNO = 1;
const int CANTIDADA_INGREIDNETES_PIZZA = 3;
const int CANTIDAD_INGREDIENTES_HAMBURGUESA =4;
const int CANTIDAD_INGREDIENTES_ENSALADA = 2;
const int PERDIDO = -1;
const int GANADO = 1;
const int JUGANDO = 0;
const int PRIMERA_POSICION =0;
const int SEGUNDA_POSICION =1;
const int TERCERA_POSICION =2;
const int CUARTA_POSICION =3;
const int QUINTA_POSICION = 4;
const int SEXTA_POSICION = 5;
const int DISTANCIA_VALIDA_MESA =1;
const int DISTANCIA_VALIDA_FUEGO = 2;


/*
 *pre: -
 *post: Carga la matriz con espacio vacio.
 */
void rellenar_matriz(char restaurante[MAX_FILAS][MAX_COLUMNAS]){
    for(int  i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){
        restaurante[i][j]= ESPACIO;
        }
    }
}
/*
 *pre: Recibe el vector de paredes vacio , una posicion en el vector de paredes ,una fila y columna para la pared.
 *post:Carga una pared en el vector de paredes.
 */
void cargar_pared(coordenada_t paredes[MAX_PAREDES],int posicion ,int contador_fil, int contador_col){

    paredes[posicion].fil = contador_fil;
    paredes[posicion].col = contador_col;
}
/*
 *pre: Recibe el vector de parerdes con su tope definido en 99.
 *post: inicializa todas las paredes del terreno.
 */
void inicializar_paredes(coordenada_t paredes[MAX_PAREDES],int tope_paredes){

    int contador_pared_inferior =0;
    int contador_pared_izquierda =0;
    int contador_pared_derecha =-1;
    int contador_central =0;
    int contador_derecho =10;

    for (int i = 0; i < tope_paredes; i++){

        if(i < LIMITE_PARED_SUPERIOR){
            cargar_pared(paredes, i, FILA_INICIAL, i);

        }else if(i < LIMITE_PARED_DERECHO){
            contador_pared_derecha++;
            cargar_pared(paredes, i, contador_pared_derecha,COLUMNA_FINAL);
        
        }else if(i< LIMITE_PARED_IMFERIOR){
            contador_pared_inferior++;
            cargar_pared(paredes, i, FILA_FINAL, contador_pared_inferior);
        
        }else if( i < LIMITE_PARED_IZQIERDO){
            contador_pared_izquierda++;
            cargar_pared(paredes, i, contador_pared_izquierda,COLUMNA_INICIAL); 

        }else if( i < LIMITE_MESA){
            contador_central++;
            cargar_pared(paredes, i, FILA_CENTRAL, contador_central);

        }else{
            contador_derecho++;
            cargar_pared(paredes, i, FILA_CENTRAL, contador_derecho);
        }
    }
}
/*
 *pre: Recibe el vector de obstaculos con su tope definido en 20.
 * post: carga los obstaculos en eel vector de obstaculos asignandole una fila y columna random junto con su tipo verificando que no se pisen entre si.
 */
void inicializar_obstaculos(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos){

    for (int i = 0; i < tope_obstaculos; i++){

        if(i < MAX_OBSTACULOS_STITCH){
            obstaculos[i].posicion.fil = rand() % MAX_FILA_STITCH + MIN_FILA_STITCH;
            obstaculos[i].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
            obstaculos[i].tipo = AGUJEROS;
            while(se_pisan_objetos( obstaculos, i, obstaculos[i].posicion.fil, obstaculos[i].posicion.col)){

                obstaculos[i].posicion.fil = rand() % MAX_FILA_STITCH + MIN_FILA_STITCH;
                obstaculos[i].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
            }
        }else{
            obstaculos[i].posicion.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
            obstaculos[i].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
            obstaculos[i].tipo = AGUJEROS;
            while(se_pisan_objetos( obstaculos, i, obstaculos[i].posicion.fil, obstaculos[i].posicion.col)){
                        
                obstaculos[i].posicion.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
                obstaculos[i].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
            }
        }
    }
}

/*
 *pre: Recibe el vector de herramientas vacio juntro con su tope definido en 4, el vector de obstaculos cargado junto con su tope definido en 20. 
 * post:Carga el vector de herramientas asignandole a cada elemento una fila y columna random y su tipo correspondiente 
 *      verificando que no se pisen entre si ni pisen a los obstaculos.
 */
void inicializar_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], objeto_t obstaculos[MAX_OBSTACULOS], int tope_herramientas, int tope_obstaculos){
    for (int i = 0; i < tope_herramientas; i++){

        if(i < LIMITE_HERRAMIENTAS_STITCH){
            herramientas[i].posicion.fil = rand() % MAX_FILA_STITCH + MIN_FILA_STITCH;
            herramientas[i].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
            herramientas[i].tipo = CUCHILLO;
            while(se_pisan_objetos(obstaculos, tope_obstaculos, herramientas[i].posicion.fil, herramientas[i].posicion.col) ||
                se_pisan_objetos(herramientas, i, herramientas[i].posicion.fil, herramientas[i].posicion.col)){
                herramientas[i].posicion.fil = rand() % MAX_FILA_STITCH + MIN_FILA_STITCH;
                herramientas[i].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
            }
        }else{
            herramientas[i].posicion.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
            herramientas[i].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
            herramientas[i].tipo = HORNO;
            while (se_pisan_objetos(obstaculos, tope_obstaculos, herramientas[i].posicion.fil, herramientas[i].posicion.col) ||
                se_pisan_objetos(herramientas, i, herramientas[i].posicion.fil, herramientas[i].posicion.col)){
                herramientas[i].posicion.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
                herramientas[i].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
            }
        }
    }
}
bool ingrediente_pisa_elementos(juego_t juego, personaje_t personaje,ingrediente_t ingrediente[MAX_INGREDIENTES],int posicion_ingrediente){

    bool se_pisan = false;
    if(se_pisan_objetos(juego.obstaculos,juego.tope_obstaculos,ingrediente[posicion_ingrediente].posicion.fil, ingrediente[posicion_ingrediente].posicion.col) ||
        se_pisan_objetos(juego.herramientas,juego.tope_herramientas,ingrediente[posicion_ingrediente].posicion.fil,ingrediente[posicion_ingrediente].posicion.col) || 
        se_pisan_ingredientes(ingrediente,posicion_ingrediente,ingrediente[posicion_ingrediente].posicion.fil,ingrediente[posicion_ingrediente].posicion.col) ||
        se_pisa_puerta(juego.salida,ingrediente[posicion_ingrediente].posicion.fil,ingrediente[posicion_ingrediente].posicion.col) ||
        se_pisa_personaje(personaje,ingrediente[posicion_ingrediente].posicion.fil,ingrediente[posicion_ingrediente].posicion.col)){
        
        se_pisan = true;
    }
    return se_pisan;
}
/*
 *pre: Recibe el juego una posicion en el vector de comidas y una posicion en el vector de ingredientes tambien el tipo de ingrediente.
 * post: Carga un ingrediente en el cuadrante de Stitch verificando que no pise a otros objetos.
 */
void cargar_ingrediente_stitch(int posicion_comida ,int posicion_ingrediente,juego_t*  juego, char ingrediente){

    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].posicion.fil = rand() %  MAX_FILA_STITCH + MIN_FILA_STITCH;
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].tipo = ingrediente;
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].esta_cortado = false;
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].esta_cocinado = false;

    while(ingrediente_pisa_elementos(*juego,juego->stitch,juego->comida[posicion_comida].ingrediente,posicion_ingrediente)){
        
        juego->comida[posicion_comida].ingrediente[posicion_ingrediente].posicion.fil = rand() %  MAX_FILA_STITCH + MIN_FILA_STITCH;
        juego->comida[posicion_comida].ingrediente[posicion_ingrediente].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    }

}

/*
 *pre: Recibe el juego una posicion en el vector de comidas y una posicion en el vector de ingredientes tambien el tipo de ingrediente.
 * post: Carga un inngrediente en el cuadrante de Reuben verificando que no pise a otros objetos.
 */
void cargar_ingrediente_reuben(int posicion_comida,int posicion_ingrediente,juego_t* juego, char ingrediente){
    
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].posicion.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].tipo = ingrediente;
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].esta_cortado = false;
    juego->comida[posicion_comida].ingrediente[posicion_ingrediente].esta_cocinado = false;

    while (ingrediente_pisa_elementos(*juego,juego->reuben,juego->comida[posicion_comida].ingrediente,posicion_ingrediente)){
        
        juego->comida[posicion_comida].ingrediente[posicion_ingrediente].posicion.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
        juego->comida[posicion_comida].ingrediente[posicion_ingrediente].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    }
}

/*
 *pre: Recibe el juego y una posicion en el vector de comida.
 *post: Carga los ingredientes de la Ensalada.
 */
void cargar_ensalda(juego_t* juego,int posicion_comida){

    juego->comida[posicion_comida].tope_ingredientes = 2;
    juego->comida[posicion_comida].tipo = ENSALADA;
    cargar_ingrediente_stitch(posicion_comida,0,juego,LECHUGA);
    cargar_ingrediente_stitch(posicion_comida,1,juego,TOMATE);
}

/*
 *pre: Recibe el juego y una posicion en el vector de comida.
 *post: Carga los ingredientes de la Pizza.
 */
void cargar_pizza(juego_t* juego,int posicion_comida){

    juego->comida[posicion_comida].tope_ingredientes = 3;
    juego->comida[posicion_comida].tipo = PIZZA;
    cargar_ingrediente_stitch(posicion_comida,PRIMERA_POSICION ,juego,JAMON);
    cargar_ingrediente_stitch(posicion_comida,SEGUNDA_POSICION ,juego,QUESO);
    cargar_ingrediente_reuben(posicion_comida,TERCERA_POSICION ,juego,MASA);
}

/*
 *pre: Recibe el juego y una posicion en el vector de comida.
 *post: Carga los ingredientes de la Hamburguesa.
 */
void cargar_hamburguesa(juego_t* juego,int posicion_comida){

    juego->comida[posicion_comida].tope_ingredientes = 4;
    juego->comida[posicion_comida].tipo = HAMBURGUESA;
    cargar_ingrediente_stitch(posicion_comida,PRIMERA_POSICION ,juego,PAN);
    cargar_ingrediente_stitch(posicion_comida,SEGUNDA_POSICION ,juego,TOMATE);
    cargar_ingrediente_stitch(posicion_comida,TERCERA_POSICION ,juego,LECHUGA);
    cargar_ingrediente_reuben(posicion_comida,CUARTA_POSICION  ,juego,CARNE);
}
/*
 *pre: Recibe el juego y una posicion en el vector de comida.
 *post: Carga los ingredientes del Sandwich.
 */
void cargar_sandwich(juego_t* juego ,int posicion_comida){

    juego->comida[posicion_comida].tope_ingredientes = 6;
    juego->comida[posicion_comida].tipo = SANDWICH;
    cargar_ingrediente_stitch(posicion_comida,PRIMERA_POSICION ,juego,PAN);
    cargar_ingrediente_stitch(posicion_comida,SEGUNDA_POSICION ,juego,TOMATE);
    cargar_ingrediente_stitch(posicion_comida,TERCERA_POSICION ,juego,LECHUGA);
    cargar_ingrediente_stitch(posicion_comida,CUARTA_POSICION ,juego,QUESO);
    cargar_ingrediente_stitch(posicion_comida,QUINTA_POSICION ,juego,JAMON);
    cargar_ingrediente_reuben(posicion_comida,SEXTA_POSICION ,juego,MILANESA);
}
/*
 *pre: Recive el juego.
 *post: Posiciona Stitch Y Reuben en sus cuadrantes verificando que lo pisen a ningun objeto.
 */
void inicializar_pesonajes(juego_t* juego){

    juego->stitch.posicion.fil = rand() % MAX_FILA_STITCH + MIN_FILA_STITCH;
    juego->stitch.posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    juego->stitch.tipo = STITCH;
    juego->stitch.objeto_en_mano = NADA;
    while(se_pisan_objetos(juego->obstaculos, juego->tope_obstaculos, juego->stitch.posicion.fil, juego->stitch.posicion.col) ||
        se_pisan_objetos(juego->herramientas, juego->tope_herramientas, juego->stitch.posicion.fil, juego->stitch.posicion.col)){

        juego->stitch.posicion.fil = rand() % MAX_FILA_STITCH + MIN_FILA_STITCH;
        juego->stitch.posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    }
    juego->reuben.posicion.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
    juego->reuben.posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    juego->reuben.tipo = REUBEN;
    juego->reuben.objeto_en_mano = NADA;
    while (se_pisan_objetos(juego->obstaculos, juego->tope_obstaculos, juego->reuben.posicion.fil, juego->reuben.posicion.col) ||
        se_pisan_objetos(juego->herramientas, juego->tope_herramientas, juego->reuben.posicion.fil, juego->reuben.posicion.col)){

        juego->reuben.posicion.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
        juego->reuben.posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    }
}

/*
 *pre: Recibe el juego.
 *post: Posiciona la puerta de entrega en el cuadrante de Reuben verificando que no pise a ningun objeto.
 */
void posicionar_puerta(juego_t* juego){

    juego->salida.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
    juego->salida.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    while(se_pisan_objetos(juego->obstaculos, juego->tope_obstaculos,juego->salida.fil, juego->salida.col) ||
        se_pisan_objetos(juego->herramientas,juego->tope_herramientas, juego->salida.fil, juego->salida.col) || 
        (juego->salida.fil == juego->reuben.posicion.fil && juego->salida.col == juego->reuben.posicion.col)){

        juego->salida.fil = rand() % MAX_FILA_REUBEN + MIN_FILA_REUBEN;
        juego->salida.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    }
}

void inicializar_juego(juego_t* juego, int precio){
    
    juego->tope_paredes = 99;
    inicializar_paredes(juego->paredes, juego->tope_paredes);
    juego->tope_obstaculos = 20;
    inicializar_obstaculos( juego->obstaculos, juego->tope_obstaculos);
    juego->tope_herramientas = 4;
    inicializar_herramientas(juego->herramientas, juego->obstaculos, juego->tope_herramientas, juego->tope_obstaculos);
    juego->tope_comida = 1;
    cargar_ensalda(juego,0);
    inicializar_pesonajes(juego);
    posicionar_puerta(juego);
    juego->precio_total = precio;
    juego->tope_comida_lista = 0;
    juego->personaje_activo = STITCH;
    juego->comida_actual = ENSALADA;
    juego->movimientos = 0;
    juego->mesa.fil = 10;
    juego->mesa.col = 10;

}

bool son_movimiento_incorrectos(juego_t juego, char movimiento, personaje_t personaje){

    int posicion_fuego= NO_EXISTE;
    int primer_horno = NO_EXISTE;
    bool tropezarse = false;

    primer_horno = posicion_horno(juego.herramientas, juego.tope_herramientas, NO_EXISTE);

    if(pasa_los_limites(movimiento,personaje)){
        printf("NO PUEDES PASAR LOS LIMITES DE LA MATRIZ\n");
        tropezarse = true;
    }else if(personaje_tiene_fuego(juego.obstaculos,juego.tope_obstaculos,personaje,&posicion_fuego) && 
            choca_con_objetos(juego.obstaculos,personaje,movimiento,posicion_fuego)){
        printf("ESTAS CHOCANDO CON UN FUEGO\n");
        tropezarse = true;
    }else if(choca_con_objetos(juego.herramientas,personaje,movimiento,primer_horno)){
        printf("ESTAS CHOCANDO CON UN HORNO\n");
        tropezarse = true;
    }if(!choca_con_objetos(juego.herramientas,personaje,movimiento,primer_horno)){
        int segundo_horno = posicion_horno(juego.herramientas, juego.tope_herramientas, primer_horno);
        if(choca_con_objetos(juego.herramientas,personaje, movimiento,segundo_horno)){
        printf("ESTAS CHOCANDO CON UN HORNO\n");
            tropezarse = true;
        }
    }
    return tropezarse;

}
/*
 *pre: Recibe el movimiento ingresado por el usuario valido y el jugador actual.
 * post: mueve al personaje dependiendo el movimiento ingresado y no permite que se salga de los limites de la matriz y 
 *       lo restringe para que no pise los hornos y el fuego.
 */
void realizar_movimientos( char movimiento, personaje_t* personaje, juego_t* juego){

    int sumador =1;
    if(son_movimiento_incorrectos(*juego,movimiento,*personaje)){
        return;
    }
    
    if(movimiento == ARRIBA){
        personaje->posicion.fil -= sumador;

    }else if(movimiento == ABAJO){
        personaje->posicion.fil += sumador;

    }else if(movimiento == DERECHA){       
        personaje->posicion.col += sumador;

    }else if(movimiento == IZQUIERDA){
        personaje->posicion.col -= sumador;
    }
}

bool se_pisan_elementos(juego_t juego, objeto_t objeto[MAX_OBJETOS] , int posicion, int tope_elemento){

    personaje_t personaje = personaje_actual(juego.personaje_activo,juego.stitch,juego.reuben);
    int comida_actual = comida(juego.comida_actual);
    bool se_pisan= false;

    if( se_pisan_objetos(juego.obstaculos,juego.tope_obstaculos,objeto[posicion].posicion.fil,objeto[posicion].posicion.col)  || 
        se_pisan_objetos(juego.herramientas,juego.tope_herramientas,objeto[posicion].posicion.fil,objeto[posicion].posicion.col) ||
        se_pisa_puerta(juego.salida,objeto[posicion].posicion.fil,objeto[posicion].posicion.col) ||
        se_pisa_personaje(personaje,objeto[posicion].posicion.fil,objeto[posicion].posicion.col) || 
        se_pisan_ingredientes(juego.comida[comida_actual].ingrediente,juego.comida[comida_actual].tope_ingredientes,objeto[posicion].posicion.fil,
        objeto[posicion].posicion.col)){

        se_pisan = true;    

    }
    return se_pisan;
}
/*
 *pre: Recibe el juego ,la posicion para gregar el fuego al vector y su tope.
 *post:Carga un el fuego en una posicion alertoria , verificando que no pise a ningun objeto y aumenta el tope 
 */

void cargar_obstaculo_fuego(juego_t* juego , int posicion, int* tope_elemento){

    juego->obstaculos[*tope_elemento].posicion.fil = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    juego->obstaculos[*tope_elemento].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    juego->obstaculos[*tope_elemento].tipo = FUEGOS;
    
    while(juego->obstaculos[*tope_elemento].posicion.fil == FILA_PARED || se_pisan_elementos(*juego,juego->obstaculos,posicion,*tope_elemento)){

        juego->obstaculos[*tope_elemento].posicion.fil = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
        juego->obstaculos[*tope_elemento].posicion.col = rand() % MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;
    }
    (*tope_elemento)++;
}
/*
 *pre: Recibe el juego ,la posicion para gregar el Matafuego al vector y su tope.
 *post:Carga el matafuego al vector de herramientas verificando que no pise a ningun objeto y aumenta su tope.
 */
void cargar_matafuego(juego_t* juego , int posicion, int* tope_elemento, int limite_minimo){

    juego->herramientas[*tope_elemento].posicion.fil = rand() % MAX_FILA_STITCH + limite_minimo;
    juego->herramientas[*tope_elemento].posicion.col = rand() %  MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;;
    juego->herramientas[*tope_elemento].tipo = MATAFUEGOS;
    
    while(se_pisan_elementos(*juego,juego->herramientas,posicion,*tope_elemento)){

        juego->herramientas[*tope_elemento].posicion.fil = rand() % MAX_FILA_STITCH + limite_minimo;
        juego->herramientas[*tope_elemento].posicion.col = rand() %  MAX_COLUMNA_JUGADOR + MIN_COLUMNA_JUGADOR;;
    }
    (*tope_elemento)++;
}

/*
 *pre: Recine el movimiemto ingresado por el usuario ,el personaje actual y el juego.
 * post: Agarra el matafuego si el personaje pasa por arriba o  elimina el fuego en el caso que el personaje active el matafuego 
 *      y este a una  distancia manhattan menor igual a 2 tambien elimina el matafuego una ves usado.
 */
void apagar_fuego(personaje_t* personaje, juego_t* juego, char movimiento){

    int posicion_matafuego = NO_EXISTE;
    int pos_fuego = NO_EXISTE;
    
    if(se_pisan_objetos(juego->herramientas,juego->tope_herramientas,personaje->posicion.fil, personaje->posicion.col)){

        posicion_matafuego = posicion_buscada(juego->herramientas ,juego->tope_herramientas ,*personaje);

        if(juego->herramientas[posicion_matafuego].tipo == MATAFUEGOS && personaje->objeto_en_mano == NADA){

            personaje->objeto_en_mano = juego->herramientas[posicion_matafuego].tipo;
        }
    }
    if(personaje_tiene_fuego(juego->obstaculos,juego->tope_obstaculos,*personaje,&pos_fuego) && 
        movimiento == ACTIVAR_MATAFUEGO && personaje->objeto_en_mano == MATAFUEGOS &&
        distancia_manhattan(personaje->posicion.fil,personaje->posicion.col,juego->obstaculos[pos_fuego].posicion.fil,
                            juego->obstaculos[pos_fuego].posicion.col) <= DISTANCIA_VALIDA_FUEGO){
    
        juego->tope_obstaculos--;
        juego->tope_herramientas--;
        personaje->objeto_en_mano = NADA;
        juego->movimientos =0;
    }
}
/*
 * pre:Recibe el juego el movimiento ingresado por el usuario y el personaje actual.
 * post: carga el fuego en uno de los dos cuadrantes a los 15 movimientos y carga el matafuego en el mismo cuadrante de del fuego. 
 */
void cargar_fuego_matafuego(juego_t* juego, personaje_t personaje, char movimiento){
    
    int posicion = NO_EXISTE;

    if(juego->movimientos == MOVIMIENTOS_NECESARIOS &&  (movimiento == ARRIBA || movimiento == ABAJO || movimiento == DERECHA || movimiento == IZQUIERDA) &&
        !objeto_esta_presente(juego->obstaculos,juego->tope_obstaculos,FUEGOS)){

        cargar_obstaculo_fuego(juego ,juego->tope_obstaculos, &(juego->tope_obstaculos));
    }
    if(objeto_esta_presente(juego->obstaculos,juego->tope_obstaculos, FUEGOS) && !objeto_esta_presente(juego->herramientas,juego->tope_herramientas,MATAFUEGOS)){
        
        posicion = posicion_fuego(juego->obstaculos, juego->tope_obstaculos);

        if(juego->obstaculos[posicion].posicion.fil < FILA_PARED){ 
        
            cargar_matafuego(juego,juego->tope_herramientas, &(juego->tope_herramientas),MIN_FILA_STITCH);
        }else{
            cargar_matafuego(juego,juego->tope_herramientas, &(juego->tope_herramientas),MIN_FILA_REUBEN);
        }
    }
    
}
/*
 *pre: Recibe un vector de ingredientes de una comida en especifico junto con su tpe definido y un personaje que sera el personaje activo.
 * post: Agarra un ingrediente del terreno.
 */
void agarrar_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, personaje_t* personaje){

    int pos_buscada = pos_ingrediente(ingrediente, tope, *personaje);
    personaje->objeto_en_mano = ingrediente[pos_buscada].tipo;
}

/*
 *pre: Recibe el vector de ingredientes cargado con su tope defido y el personaje actual.
 *post: Busca el ingrediente que el personaje tiene en la mano y lo deja en la posicion del personaje.
 */
void soltar_ingrediente(ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, personaje_t* personaje){

    int pos_buscada = posicion_ingrediente(ingrediente, tope, *personaje);

    ingrediente[pos_buscada].posicion.fil = personaje->posicion.fil;
    ingrediente[pos_buscada].posicion.col = personaje->posicion.col;
    personaje->objeto_en_mano = NADA;

}
/*
 *pre: recibe el juego y el personaje actual.
 * post: busca la posicion del fuego si esta y en caso que este devuelve true si se encuentra en el mismo cuadrante del personaje actual o caso contrario false.
 */
bool fuego_esta_activo(juego_t juego, personaje_t personaje){

    bool tiene_fuego = false;
    int posicion = posicion_fuego(juego.obstaculos, juego.tope_obstaculos);

    if(posicion != NO_EXISTE && personaje.tipo == STITCH){
        if(juego.obstaculos[posicion].posicion.fil < FILA_PARED){
            tiene_fuego = true;
        }
    }else if(posicion != NO_EXISTE && personaje.tipo == REUBEN){
        if(juego.obstaculos[posicion].posicion.fil > FILA_PARED){
            tiene_fuego = true;
        }
    }

    return tiene_fuego;

}
/*
 * pre: Recibe el juego el movimiento ingresado por el usuario y la pos de la comida actual.
 * post: Realiza las acciones necesarias para cada caso de recoleccion de ingredintes segun el personaje actual.
 */
void recolectar_ingredientes(char movimiento,personaje_t* personaje, ingrediente_t ingrediente[MAX_INGREDIENTES], int tope_ingredientes, juego_t* juego){

    if(movimiento == AGARAR && personaje->objeto_en_mano == NADA && !fuego_esta_activo(*juego,*personaje) && 
        se_pisan_ingredientes(ingrediente, tope_ingredientes ,personaje->posicion.fil, personaje->posicion.col)){

        agarrar_ingrediente(ingrediente, tope_ingredientes, personaje);

    }else if(movimiento == AGARAR && personaje->objeto_en_mano != NADA  && personaje->objeto_en_mano != MATAFUEGOS &&
            !se_pisa_puerta(juego->salida,personaje->posicion.fil,personaje->posicion.col) && 
            !se_pisan_objetos(juego->herramientas,juego->tope_herramientas, personaje->posicion.fil, personaje->posicion.col) &&
            !se_pisan_ingredientes(ingrediente,tope_ingredientes,personaje->posicion.fil,personaje->posicion.col)){

        soltar_ingrediente(ingrediente, tope_ingredientes, personaje);

    }
}

/*
 *pre: Recibe el movimiento ingresado por el usuario el personaje actual el juego y la posicion de la comida actual.
 *post: Corta el ingrediente.
 */
void cortar_ingredientes(char movimiento, personaje_t personaje, juego_t* juego, int comida_actual){
    int posicion_herramienta = NO_EXISTE;
    int pos_ingrediente_en_mano = NO_EXISTE;

    if(!fuego_esta_activo(*juego,personaje) &&  se_pisan_objetos(juego->herramientas,juego->tope_herramientas, personaje.posicion.fil,personaje.posicion.col)){
        posicion_herramienta = posicion_buscada(juego->herramientas, juego->tope_herramientas, personaje);

        if(juego->herramientas[posicion_herramienta].tipo == CUCHILLO && movimiento == CORTAR &&  personaje.objeto_en_mano != NADA){
            pos_ingrediente_en_mano = posicion_ingrediente(juego->comida[comida_actual].ingrediente ,juego->comida[comida_actual].tope_ingredientes,personaje);
            
            if(ingrediente_es_para_cortar(juego->comida[comida_actual].ingrediente[pos_ingrediente_en_mano].tipo)){
                juego->comida[comida_actual].ingrediente[pos_ingrediente_en_mano].esta_cortado = true;
            }
        }
    }
}

/*
 *pre: Recibe el juego el movimieento ingresado el personaje actual y la posicion de la comida actual.
 *post: Apoya un ingrediente en la mesa si esta vacia  o lo agarra si no tiene nada en las manos.
 */
void pasar_ingredientes(char movimiento, juego_t* juego, personaje_t* personaje, int pos_comida){

    int pos_ingrediente_en_mano =NO_EXISTE;
    int pos_ingrediente_mesa=NO_EXISTE;
    
    if(!fuego_esta_activo(*juego,*personaje) &&  movimiento == PASAR_INGREDIENTE  && personaje->objeto_en_mano == NADA &&
            distancia_manhattan(personaje->posicion.fil, personaje->posicion.col, juego->mesa.fil, juego->mesa.col) == DISTANCIA_VALIDA_MESA  &&
            !esta_mesa_vacia(juego->comida[pos_comida].ingrediente,juego->comida[pos_comida].tope_ingredientes, juego->mesa)){

        pos_ingrediente_mesa = posicion(juego->comida[pos_comida].ingrediente, juego->comida[pos_comida].tope_ingredientes, juego->mesa.fil, juego->mesa.col);
        personaje->objeto_en_mano = juego->comida[pos_comida].ingrediente[pos_ingrediente_mesa].tipo;
        juego->comida[pos_comida].ingrediente[pos_ingrediente_mesa].posicion.fil = personaje->posicion.fil;
        juego->comida[pos_comida].ingrediente[pos_ingrediente_mesa].posicion.col = personaje->posicion.col;

    }else if(!fuego_esta_activo(*juego,*personaje) && movimiento == PASAR_INGREDIENTE && personaje->objeto_en_mano != NADA &&
        distancia_manhattan(personaje->posicion.fil, personaje->posicion.col, juego->mesa.fil, juego->mesa.col) == DISTANCIA_VALIDA_MESA && 
        esta_mesa_vacia(juego->comida[pos_comida].ingrediente,juego->comida[pos_comida].tope_ingredientes, juego->mesa)){

        pos_ingrediente_en_mano = posicion_ingrediente(juego->comida[pos_comida].ingrediente ,juego->comida[pos_comida].tope_ingredientes,*personaje);
        
        personaje->objeto_en_mano = NADA;
        juego->comida[pos_comida].ingrediente[pos_ingrediente_en_mano].posicion.fil = juego->mesa.fil;
        juego->comida[pos_comida].ingrediente[pos_ingrediente_en_mano].posicion.col = juego->mesa.col;

    }
}

/*
 *pre: Recibe el personaje actual el vector de herramientas cargado con su tope definido.
 * post:Verifica si personaje esta a distancia manhattan de alguno de los dos hornos y devuelve true si es el caso o false en caso contrario.
 */
bool es_distancia_permitida_horno(personaje_t personaje, objeto_t herramientas[MAX_HERRAMIENTAS], int tope){
    bool distancia_permitida = false;

    int primera_distancia = NO_EXISTE;
    int segunda_distancia = NO_EXISTE;
    int segunda_posicion = NO_EXISTE;
    int posicion = posicion_horno(herramientas, tope, NO_EXISTE);

    primera_distancia = distancia_manhattan(personaje.posicion.fil, personaje.posicion.col, herramientas[posicion].posicion.fil,
                                            herramientas[posicion].posicion.col);

    if(primera_distancia != DISNTANCIA_VALIDA_HORNO){
        segunda_posicion = posicion_horno(herramientas,tope,posicion);
        segunda_distancia = distancia_manhattan(personaje.posicion.fil, personaje.posicion.col, herramientas[segunda_posicion].posicion.fil,
                                            herramientas[segunda_posicion].posicion.col);
        if(segunda_distancia == DISNTANCIA_VALIDA_HORNO){

            distancia_permitida = true;
        }                                    
    }else{
        distancia_permitida = true;
    }
    return distancia_permitida;

}
/*
 *pre: Recibe el personaje actual el movimiento ingresado el juego y la posicion de la comida actual. 
 * post:Cocina el ingrediente si es carne ,milanesam o masa y si el personaje esta a una distancia manhattan igual a 1 del horno 
 */
void cocinar_ingredientes(personaje_t* personaje, char movimiento,juego_t* juego, int pos_comida ){

    int posicion_ingrediente_mano = NO_EXISTE;

    if(!fuego_esta_activo(*juego,*personaje) &&  movimiento == HORNEAR && personaje->objeto_en_mano != NADA && 
        es_distancia_permitida_horno(*personaje,juego->herramientas, juego->tope_herramientas)){

        posicion_ingrediente_mano = posicion_ingrediente(juego->comida[pos_comida].ingrediente, juego->comida[pos_comida].tope_ingredientes, *personaje);

        if(es_ingrediente_para_cocinar(juego->comida[pos_comida].ingrediente[posicion_ingrediente_mano].tipo)){

            juego->comida[pos_comida].ingrediente[posicion_ingrediente_mano].esta_cocinado = true;
        }
    }
}

/*
 *pre: Recibe el vector de comida lista con su tope igual a 0 y el vector de ingrediente a agregar.
 * post:Carga un ingrediente al plato y suma el tope de comida lista.
 */
void agregar_ingrediente_al_plato(ingrediente_t comida_lista[MAX_INGREDIENTES], int* tope_ingrediente, ingrediente_t ingrediente[MAX_INGREDIENTES], int posicion){

    comida_lista[*tope_ingrediente].tipo = ingrediente[posicion].tipo;
    comida_lista[*tope_ingrediente].posicion.fil = ingrediente[posicion].posicion.fil;
    comida_lista[*tope_ingrediente].posicion.col = ingrediente[posicion].posicion.col;
    comida_lista[*tope_ingrediente].esta_cocinado = ingrediente[posicion].esta_cocinado;
    comida_lista[*tope_ingrediente].esta_cortado = ingrediente[posicion].esta_cortado;
    (*tope_ingrediente)++;
}
/*
 *pre: Recibe el juego el personaje actual y la posicion de la comida actual.
 * post: Carga un ingrediente al plato si el personaje esta sobre la puerta y tiene un ingrediente procesado(cortado o cocinado).
 */
void preparar_plato(juego_t* juego, personaje_t* personaje, int pos_comida){

    int ingrediente = NO_EXISTE;

    if(!fuego_esta_activo(*juego,*personaje) &&  se_pisa_puerta(juego->salida,personaje->posicion.fil, personaje->posicion.col) && 
        personaje->objeto_en_mano != NADA){

        ingrediente = posicion_ingrediente(juego->comida[pos_comida].ingrediente,juego->comida[pos_comida].tope_ingredientes, *personaje);

        if(esta_procesado(juego->comida[pos_comida].ingrediente ,ingrediente)){
            
            juego->comida[pos_comida].ingrediente[ingrediente].posicion.fil = juego->salida.fil;
            juego->comida[pos_comida].ingrediente[ingrediente].posicion.col = juego->salida.col;
            agregar_ingrediente_al_plato(juego->comida_lista, &(juego->tope_comida_lista), juego->comida[pos_comida].ingrediente, ingrediente);
            personaje->objeto_en_mano = NADA;
        }
    }
}

/*
 *pre: Recibe el juego.
 * post: Cambia de receta cuando se termina la anterior dependiendo del precio.
 */
void cambio_de_comida(juego_t* juego){

    if(juego->comida_actual == ENSALADA && juego->tope_comida_lista == CANTIDAD_INGREDIENTES_ENSALADA){

        juego->tope_comida_lista = 0;
        cargar_pizza(juego,COMIDA_PIZZA);
        juego->tope_comida = 2;
        juego->comida_actual = PIZZA;

    }else if(juego->comida_actual == PIZZA && juego->tope_comida_lista == CANTIDADA_INGREIDNETES_PIZZA && juego->precio_total > PRECIO_MINIMO){

        juego->tope_comida_lista = 0;
        cargar_hamburguesa(juego,COMIDA_HAMBURGUESA);
        juego->tope_comida = 3;
        juego->comida_actual = HAMBURGUESA;

    }else if(juego->comida_actual == HAMBURGUESA && juego->tope_comida_lista == CANTIDAD_INGREDIENTES_HAMBURGUESA && juego->precio_total > PRECIO_BASICO){

        juego->tope_comida_lista = 0;
        cargar_sandwich(juego, COMIDA_SANWICH);
        juego->tope_comida = 4;
        juego->comida_actual = SANDWICH;
    }
}
void realizar_jugada(juego_t* juego, char movimiento){

    cambiar_de_personaje(&(juego->personaje_activo), movimiento);
    personaje_t* personaje_actual = personaje(juego->personaje_activo, &(juego->stitch), &(juego->reuben));
    int pos_comida = comida(juego->comida_actual);

    realizar_movimientos(movimiento, personaje_actual, juego);
    cargar_fuego_matafuego(juego, *personaje_actual, movimiento);
    apagar_fuego(personaje_actual,juego , movimiento);
    recolectar_ingredientes(movimiento, personaje_actual, juego->comida[pos_comida].ingrediente,juego->comida[pos_comida].tope_ingredientes,juego);
    cortar_ingredientes(movimiento, *personaje_actual, juego, pos_comida);
    pasar_ingredientes(movimiento, juego, personaje_actual, pos_comida);
    cocinar_ingredientes(personaje_actual,movimiento,juego,pos_comida);
    preparar_plato(juego,personaje_actual,pos_comida);   
    cambio_de_comida(juego);

}


/*
 *pre: Recibe la matriz el tope de paredes = 99 y el vector de paredes cargado.
 * post:Carga cada pared en la matriz.
 */
void cargar_paredes(char restaurante[MAX_FILAS][MAX_COLUMNAS], int tope_paredes , coordenada_t paredes[MAX_PAREDES]){

    for (int i = 0; i < tope_paredes; i++){
        restaurante[paredes[i].fil][paredes[i].col] = PAREDES;
    }
} 

/*
 *pre: Recibe la matriz del terreno el tope de obstaculos definido y el vector de obstaculos cargado.
 * post: Carga los obstaculos (Augeros y/o Fuego) en el terreno.
 */
void cargar_obstaculos(char restaurante[MAX_FILAS][MAX_COLUMNAS], int tope_obstaculos, objeto_t obstaculos[MAX_OBSTACULOS]){

    for (int i = 0; i < tope_obstaculos; i++){
        restaurante[obstaculos[i].posicion.fil][obstaculos[i].posicion.col] = obstaculos[i].tipo;
    }
}

/*
 *pre: Recibe el terreno el vector de herramientas cargado con (hornos y cuchillos y/o matafuego) y su tope definido.
 * post:Carga las herramientas en la matriz en el caso del matafuego lo muestra cuando el personaje no lo tiene en la mano
 */
void cargar_herramientas(char restaurante[MAX_FILAS][MAX_COLUMNAS], int tope, objeto_t herramientas[MAX_HERRAMIENTAS], personaje_t stitch, personaje_t reuben){

    for (int i = 0; i < tope; i++){
        if(herramientas[i].tipo != stitch.objeto_en_mano && herramientas[i].tipo != reuben.objeto_en_mano){
            restaurante[herramientas[i].posicion.fil][herramientas[i].posicion.col] = herramientas[i].tipo;
        }
    }
}

/*
 *pre: Recibe un vector de ingredientes cargado con su tope definido, el terreno y los personajes.
 *post: Carga los ingredientes de la comida ingresada en el terreno si el personaje no los tiene en la mano.
 */
void cargar_ingredientes(char restaurante[MAX_FILAS][MAX_COLUMNAS], ingrediente_t ingrediente[MAX_INGREDIENTES], int tope, personaje_t stitch, personaje_t reuben){

    for (int i = 0; i < tope ; i++){

        if(ingrediente[i].tipo !=  stitch.objeto_en_mano && ingrediente[i].tipo !=  reuben.objeto_en_mano){
            restaurante[ingrediente[i].posicion.fil][ingrediente[i].posicion.col] = ingrediente[i].tipo;
        }
    }
}

/*
 *pre: Recibe el terreno y el juego.
 * post:Carga los ingredientes en el terreno  dependiendo de la comida actual.
 */
void cargar_ingredientes_terreno(char restaurante[MAX_FILAS][MAX_COLUMNAS], juego_t juego){

    if(juego.comida_actual == ENSALADA){
        cargar_ingredientes(restaurante, juego.comida[COMIDA_ENSALADA].ingrediente, juego.comida[COMIDA_ENSALADA].tope_ingredientes, juego.stitch, juego.reuben);
        
    }else if(juego.comida_actual == PIZZA){
        cargar_ingredientes(restaurante, juego.comida[COMIDA_PIZZA].ingrediente, juego.comida[COMIDA_PIZZA].tope_ingredientes, juego.stitch, juego.reuben);

    }else if(juego.comida_actual == HAMBURGUESA){
        cargar_ingredientes(restaurante, juego.comida[COMIDA_HAMBURGUESA].ingrediente, juego.comida[COMIDA_HAMBURGUESA].tope_ingredientes, juego.stitch, juego.reuben);

    }else if(juego.comida_actual == SANDWICH){
        cargar_ingredientes(restaurante, juego.comida[COMIDA_SANWICH].ingrediente, juego.comida[COMIDA_SANWICH].tope_ingredientes, juego.stitch, juego.reuben);
    } 
}
/*
 *pre: Recibe el juego y el terreno.
 * post: carga todos los obstaculos herramientas personajes puerta paredes mesa e ingredientes en el terreno.
 */
void cargar_objetos(juego_t juego,char restaurante[MAX_FILAS][MAX_COLUMNAS]){

    int pos_comida = comida(juego.comida_actual);

    cargar_paredes(restaurante, juego.tope_paredes, juego.paredes);
    cargar_obstaculos(restaurante, juego.tope_obstaculos, juego.obstaculos);
    cargar_herramientas(restaurante, juego.tope_herramientas, juego.herramientas, juego.stitch, juego.reuben);
    cargar_ingredientes_terreno(restaurante, juego);

    restaurante[juego.stitch.posicion.fil][juego.stitch.posicion.col] = juego.stitch.tipo;
    restaurante[juego.reuben.posicion.fil][juego.reuben.posicion.col] = juego.reuben.tipo;

    if(esta_mesa_vacia(juego.comida[pos_comida].ingrediente,juego.comida[pos_comida].tope_ingredientes, juego.mesa)){
        restaurante[juego.mesa.fil][juego.mesa.col] = MESA;
    }
    
    if(juego.reuben.posicion.fil != juego.salida.fil || juego.reuben.posicion.col != juego.salida.col){
        restaurante[juego.salida.fil][juego.salida.col] = PUERTA_DE_SALIDA; 
    }
}

void imprimir_terreno(juego_t juego){

    char restaurante[MAX_FILAS][MAX_COLUMNAS];
    rellenar_matriz(restaurante);
    cargar_objetos(juego,restaurante);
    printf(" ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf(" ┃    ┃ 0 ┃ 1 ┃ 2 ┃ 3 ┃ 4 ┃ 5 ┃ 6 ┃ 7 ┃ 8 ┃ 9 ┃ 10┃ 11┃ 12┃ 13┃ 14┃ 15┃ 16┃ 17┃ 18┃ 19┃ 20┃    ┃\n");
    for(int  i = 0; i < MAX_FILAS; i++){ 
        if (i<10){
        printf(" ┃  %i ┃",i);
        }else{
        printf(" ┃ %i ┃",i);
        }
        for (int j = 0; j < MAX_COLUMNAS; j++){
            printf(" %c ┃", restaurante[i][j]);
        }
        if (i<10){
        printf(" %i  ┃",i);
        }else{
        printf(" %i ┃",i);
        }
        printf("\n");
    }
    printf(" ┃    ┃ 0 ┃ 1 ┃ 2 ┃ 3 ┃ 4 ┃ 5 ┃ 6 ┃ 7 ┃ 8 ┃ 9 ┃ 10┃ 11┃ 12┃ 13┃ 14┃ 15┃ 16┃ 17┃ 18┃ 19┃ 20┃    ┃\n");
    printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

}


int estado_juego(juego_t juego){

    personaje_t personaje = personaje_actual(juego.personaje_activo, juego.stitch, juego.reuben);
    int posicion = posicion_buscada(juego.obstaculos, juego.tope_obstaculos,personaje);



    if(se_pisan_objetos(juego.obstaculos,juego.tope_obstaculos,personaje.posicion.fil,personaje.posicion.col) && juego.obstaculos[posicion].tipo == AGUJEROS){
        printf("ESTADO DE JUEGO : -1\n");
        printf("PERDISTE :(\n");
        return PERDIDO;
    }else if(es_juego_ganado(juego)){
        
        printf("ESTADO DE JUEGO : 1\n");
        printf("GANASTE!!\n");
        return GANADO;
    }else{
        printf("ESTADO DE JUEGO : 0\n");
        return JUGANDO;
    }
}
