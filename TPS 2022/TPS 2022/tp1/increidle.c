#include<stdio.h>

const char PRIMERA_OPCION_CODIGO='A';
const char SEGUNDA_OPCION_CODIGO='B';
const char TERCERA_OPCION_CODIGO='C';
const char CUARTA_OPCION_CODIGO='D';
const char STTICH ='A';
const char PEZ='B';
const char PATO='C';
const char AURELIO='D';
const char ZAFIRO ='A';
const char ABU='B';
const char RAJAH='C';
const char JAFAR ='D';
#define MAX_NUMEROS 5
#define MAX_DIGITOS 5
const int  MAX_DIVISORES = 2;
const int  CIFRA_MAXIMA = 100;
const int  CIFRA_MINIMA = 1;
const char DIGITO_NUMEROS = 'O';

const char NUMERO_MAX = 100;
const char NUMERO_MIN = 1;
const int MAX_NUMEROS_PRIMOS=5;
const int INICIAL_DE_RAYO= 95;

const char DIGITO_MASCOTAS ='R';
const char DIGITO_FELINO= 'S';
const char DIGITO_CODIGO='K';
const char DIGITO_RAYO='N';
const char DIGITO_NUMEROS_PRIMOS= 'O';
const char RESPUESTA_INCORRECTA='X';

const int PRIMER_CODIGO = 3312;
const int SEGUNDO_CODIGO = 3317;
const int TERCER_CODIGO = 2312;
const int CUARTO_CODIGO = 2031;


/*
 *pre-condiciones: se deben ingresar A,B,C o D en mayuscula para poder continuar con el cuestionario.
 *post-condiciones:  verifica que la opcion ingresada cumpla con las precondiciones y guarda la opcion ingresada.
 */

void pedir_codigo_de_emergencia(char *opcion){
   
    printf("cual es el codigo de emergencia usado por Monsters Inc.cuando uno de los personajes tiene una media humana pegada al cuerpo seleccione :\n "
    "A para 3312 \n B para 3317\n C para 2312 \n D para 2031\n PONER EN MAYUSCULA PORFAVOR\n ");
    scanf(" %c",opcion);

    while(!(*opcion== PRIMERA_OPCION_CODIGO || *opcion== SEGUNDA_OPCION_CODIGO|| *opcion==TERCERA_OPCION_CODIGO|| *opcion== CUARTA_OPCION_CODIGO)){
    printf("la opcion ingresada es incorrecta ,Seleccione:\n  A para 3312\n  B para 3317\n  C para 2312\n  D para 2031 \n");
    scanf(" %c",opcion);
    }
 

}


/*
 *pre-condiciones: recibe un codigo.
 *post-condiciones: asigna codigos a las diferentes obciones.
 */
void calcular_codigo(char opcion,int* codigo){
    if(opcion==PRIMERA_OPCION_CODIGO){
        *codigo = PRIMER_CODIGO; 
    }else if( opcion == SEGUNDA_OPCION_CODIGO){
        *codigo = SEGUNDO_CODIGO;
    }else if( opcion== TERCERA_OPCION_CODIGO){
        *codigo= TERCER_CODIGO;
    }else{
        *codigo= CUARTO_CODIGO;
    }
    
}


/*
 *pre-condiciones: se deben ingresar A,B,C o D en mayuscula para poder continuar con el cuestionario.
 *post-condiciones: verifica que la opcion ingresada cumpla con las precondiciones y guarda la opcion ingresada.
 */
void preguntar_mascotas(char* opcion_mascota){
   do{
    printf("cual es el nombre del pez mascota de lilo ingrese :\n A para sttich\n B para pez\n C para pato\n D para aurelio\n PONER EN MAYUSCULA POR FAVOR\n");
    scanf(" %c",opcion_mascota);

   }while(!( *opcion_mascota == STTICH || *opcion_mascota == PEZ|| *opcion_mascota == PATO|| *opcion_mascota == AURELIO));
    


}


/*
 *pre-condiciones: recibe una opcion.
 *post-condiciones: asigna una mascota a cada opcion.
 */
void definir_mascota(char* mascota, char opcion_mascota){
    if(opcion_mascota== STTICH){
        *mascota= STTICH;
    }else if(opcion_mascota==PEZ){
        *mascota= PEZ;
    }else if( opcion_mascota==PATO){
        *mascota= PATO;
    }else{
        *mascota= AURELIO;
    }
  
}

/*
 *pre-condiciones: los numeros ingresados deben estan dentro del rango de no ser menores o iguales a 1 y mayores o iguales  a 100.
 *post-condiciones:  pide 5 numeros primos,calcula cuantos numeros primos se ingresaron y cuantos compuestos Y devuelve la cantidad de 
 *                   numeros primos que se ingresaron.
 */

void pedir_numeros_primos(int numeros[MAX_NUMEROS],int tope_numeros,int* contador, int* numeros_primos, int* numeros_compuestos,int* cantidad){

   
    for (int i = 0; i < tope_numeros; i++){ 
        *contador=0;
        printf(" INGRESE 5 NUMEROS PRIMOS :\n");
        scanf("%i",&numeros[i]);
        for (int j = 1; j <= numeros[i]; j++){ 
            if((numeros[i] % j)== 0){
                (*contador)++;
            }
        }

        while(numeros[i] < NUMERO_MIN || numeros[i] > NUMERO_MAX){
            printf("EL NUMERO INGRESADO ES INVALIDO,INGRESE OTRA VEZ :\n");
            scanf("%i",&numeros[i]);
                *contador=0;
            for (int j = 1; j <= numeros[i]; j++){
                if((numeros[i] % j)== 0){
                    (*contador)++;
                }
            }
        }
            if(*contador != MAX_DIVISORES){
                (*numeros_compuestos) = numeros[i];  
              
            }else{
                (*numeros_primos) = numeros[i];
            
               
                (*cantidad)++;
            }    
          
    }
    
      
}

/*
 *pre-condiciones: el numero ingresado debe ser mayor a 1 y menor a 100.
 *post-condiciones: pide un numero ,verifica que el numero ingresado cumpla las condiciones y los guarda.
 */
void pedir_numero_de_rayo(int* numero){

        printf("ingrese el numero que lleva Rayo MaQueen,dentro del rango de 1 entre 100\n");
        scanf("%i",numero);

    while(*numero < NUMERO_MIN  || *numero> NUMERO_MAX){
        printf("la opcion es incorrecta ,ingrese el numero que lleva Rayo MaQueen\n");
        scanf("%i",numero);

    }


}


/*
 *pre-condiciones: se debe seleccionar A,B,C o D en mayuscula.
 *post-condiciones: pide que seleccione una opcion ,verifica que cumpla con las precondiciones y la guarda.
 */
void preguntar_nombre(char* opcion_felino){

        printf("como se llama el tigre de la princesa jasmin seleccione:\n A para ZAFIRO\n B para ABU\n C para RAJAH\n D para JAFAR\n PONER EN MAYUSCULA POR FAVOR\n");
        scanf(" %c",opcion_felino);

    while(!(*opcion_felino == ZAFIRO || *opcion_felino == ABU|| *opcion_felino == RAJAH || *opcion_felino == JAFAR)){
        printf("la opcion es incorrecta ,seleccione\n  A para ZAFIRO\n  B para ABU\n  C para RAJAH\n  D para JAFAR\n  PONER EN MAYUSCULA PORFAVOR\n");
        scanf(" %c",opcion_felino);

    }

}

/*
 *pre-condiciones: recibe un nombre.
 *post-condiciones: asigna un nombre a cada una de las diferentes opciones.
 */
void verificar_nombre(char opcion_felino,char* nombre){

    if(opcion_felino== ZAFIRO){
     *nombre= ZAFIRO;

    }else if(opcion_felino== ABU){
        *nombre= ABU;
    }else if(opcion_felino== RAJAH){
        *nombre= RAJAH;
    }else{
        *nombre= JAFAR;
    }

}

/*
 *pre-condiciones: recibe un codigo.
 *post-condiciones: define la opcion del codigo correcto y los incorectos y devielve la respuesta correspondiente.
 */

char respuesta_digito(int codigo,char* respuesta_codigo){

    if(codigo == PRIMER_CODIGO){
        *respuesta_codigo=DIGITO_CODIGO;
    }else{
        *respuesta_codigo = RESPUESTA_INCORRECTA;
    }
    return *respuesta_codigo;
}   

/*
 *pre-condiciones: recibe una mascota.
 *post-condiciones: definene la opcion de mascota correcta y las incorrectas devolviendo la respuesta correspondiente.
 */
char respuesta_digito_mascota(char mascota,char* respuesta_mascota){

    if(mascota== PATO){
        *respuesta_mascota= DIGITO_MASCOTAS;
    }else{
        *respuesta_mascota= RESPUESTA_INCORRECTA;

    }
    return *respuesta_mascota;
}

/*
 *pre-condiciones: recibe la cantidad de numeros primos.
 *post-condiciones: compara la cantidad de numeros primos guardada con la cantidad total de numeros y define la respuesta correcta y 
 *                   devuelve la respuesta correspondiente.
 */
char respuesta_digito_numeros_primos(int cantidad,char* respuesta_numeros_primos){

    if (cantidad == MAX_NUMEROS_PRIMOS){
      *respuesta_numeros_primos= DIGITO_NUMEROS_PRIMOS;
    }else {
      *respuesta_numeros_primos= RESPUESTA_INCORRECTA;
    }
    return *respuesta_numeros_primos;
}


/*
 *pre-condiciones: recibe un numero.
 *post-condiciones: define el numero correcto de rayo mcqueen y lo devuelve.
 */
char respuesta_digito_rayo(int numero,char* respuesta_numero){

    if(numero== INICIAL_DE_RAYO){
        *respuesta_numero=DIGITO_RAYO;
    }else{
        *respuesta_numero= RESPUESTA_INCORRECTA; 
    }
    return *respuesta_numero;
} 

/*
 *pre-condiciones: recibe un nombre.
 *post-condiciones: define la opcion correcta y las incorectas devolviendo la respuesta correspondiente.
 */
char respuesta_digito_felino(char nombre,char* respuesta_felino){

    if(nombre== RAJAH){
        *respuesta_felino= DIGITO_FELINO;
    }else{
        *respuesta_felino= RESPUESTA_INCORRECTA;
    }
    return *respuesta_felino;
}

/*
 *pre-condiciones: recibe todas las respuestas a las preguntas hechas.
 *post-condiciones: muesta por pantalla la contraseña correspondiente a las respuestas guardadas.
 */
void calcular_resultados(char digitos[MAX_DIGITOS],int tope_digitos,char respuesta_codigo, char respuesta_mascota,char respuesta_numeros_primos,
                        char respuesta_numero,char respuesta_felino){
        digitos[0] = respuesta_codigo;
        digitos[1] = respuesta_mascota;
        digitos[2] = respuesta_numeros_primos;
        digitos[3] = respuesta_numero;
        digitos[4] = respuesta_felino;                        

    for (int i = 0; i < tope_digitos; i++){
        printf("con las letras reveladas la contraseña obtenida es -%c%c%c%c%c%c-\n",digitos[0],digitos[1],digitos[2],digitos[3],digitos[2],digitos[4]);
    }
                        
}

int main(){

    
    char opcion= ' ';
    int codigo=0;
    char opcion_mascota=' ';
    char mascota=' ';
    int numeros[MAX_NUMEROS];
    int tope_numeros=5;
    int contador=0;
    int numero=0;
    int numeros_compuestos=0;
    int numeros_primos =0;
    int cantidad=0;
    char opcion_felino=' ';
    char nombre=' ';
    char respuesta_codigo =' ';
    char respuesta_mascota=' ';
    char respuesta_numeros_primos=' ';
    char respuesta_numero=' ';
    char respuesta_felino=' ';
    char digitos[MAX_DIGITOS];
    int tope_digitos=1;
  
    pedir_codigo_de_emergencia(&opcion);
    calcular_codigo(opcion,&codigo);
    preguntar_mascotas(&opcion_mascota);
    definir_mascota(&mascota,opcion_mascota);
    pedir_numeros_primos(numeros,tope_numeros,&contador,&numeros_primos,&numeros_compuestos,&cantidad);
    pedir_numero_de_rayo(&numero);
    preguntar_nombre(&opcion_felino);
    verificar_nombre(opcion_felino,&nombre);
    respuesta_digito( codigo, &respuesta_codigo);
    respuesta_digito_mascota(mascota, &respuesta_mascota);
    respuesta_digito_numeros_primos(cantidad,&respuesta_numeros_primos);
    respuesta_digito_rayo( numero, &respuesta_numero);
    respuesta_digito_felino(nombre,&respuesta_felino);
    calcular_resultados( digitos, tope_digitos,respuesta_codigo,respuesta_mascota,respuesta_numeros_primos,respuesta_numero,respuesta_felino);
    return 0;
}