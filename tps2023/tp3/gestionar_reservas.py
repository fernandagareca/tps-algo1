import csv
import os


CANTIDAD_INVALIDA_DE_PERSONAS =0
ID_MINIMO = 1
MAXIMO_HORAS = 23
MINIMO_HORAS = 00
MINIMO_MINUTOS = 00
MAXIMO_MINUTOS = 60
AFUERA = "F"
ADENTRO ="D"
UBICACION_AFUERA = "afuera"
UBICACION_ADENTRO = "adentro"
ARCHIVO_PRINCIPAL = "archivo.csv"
ARCHIVO_AUXILIAR = "aux.csv"
LEER ="r"
ESCRIBIR ="w"
NOMBRE = "nombre"
CANTIDAD = "cantidad"
HORA = "hora"
UBICACION = "ubicacion"
HORAS = 0
MINUTOS =1
LARGO_MINUTOS = 2
LARGO_HORAS = 2
LIMITADOR_LECTURA = ";"
LIMITADOR_ESCRITURA = ";"
SEPARADOR_HORARIO =":"
POSICION_ID =0
POSICION_NOMBRE =1
POSICION_HORARIO =3
POSICION_INVITADOS = 2
POSICION_UBICACION= 4
CAMPO_MODIFICABLE =0
DATO_NUEVO=1

#pre: Recibe  un string.
#post: Devuelve false en el caso que el string no se pueda convertir a un entero o si es menor o igual a 0.
def es_id_valido(id):
    
    id_valido = True
    
    if not id.isnumeric() :
        
        id_valido= False
        print(f"El ID: {id} no es valido")
    elif int(id) < ID_MINIMO:   
        print(f"El ID: {id} no es valido, debe ser un numero mayor a 0")
        
        id_valido = False
        
    return id_valido

#pre: Recibe un string.
#post: Devuelve false en el caso que el string no se pueda convertir a un entero o si es menor o igual a 0.
def es_cantidad_personas_correcta(cantidad_personas):
    
    cantidad_valida= True
    
    if  not  cantidad_personas.isnumeric() or int(cantidad_personas) == CANTIDAD_INVALIDA_DE_PERSONAS:
        
        print(f"La cantidad de personas:{cantidad_personas} no es valida,debe ser un numero mayor a 0")
        cantidad_valida = False

    return cantidad_valida

#pre:Recibe un string.
#post: Verifica si la hora y los minutos coinciden con el formato de la hora y minutos (XX:XX) ,Devuelve false si no se cumple.
def es_formato_correcto(horario):
    
    partes_horario = horario.split(":")
    
    horario_valido = True
    if not SEPARADOR_HORARIO in horario:
        horario_valido = False
        print("El formato del horario es incorrecto, deveria ser XX:XX")
        return horario_valido
    
    if len(partes_horario[HORAS]) < LARGO_HORAS or len(partes_horario[HORAS]) > LARGO_HORAS:
        
        print(f"El formato de la hora : {partes_horario[HORAS]} no es valido, deberia ser: XX:XX")
        horario_valido= False
    
    if len(partes_horario[MINUTOS]) < LARGO_MINUTOS or len(partes_horario[MINUTOS]) > LARGO_MINUTOS:
        print(f"El formato de los minutos : {partes_horario[MINUTOS]} no es valido, deveria ser: XX:XX")
        horario_valido= False
    return horario_valido

#pre:recibe un string.
#post: Devuelve false si el formato del horario es incorrecto o si los minutos se sale del rango (00 a 59) o si la hora  se sale del rango (00 a 23).
def es_horario_correcto(horario):
    
    partes_horario = horario.split(":")
    horario_valido = True
    
    if not es_formato_correcto(horario):
        horario_valido = False
        return horario_valido
    
    if  not partes_horario[HORAS].isnumeric() and not partes_horario[MINUTOS].isnumeric():
        print(f"La hora: {partes_horario[HORAS]} no es valida y los minutos: {partes_horario[MINUTOS]} no son validos")
        horario_valido = False
        return horario_valido
    elif not partes_horario[HORAS].isnumeric():
        print(f"La hora : {partes_horario[HORAS]} no es valida")
        horario_valido = False
        return horario_valido
    elif not partes_horario[MINUTOS].isnumeric():
        print(f"Los minutos {partes_horario[MINUTOS]} no son validos")
        horario_valido = False
        return horario_valido
    
    else:
    
        if int(partes_horario[HORAS]) < MINIMO_HORAS or int(partes_horario[HORAS]) > MAXIMO_HORAS:
            print(f"La hora: {partes_horario[HORAS]} no es valida debe estar en el rango de 00 a 23")
            horario_valido = False
        
        elif int(partes_horario[MINUTOS]) < MINIMO_MINUTOS or int(partes_horario[MINUTOS]) > MAXIMO_MINUTOS:
            print(f"Los minutos: {partes_horario[MINUTOS]} no son validos debe estar en el rango de 00 a 60")
            horario_valido = False
        
    return horario_valido    

#pre: Recibe un string.
#post: Devuelve false si la ubicacion no es F ni D.
def es_ubicacion_correcta(ubicacion):
    
    ubicacion_valida = True
    if  not (ubicacion == AFUERA) and not(ubicacion == ADENTRO):
        print(f"La ubicacion :{ubicacion} no es valida debe ingresar D(adentro) o F(afuera)")
        ubicacion_valida = False
    
    return ubicacion_valida

#pre: Recibe un string ,la cantidad de personas que es un entero positivo, el horario con el formato (XX:XX) entre 00:00 y 23:59 y la ubicacion (F o D). 
#post: Agrega una reserva al final del archivo con id ascendente.
def agregar_reserva(nombre, cantidad_personas, horario, ubicacion):
        
    try:
        archivo_reservas = open(ARCHIVO_PRINCIPAL,LEER)
        print("Se abrio con exito el archivo")
    except:
        return 
        
    try:
        archivo_auxiliar= open(ARCHIVO_AUXILIAR,ESCRIBIR)
        print("Se abrio con exito el archivo auxiliar ")
    except:
        print("No se pudo abrir el archivo aux")
        archivo_reservas.close()
        return
    
    lectura = csv.reader(archivo_reservas, delimiter = LIMITADOR_LECTURA)
    escritura = csv.writer(archivo_auxiliar,delimiter= LIMITADOR_ESCRITURA)
    id=0
    
    for linea in lectura:
        escritura.writerow(linea)
        id = linea[POSICION_ID]
    
    reserva_a_agregar = [int(id)+1, nombre, cantidad_personas, horario, ubicacion]
    escritura.writerow(reserva_a_agregar)
    print("La reserva fue agregada!!")
            
    archivo_reservas.close()
    archivo_auxiliar.close()
    os.rename(ARCHIVO_AUXILIAR,ARCHIVO_PRINCIPAL)
    return True

#pre:  Recibe un string ,la cantidad de personas que es un entero positivo, el horario con el formato (XX:XX) entre 00:00 y 23:59 y la ubicacion (F o D).
#post: Crea un archivo de reservas y agrega una reserva.

def crear_lista_de_reservas(nombre, cantidad_personas, horario, ubicacion):
    
    try:
        archivo_reservas = open(ARCHIVO_PRINCIPAL, ESCRIBIR)
        print("Se abrio con exito el archivo")
    except:
        print("No se pudo abrir el archivo")
        return 
    
    escritura = csv.writer(archivo_reservas,delimiter= LIMITADOR_ESCRITURA)
    
    reserva_a_agregar = [ID_MINIMO, nombre, cantidad_personas, horario, ubicacion]
    escritura.writerow(reserva_a_agregar)
    print("La reserva fue agregada!!")
    
    
    archivo_reservas.close()

#pre: Recibe dos estrigs.
#post: Devuelve false si el tipo de dato lo es no es CANTIDAD,UBICACION,HORA o NOMBRE  o si el dato a modificar no es valido dependiendo que tipo de dato sea
#      caso contrario devuelve true.

def son_datos_correctos(tipo_de_dato ,dato):
    
    datos_validos = True 
    if  not(tipo_de_dato == NOMBRE) and not( tipo_de_dato == CANTIDAD) and not(tipo_de_dato == UBICACION) and not(tipo_de_dato == HORA):
        datos_validos = False
        
    else:
            
        if tipo_de_dato == CANTIDAD and not es_cantidad_personas_correcta(dato):
            datos_validos = False
            
        elif  tipo_de_dato == UBICACION and not es_ubicacion_correcta(dato):
            datos_validos = False
            
        elif tipo_de_dato == HORA and not es_horario_correcto(dato):
            datos_validos = False
            
    return datos_validos                


#pre: Recibe un id valido entre mayor a 0.
#post: Pide al usuario el dato a modificar si es valido modifica el dato de una reserva segun el 
#      id ingresado si no existe el id informa al usuario.

def modificar_reserva(id):
    try:
        archivo_reservas = open(ARCHIVO_PRINCIPAL,LEER)
        print("Se abrio con exito el archivo")
    except:
        print("No se pudo abrir el archivo")
        return
            
    try:
        archivo_auxiliar = open(ARCHIVO_AUXILIAR,ESCRIBIR)
        print("Se abrio con exito el archivo auxiliar ")
    except:
        print("No se pudo abrir el archivo aux")
        archivo_reservas.close()
        return
        
    print("Los datos que puede odificar son: Nombre, la Cantidad , Hora (hh:mm) o la Ubicacion?\n")
    dato = input("Que quiere modificar?: ")
        
    informacion = dato.split(" ")
        
    while not son_datos_correctos(informacion[CAMPO_MODIFICABLE], informacion[DATO_NUEVO]):
            
        print("Opcion invalida,Los datos que puede modificar son: Nombre, la Cantidad , Hora (hh:mm) o la Ubicacion(F o D)\n")
        dato = input("Que quiere modificar?: ")
        informacion = dato.split(" ")
            
            
    lectura = csv.reader(archivo_reservas, delimiter = LIMITADOR_LECTURA)
    escritura = csv.writer(archivo_auxiliar,delimiter= LIMITADOR_ESCRITURA)
    id_encontrado = False
        
    for reserva in lectura:
            
        if int(reserva[POSICION_ID]) == int(id):
                
            if informacion[CAMPO_MODIFICABLE] == NOMBRE:
                reserva[POSICION_NOMBRE] = informacion[DATO_NUEVO]
    
            elif informacion[CAMPO_MODIFICABLE] == CANTIDAD:
                reserva[POSICION_INVITADOS] = informacion[DATO_NUEVO]
            
            elif informacion[CAMPO_MODIFICABLE] == HORA: 
                reserva[POSICION_HORARIO] = informacion[DATO_NUEVO]
            else:
                reserva[POSICION_UBICACION] = informacion[DATO_NUEVO]    
            id_encontrado = True
            escritura.writerow(reserva)
            
        else:
            escritura.writerow(reserva)
            
    if id_encontrado == False:
        print("La reserva no pudo modificarse porque no existe\n")
    else:
        print("La reserva fue modificada!!")
    
        
    archivo_auxiliar.close()
    archivo_reservas.close()
    os.rename(ARCHIVO_AUXILIAR, ARCHIVO_PRINCIPAL)

#pre: Recibe un id valido mayor a 0.
#post:elimina la reserva correspondiente al id recibido informa si se pudo borrar la reserva.
def eliminar_reserva(id):

    try:
        archivo_reservas = open(ARCHIVO_PRINCIPAL,LEER)
        print("Se abrio con exito el archivo")
    except:
        print("No se pudo abrir el archivo")
        return
    try:
        archivo_auxiliar = open(ARCHIVO_AUXILIAR,ESCRIBIR)
        print("Se abrio con exito el archivo auxiliar ")
    except:
        print("No se pudo abrir el archivo aux")
        archivo_reservas.close()
        return
        
    lectura = csv.reader(archivo_reservas, delimiter = LIMITADOR_LECTURA)
    escritura = csv.writer(archivo_auxiliar,delimiter= LIMITADOR_ESCRITURA)
        
    id_eliminado = False
    for reserva in lectura:
        if not (int(reserva[POSICION_ID]) == int(id)):
            escritura.writerow(reserva)
        else:
            id_eliminado = True
                
    if id_eliminado == True:
        print("La reserva fue eliminada!!")
    else:
        print(f"La reserva no pudo eliminarse porque no existe una reserva con ID {id}")
        
    archivo_auxiliar.close()
    archivo_reservas.close()
    os.rename(ARCHIVO_AUXILIAR, ARCHIVO_PRINCIPAL)


#pre:  Recibe un string ,la cantidad de personas que es un entero positivo, el horario con el formato (XX:XX) entre 00:00 y 23:59 y la ubicacion (F o D).
#post: Imprime los datos de una reserva.
def imprimir_reserva(id,nombre,cantidad,horario,ubicacion):
    if ubicacion == AFUERA:
        ubicacion = UBICACION_AFUERA
    else:
        ubicacion = UBICACION_ADENTRO
    print("  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━")
    print(f"  ┃ ● ID : {id} ")  
    print(f"  ┃ ● NOMBRE : {nombre}")  
    print(f"  ┃ ● CANTIDAD DE PERSONAS : {cantidad}")  
    print(f"  ┃ ● HORA : {horario}")
    print(f"  ┃ ● UBICACION: {ubicacion}            ")
    print("  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n")


#pre: Recibe dos ids validos mayores que 0.
#post: muestra las reservas que se encuentren entre el primer id y el segundo id.
def listar_algunas_reservas(primer_id , segundo_id):
    
    try:
        archivo_reservas = open(ARCHIVO_PRINCIPAL,LEER)
        print("Se abrio con exito el archivo")
    except:
        print("No se pudo abrir el archivo")
        return
        
    lectura = csv.reader(archivo_reservas, delimiter = LIMITADOR_LECTURA)
    id_encontrado = False
    
    for reserva in lectura:
        if int(reserva[POSICION_ID]) >= int(primer_id) and int(reserva[POSICION_ID]) <= int(segundo_id):
            id_encontrado = True
            imprimir_reserva(reserva[POSICION_ID], reserva[POSICION_NOMBRE], reserva[POSICION_INVITADOS], reserva[POSICION_HORARIO], reserva[POSICION_UBICACION])
    
    if not id_encontrado:
        print(f"El ID :{primer_id} no se encuentra en la lista por ende no hay reservas para mostrar")
            
    archivo_reservas.close()

#pre:-
#post:muestra todas las reservas.
def listar_todas_las_reservas():
    
    try:
        archivo_reservas = open(ARCHIVO_PRINCIPAL,LEER)
        print("Se abrio con exito el archivo")
    except:
        print("No se pudo abrir el archivo")
        return
        
    lectura = csv.reader(archivo_reservas, delimiter = LIMITADOR_LECTURA)
    
    for reserva in lectura:
        imprimir_reserva(reserva[POSICION_ID], reserva[POSICION_NOMBRE], reserva[POSICION_INVITADOS], reserva[POSICION_HORARIO], reserva[POSICION_UBICACION])
    archivo_reservas.close()

#pre:Recibe un 4 strings.
#post: Verifica que los verifca que los daton ingresados sean validos y si se cumple agrega la reserva si el archivo no existe lo crea.
def pasos_para_agregar(nombre,invitados,horario,ubicacion):

    if(not es_cantidad_personas_correcta(invitados)  or not es_horario_correcto(horario) or 
        not es_ubicacion_correcta(ubicacion)):
        return 
    else:
        if agregar_reserva(nombre,invitados,horario,ubicacion) == True:
            pass
        else:
            crear_lista_de_reservas(nombre,invitados,horario,ubicacion)
#pre: Recibe un string.
#post: verifica que el id sea valido y si cumple modifica la recerva correspondiente al id.
def pasos_para_modificar(id):
    if not es_id_valido(id):
        return
    else:
        modificar_reserva(id)
#pre: Recibe un string.
#post: Verifica que el id recibido sea valido y si cumple elimina la reserva.
def pasos_para_eliminar(id):
    if not es_id_valido(id):
        return
    else:
        eliminar_reserva(id)
        
#pre:Recibe dos strings.
#post: verifica que ambos ids sena validos que el segundo sea menor que el primero y si se cumple muestra las reservas 
def pasos_para_listar(primer_id, segundo_id):
    if not es_id_valido(primer_id) or not es_id_valido(segundo_id):
        return
    if  int(segundo_id) < int(primer_id):
        print(f" El segundo id :{segundo_id} no puede ser menor que el primer id : {primer_id}")
    else:
        listar_algunas_reservas(primer_id, segundo_id)

#pre: Recibe una cantidad de argumentos definida un comando(agregar,modificar,eliminar,listar) y la cantidad de argumentos necesaria.
#post: Informa imprimiendo un mensaje cuando la cantidad de parametros recibida no es igual a la necesaria.
def cantidad_incorrecta_de_argumentos(cantidad_de_argumentos, comando, cantidad_necesitada):
    if cantidad_de_argumentos < cantidad_necesitada:
        print(f"No hay suficientes argumentos para {comando}")
        return 
    else:
        print(f"Hay demasiados argumentos no se puede {comando}")
        return 
    