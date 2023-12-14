#!/usr/bin/python3

import sys
from grafo import Grafo
import csv
from biblioteca import *

# Para evitar el error 'RecursionError: maximum recursion depth exceeded'.
sys.setrecursionlimit(100000)
            
# ******************************************************************
# *                     FUNCIONES AUXILIARES                       *
# ******************************************************************

def leer_archivo(archivo):
    '''Dado un archivo tsv, lee el archivo y nos devuelve un grafo dirigido y no pesado 
    con el contenido del archivo.'''

    grafo = Grafo(True)

    with open(archivo, "r", encoding = "UTF8") as f:
        csv_reader = csv.reader(f, delimiter = "\t")
        
        for linea in csv_reader:
            vertice = linea[0]
            adyacentes = linea[1:]

            if not grafo.pertenece_vertice(vertice):
                grafo.agregar_vertice(vertice)

            for w in adyacentes:
                if not grafo.pertenece_vertice(w):
                    grafo.agregar_vertice(w)

                grafo.agregar_arista(vertice, w)

    return grafo

def separar_entrada(entrada):
    '''Dada una cadena que ingreso el usuario, nos devuelve el comando y los parametros por separado en listas.'''

    lista = entrada.split(" ")
    comando = lista.pop(0)

    if len(lista) > 0:
        parametros = ((" ").join(lista)).split(",")
        return comando, parametros

    else:
        return comando, lista

def imprimir_conjunto(conjunto):
    '''Dado un conjunto, imprime todos sus elementos'''

    salida = ""
    for elemento in conjunto:
        salida += f"{elemento}, "

    print(salida[:-2])  

def imprimir_camino(camino):
    '''Dada una lista que representa un camino de vertices, la imprime
    separando cada vertice por -> .'''

    ultimo = len(camino) - 1
    for i in range(len(camino)):
        if i == ultimo:
            print(camino[i])
            break
        print(camino[i], end = " -> ")

# ******************************************************************
# *                          COMANDOS                              *
# ******************************************************************

def listar_operaciones(comandos):
    '''Dada una estructura de comandos, imprime una línea por cada comando implementado para mostrarselos al usuario.'''
    
    for operacion in comandos:
        if operacion == "listar_operaciones":
            continue
        print(operacion)

def camino(grafo, origen, destino):
    '''Recibe un grafo dirigido y NO pesado, un origen y un destino. Nos imprime una lista con las páginas con los cuales navegamos
    de la página origen a la página destino, navegando lo menos posible.'''

    informacion = bfs(grafo, origen, destino)

    if informacion is None:
        print("No se encontro recorrido")
        return

    padres = informacion[0]
    distancias = informacion[1]
    camino = reconstruir_camino(padres, origen, destino)

    for i in range(len(camino)):
        print(f"{camino[i]}", end = "")
        if (i < len(camino) - 1):
            print(" -> ", end = "")

    print(f"\nCosto: {distancias[destino]}")

def rango(grafo, pagina, n):
    '''Recibe un grafo dirigido y NO pesado, una pagina y un numero n. Imprime por pantalla la 
    cantidad de páginas que se encuenten a exactamente n links/saltos desde la página pasada por parámetro.'''

    informacion = bfs(grafo, pagina)

    if informacion is None:
        print("Error: La pagina no existe")
        return

    distancias = informacion[1]
    cantidad = 0

    for d in distancias.values():
        if d == int(n):
            cantidad += 1

    print(cantidad)

def obtener_diametro(grafo, datos):
    '''Recibe un grafo dirigido y no pesado.
    Imprime por pantalla el diametro del grafo, es decir la distancia del mayor de los caminos
    mínimos y también imprime todos los vértices que conforman este camino.'''

    if not "diametro" in datos:
        distancia, camino = diametro(grafo)
        datos["diametro"] = (distancia, camino)
    
    else:
        distancia, camino = datos["diametro"]
    
    imprimir_camino(camino)
    print(f"Costo: {distancia}")

def navegacion(grafo, origen):
    '''Recibe un grafo dirigido y NO pesado y una pagina.
    Imprime por pantalla todo el recorrido que hace navegando por los primeros links
    de cada página, hasta recorrer 20 páginas o hasta que ya no hay más links.'''

    if not grafo.pertenece_vertice(origen):
        print("La pagina no existe")
        return

    contador = 0
    navegados = []
    navegados.append(origen)

    while len(grafo.adyacentes(origen)) != 0 and contador < 20:
        origen = grafo.adyacentes(origen)[0]
        contador += 1
        navegados.append(origen)

    imprimir_camino(navegados)

def conectados(grafo, pagina, datos):
    '''Recibe un grafo, dirigido y NO pesado, y una pagina. Nos imprime por pantalla todos las páginas 
    a los que podemos llegar desde la página pasado por parámetro y que, a su vez, puedan también volver a dicha página.'''

    if not "cfcs" in datos:
        todas_cfc = cfc(grafo, pagina)
        datos["cfcs"] = todas_cfc
    
    else:
        todas_cfc = datos["cfcs"]

    componente = []
    for c in todas_cfc:
        if pagina in c:
            componente = c
            break

    imprimir_conjunto(componente)
    
def comunidad(grafo, pagina):
    '''Documentacion.'''
    
    comunidad = label_propagation(grafo, pagina)
    imprimir_conjunto(comunidad)

def lectura(grafo, paginas):
    '''Dado un grafo dirigido y una lista de páginas, devuelve
    un orden en el que es válido leer las páginas.'''
    
    orden = orden_topologico_subconjunto(grafo, paginas)

    if orden is None:
        print("No existe forma de leer las paginas en orden")
        return

    orden.reverse()
    imprimir_conjunto(orden)
    
def clustering(grafo, pagina = None):
    '''Dado un grafo dirigido y una pagina, devuelve el coeficiente de clustering de esa pagina.
    En caso de no recibir una pagina, devuelve el clustering promedio del grafo.'''

    grado_salida = grados_salida(grafo)

    if not pagina is None:
        calculo = clustering_particular(grafo, pagina, grado_salida)
        print(calculo)

    else:
        calculo = clustering_promedio(grafo, grado_salida)
        print(calculo)

def ciclo(grafo, pagina, n):
    '''Dado un grafo dirigido, una página y un número entero n, 
    devuelve un ciclo de largo n que comienza en la página pasada por parametro.'''

    recorrido = []
    visitados = set()
    
    if ciclo_n_vertices(grafo, pagina, n, pagina, visitados, recorrido) == False:
        print("No se encontro recorrido")
        return
    
    recorrido.append(pagina)
    recorrido.reverse()
    imprimir_camino(recorrido)

# ******************************************************************
# *                           ENTRADA                              *
# ******************************************************************

def comandos(grafo, comando, parametros, datos):
    '''Dado un grafo, un comando y una lista de parametros ejecuta el comando en caso
    de que sea valido.'''

    comandos = {"listar_operaciones", "camino", "rango", "diametro", "navegacion", "conectados", "comunidad", "lectura", "clustering", "ciclo"}
   
    if not comando in comandos:
        print("Error: Comando invalido")
        return

    if comando == "listar_operaciones":
        listar_operaciones(comandos)

    if comando == "camino":
        if len(parametros) < 2:
            print("Error: Cantidad de parámetros incorrecta")
            return 

        origen = parametros[0]
        destino = parametros[1]
        camino(grafo, origen, destino)

    if comando == "rango":
        if len(parametros) < 2:
            print("Error: Cantidad de parámetros incorrecta")
            return

        pagina = parametros[0]
        n = parametros[1]
        rango(grafo, pagina, n)

    if comando == "diametro":
        obtener_diametro(grafo, datos)

    if comando == "navegacion":
        if len(parametros) != 1:
            print("Error: Cantidad de parámetros incorrecta")
            return

        navegacion(grafo, parametros[0])

    if comando == "conectados":
        if len(parametros) < 1:
            print("Error: Cantidad de parámetros incorrecta")
            return

        pagina = parametros[0]
        conectados(grafo, pagina, datos)

    if comando == "comunidad":
        if len(parametros) < 1:
            print("Error: Cantidad de parámetros incorrecta")
            return

        pagina = parametros[0]
        comunidad(grafo, pagina)

    if comando == "lectura":
        if len(parametros) <= 1:
            print("Error: Cantidad de parámetros incorrecta")
            return

        lectura(grafo, set(parametros))
        
    if comando == "clustering":
        if len(parametros) > 0:
            pagina = parametros[0]
            clustering(grafo, pagina)
            return

        clustering(grafo)

    if comando == "ciclo":
        if len(parametros) != 2:
            print("Error: Cantidad de parámetros incorrecta")
            return

        pagina = parametros[0]
        n = int(parametros[1])
        ciclo(grafo, pagina, n)

def leer_entrada(grafo):
    '''Recibe un grafo y se queda esperando órdenes (o comandos) por entrada estándar del usuario.'''

    datos = {} 
    entrada = True

    while entrada:
        entrada = sys.stdin.readline()
        
        if entrada == "":
            return

        comando, parametros = separar_entrada(entrada.rstrip())
        comandos(grafo, comando, parametros, datos)

# ******************************************************************
# *                             MAIN                               *
# ******************************************************************

def main():
    parametros = sys.argv

    if len(parametros) != 2:
        print("Error: Cantidad de parámetros incorrecta")
        return

    if len(parametros) == 2:
        archivo = parametros[1]
        grafo = leer_archivo(archivo)
        leer_entrada(grafo)

main()