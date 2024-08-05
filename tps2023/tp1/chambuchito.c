#include <stdio.h>
#include <stdbool.h>

const int MEDIDA_MINIMA = 15;
const int MEDIDA_MAXIMA = 30;
const int PRECIO_BASICO = 5;
const int PRECIO_ESPECIAL = 8;
const int PRECIO_ROAF_BEEF = 7;
const int PRECIO_ATUN = 9;
const int PRECIO_POLLITO = 5;
const int PRECIO_SOJA = 3;
const int SIN_PRECIO =0;
const float VALOR_NUMERICO = 0.3f;
const char PAN_BLANCO = 'B';
const char PAN_INTEGRAL = 'I';
const char AVENA_Y_MIEL = 'A';
const char QUESO_Y_OREGANO = 'Q';
const char QUESO_DAMBO = 'D';
const char QUESO_CHEDDAR = 'C';
const char QUESO_GRUYERE = 'G';
const char SIN_QUESO = 'S';
const char ROAST_BEEF = 'R';
const char ATUN = 'A';
const char SOJA = 'S';
const char POLLITO = 'P';
const char NADA_DE_PROTE = 'N';
const char SI = 'S';
const char NO = 'N';


/*
 * pre-condiciones: Recibe una medida ingresda por el usuario.
 * post-condiciones: Verifica si la medida recibida se encuentra entre el rango de valores 15 a 30(inclusive),devolviendo verdadero en caso afirmativo o
 *                   falso en caso contrario.
 */
bool es_medida_correcta(int medida_chambuchito){
    return ( medida_chambuchito >= MEDIDA_MINIMA && medida_chambuchito <= MEDIDA_MAXIMA );
}
/*
 * pre-condiciones: -
 * post-condiciones: Pide al usuario una medida y la guarda.
 */
void preguntar_medida(int* medida_chambuchito){
    
    printf("  ______________________________________________\n");
    printf(" |                                              |\n");
    printf(" | ¿De que medida desea su Chambuchito?         |\n");
    printf(" | Las medidas van de 15 cm a 30 cm (incluidos) |\n");
    printf(" |______________________________________________|\n");
    scanf("%i",medida_chambuchito);
    while(!es_medida_correcta(*medida_chambuchito)){ 
        printf("  _____________________________________________________\n");
        printf(" |                                                     |\n");
        printf(" | La medida ingresada no se encuentra en el rango     |\n");
        printf(" | Ingrese una medida entre 15 cm a 30 cm  (incluidos) |\n");
        printf(" |_____________________________________________________|\n");
        scanf("%i",medida_chambuchito);
    }
}
/*
 * pre-condiciones: Recibe una variable cargada.
 * post-condiciones: Verifica si la variable es alguna de las opciones,devolviendo verdadero en caso afirmativo o falso en caso contrario.
 */
bool es_pan_correcto(char tipo_pan){
    return( tipo_pan == PAN_BLANCO || tipo_pan == PAN_INTEGRAL || tipo_pan == AVENA_Y_MIEL || tipo_pan == QUESO_Y_OREGANO );
}
/*
 * pre-condiciones: -
 * post-condiciones: Pide al usuario un tipo de pan y lo guarda.
 */
void preguntar_tipo_pan(char* tipo_pan){
    
    printf("  __________________________________________________\n");
    printf(" |                                                  |\n");
    printf(" | ¿Que tipo de pan quiere para su Chambuchito? |\n");
    printf(" | [B] para Blanco                                  |\n");
    printf(" | [I] para Integral                                |\n");
    printf(" | [A] para Avena y Miel                            |\n");
    printf(" | [Q] para Queso y Oregano                         |\n");
    printf(" |__________________________________________________|\n");
    scanf(" %c",tipo_pan);
    while(!es_pan_correcto(*tipo_pan)){
        printf("  _______________________________________________________\n");
        printf(" |                                                        |\n");
        printf(" | La opcion seleccionada es invalida,Ingrese nuevamente: |\n");
        printf(" | [B] para Blanco                                        |\n");
        printf(" | [I] para Integral                                      |\n");
        printf(" | [A] para Avena y Miel                                  |\n");
        printf(" | [Q] para Queso y Oregano                               |\n");
        printf(" |________________________________________________________|\n");
        scanf(" %c",tipo_pan);
    }
}
/*
 * pre-condiciones: Recibe el tipo de queso cargado con ( D,C,G o S).
 * post-condiciones: Verifica que la variable sea alguna de las opciones ,devolviendo verdadero si es una opcion o falso si no es ninguna.
 */
bool es_queso_correcto(char tipo_queso){
    return(tipo_queso == QUESO_DAMBO || tipo_queso == QUESO_CHEDDAR || tipo_queso == QUESO_GRUYERE || tipo_queso == SIN_QUESO);
}
/*
 * pre-condiciones: -
 * post-condiciones: Pregunta al usuario el tipo de queso ,Verifica que cumpla las condiciones y la guarda.
 */
void preguntar_tipo_queso(char* tipo_queso){
    printf("  ________________________________________________\n");
    printf(" |                                                |\n");
    printf(" | ¿Que tipo de queso quiere para su Chambuchito? |\n");
    printf(" | [D] para Dambo                                 |\n");
    printf(" | [C] para Cheddar                               |\n");
    printf(" | [G] para Gruyere                               |\n");
    printf(" | [S] Sin Queso                                  |\n");
    printf(" |________________________________________________|\n");
    scanf(" %c",tipo_queso);
    while(!es_queso_correcto(*tipo_queso)){
        printf("  _______________________________________________________\n");
        printf(" |                                                        |\n");
        printf(" | La opcion seleccionada es invalida,Ingrese nuevamente: |\n");
        printf(" | [D] para Dambo                                         |\n");
        printf(" | [C] para Cheddar                                       |\n");
        printf(" | [G] para Gruyere                                       |\n");
        printf(" | [S] Sin Queso                                          |\n");
        printf(" |________________________________________________________|\n");
        scanf(" %c",tipo_queso);
    }
}
/*
 * pre-condiciones: Recibe el tipo de proteina cargada con (R,A,S,P o N)..
 * post-condiciones: Verifica que sea alguna de las opciones  devuelviendo verdadero o falso  en caso contrario  
 */
bool es_proteina_correcta(char proteina){
    return (proteina == ROAST_BEEF || proteina == ATUN || proteina == SOJA || proteina == POLLITO || proteina == NADA_DE_PROTE);
}
/*
 * pre-condiciones: -
 * post-condiciones: Pide al usuario un tipo de proteina ,verificando que cumpla la condicion y la guarda.
 */

void preguntar_proteina(char* proteina){

    printf("  __________________________________________________\n");
    printf(" |                                                  |\n");
    printf(" | ¿Que tipo de proteina desea para su Chambuchito? |\n");
    printf(" | [R] para Roast Beef                              |\n");
    printf(" | [A] para Atun                                    |\n");
    printf(" | [S] para Soja                                    |\n");
    printf(" | [N] Nada de Prote                                |\n");
    printf(" |__________________________________________________|\n");
    scanf(" %c",proteina);
    while(!es_proteina_correcta(*proteina)){
        printf("  ________________________________________________________\n");
        printf(" |                                                        |\n");
        printf(" | La opcion seleccionada es invalida,Ingrese nuevamente: |\n");
        printf(" | [R] para Roast Beef                                    |\n");
        printf(" | [A] para Atun                                          |\n");
        printf(" | [S] para Soja                                          |\n");
        printf(" | [N] Nada de Prote                                      |\n");
        printf(" |________________________________________________________|\n");
        scanf(" %c",proteina);
    }
}
/*
 * pre-condiciones: Recibe un tipo de proteina que puede ser (R,A,S,P o N).
 * post-condiciones: devuelve verdadero si la variable coincide con la proteina o falso en caso contrario.
 */
bool es_proteina_atun(char tipo_prote){
    return (tipo_prote == ATUN);
}
/*
 * pre-condiciones: Recibe una variable cargada con S o N.
 * post-condiciones: devuelve verdadero si la variable es alguna de las opciones o falso en caso contrario.
 */
bool es_estado_correcto(char respuesta){
    return ( respuesta == SI || respuesta == NO);
}
/*
 * pre-condiciones: Recibe un estado de chambuchito inicializado y un tipo de proteina  cargado con (R,A,S,P o N) .
 * post-condiciones: verifica que la proteina no se atun y hace la pregunta del estado del chambuchito,caso contrario no pregunta nada. 
 */
void preguntar_estado_chambuchito(char* estado,char proteina){

    if(!es_proteina_atun(proteina)){
        printf("  _______________________________________\n");
        printf(" |                                       |\n");
        printf(" |  ¿Desea su chambuchito caliente o no? |\n");
        printf(" |  Responda con:                        |\n");
        printf(" |  (S) para Si                          |\n");
        printf(" |  (N) para No                          |\n");
        printf(" |_______________________________________|\n");
        scanf(" %c",estado);
        while (!es_estado_correcto(*estado)){
            printf("  _________________________________________\n");
            printf(" |                                         |\n");
            printf(" | La respuesta no esta entre las opciones |\n");
            printf(" | Responda con:                           |\n");
            printf(" | (S) para Si                             |\n");
            printf(" | (N) para No                             |\n");
            printf(" |_________________________________________|\n");
            scanf(" %c",estado);
        }
    }
}
/*
 * pre-condiciones: Recibe el tipo de pan que puede ser (B I A o Q).
 * post-condiciones: Segun el tipo de pan devuelve un precio.
 */
int precio_pan(char pan){

    if(pan == PAN_INTEGRAL || pan == PAN_BLANCO){
        return PRECIO_BASICO;
    }else{
        return PRECIO_ESPECIAL;
    }
}
/*
 * pre-condiciones: Recibe un tipo de queso que puede ser (D,C,G o S).
 * post-condiciones: Segun el tipo de queso devuelve un precio.
 */
int precio_queso(char queso){

    if(queso == QUESO_DAMBO || queso == QUESO_CHEDDAR){
        return PRECIO_BASICO;

    }else if(queso == QUESO_GRUYERE){
        return PRECIO_ESPECIAL;

    }else{
        return SIN_PRECIO;
    }
}
/*
 * pre-condiciones: Recibe un tipo de proteina que puede ser (R,A,S,P o N).
 * post-condiciones: Segun la proteina devuelve un precio.
 */
int precio_proteina(char proteina){

    if(proteina == ROAST_BEEF){
        return PRECIO_ROAF_BEEF;

    }else if(proteina == ATUN){
        return PRECIO_ATUN;

    }else if(proteina == SOJA){
        return PRECIO_SOJA;

    }else if(proteina == POLLITO){
        return PRECIO_POLLITO;

    }else{
        return SIN_PRECIO;
    }
}
/*
 * pre-condiciones: Recibe los tipos de ingredientes cargados y la medida que esta entre 15 y 30 incluidos.
 * post-condiciones: Llama a las funciones que calculan los precios de cada ingrediente, Calcula y devuelve el precio total de chambuchito > 0.
 */
int precio_total(int medida ,char tipo_pan,char tipo_proteina, char tipo_queso){

    int valor_pan = precio_pan(tipo_pan);
    int valor_queso = precio_queso(tipo_queso);
    int valor_prote = precio_proteina(tipo_proteina);
    float valor_medida = (float)medida * VALOR_NUMERICO;
    float total_ingredientes =  (float)(valor_pan + valor_prote + valor_queso);

    return ( (int)(valor_medida * total_ingredientes) );
}
/*
 * pre-condiciones: Recibe el precio total del chambuchito que es > 0.
 * post-condiciones: Muestra por pantalla el precio del chambuchito.
 */
void mostrar_precio_total(int total){
    
    printf("  ___________________________________________\n");
    printf(" |                                           |\n");
    printf(" |  El precio de su chambuchito es:   -%i-   |\n",total);
    printf(" |___________________________________________|\n\n");
}
int main(){

    int medida_chambuchito = 0;
    char tipo_pan = ' ';
    char tipo_queso = ' ';
    char tipo_proteina = ' ';
    char estado_chambuchito = ' ';
    int total = 0;
    preguntar_medida(&medida_chambuchito);
    preguntar_tipo_pan(&tipo_pan);
    preguntar_tipo_queso(&tipo_queso);
    preguntar_proteina(&tipo_proteina);
    preguntar_estado_chambuchito(&estado_chambuchito,tipo_proteina);
    total = precio_total(medida_chambuchito,tipo_pan,tipo_proteina,tipo_queso);
    mostrar_precio_total(total);
    
    return 0;
}