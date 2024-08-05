import gestionar_reservas
import sys


COMANDO_AGREGAR = "agregar"
COMANDO_MODIFICAR = "modificar"
COMANDO_ELIMINAR = "eliminar"
COMANDO_LISTAR = "listar"

ARGUMENTOS_PARA_AGREGAR = 6
ARGUMENTOS_PARA_MODIFICAR = 3
ARGUMENTOS_PARA_ELIMINAR = 3
ARGUMENTOS_PARA_LISTAR = 2
MAX_ARGUMENTOS_PARA_LISTAR = 4

POSICION_COMANDO =1
POSICION_INVITADOS =3
POSICION_HORA = 4
POSICION_UBICACION = 5
POSICION_NOMBRE = 2
POSICION_ID=2
POSICION_SEGUNDO_ID =3

def main():
    if sys.argv[POSICION_COMANDO] == COMANDO_AGREGAR:

        if len(sys.argv) == ARGUMENTOS_PARA_AGREGAR:
            gestionar_reservas.pasos_para_agregar(sys.argv[POSICION_NOMBRE],sys.argv[POSICION_INVITADOS],sys.argv[POSICION_HORA],sys.argv[POSICION_UBICACION])
        else:
            gestionar_reservas.cantidad_incorrecta_de_argumentos(len(sys.argv),COMANDO_AGREGAR,ARGUMENTOS_PARA_AGREGAR)
            
    elif sys.argv[POSICION_COMANDO] == COMANDO_MODIFICAR:
        
        if len(sys.argv) == ARGUMENTOS_PARA_MODIFICAR:
            gestionar_reservas.pasos_para_modificar(sys.argv[POSICION_ID])
        else:
            gestionar_reservas.cantidad_incorrecta_de_argumentos(len(sys.argv),COMANDO_MODIFICAR,ARGUMENTOS_PARA_MODIFICAR)
        
    elif sys.argv[POSICION_COMANDO] == COMANDO_ELIMINAR:
        
        if len(sys.argv) == ARGUMENTOS_PARA_ELIMINAR:
            gestionar_reservas.pasos_para_eliminar(sys.argv[POSICION_ID])
        else:
            gestionar_reservas.cantidad_incorrecta_de_argumentos(len(sys.argv),COMANDO_ELIMINAR,ARGUMENTOS_PARA_ELIMINAR)
        
    elif sys.argv[POSICION_COMANDO] == COMANDO_LISTAR:
        
        if len(sys.argv) == MAX_ARGUMENTOS_PARA_LISTAR:
            
            gestionar_reservas.pasos_para_listar(sys.argv[POSICION_ID],sys.argv[POSICION_SEGUNDO_ID])
            
        elif len(sys.argv) == ARGUMENTOS_PARA_LISTAR:
            
            gestionar_reservas.listar_todas_las_reservas()

        elif len(sys.argv) > MAX_ARGUMENTOS_PARA_LISTAR:
            print("hay demasiados argumentos para listar")
        else:
            print("no hay sufientes argumentos para listar")
    else:
        print("ingrese alguna accion valida : agregar , eliminar modificar o listar")
main()    
    