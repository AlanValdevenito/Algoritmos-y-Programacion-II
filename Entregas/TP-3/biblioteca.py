from cola import Cola
from pila import Pila
import random

# ******************************************************************
# *                            RECORRIDOS                          *
# ******************************************************************

def bfs(grafo, origen, destino = None):
	"""
	Recorrido BFS. 
	Recibe un grafo, un origen y puede tambien recibir (o no) un destino.
	Nos devuelve un conjunto con los padres de los vertices (para reconstruir el camino) y
	tambien un conjunto de las distancias.
	En el caso particular de recibir un posible destino, entonces el algoritmo finalizara 
	cuando se llegue a dicho destino.
	"""

	if not grafo.pertenece_vertice(origen):
		return None

	if not destino is None:
		if not grafo.pertenece_vertice(destino):
			return None

	visitados = set()
	padres = {}
	distancias = {}

	padres[origen] = None
	distancias[origen] = 0
	visitados.add(origen)

	q = Cola()
	q.encolar(origen)
		
	while not q.esta_vacia():
		v = q.desencolar()

		if v == destino:
			return padres, distancias

		for w in grafo.adyacentes(v):
			if w not in visitados:
				padres[w] = v
				distancias[w] = distancias[v] + 1
				visitados.add(w)
				q.encolar(w)

	if (not destino is None) and (destino not in visitados):
		return None
	
	return padres, distancias

def reconstruir_camino(padres, origen, destino):
	'''Dado un conjunto de padres, un origen y un destino, nos devuelve una lista
	con el camino reconstruido desde el origen hasta el destino.'''

	v = destino
	camino = []

	while v != origen:
		camino.append(v)
		v = padres[v]

	camino.append(origen)
	camino.reverse()
	return camino

# ******************************************************************
# *                 COMPONENTES FUERTEMENTE CONEXAS                *
# ******************************************************************

def _cfc(grafo, v, visitados, apilados, orden, mb, todas_cfc, pila, orden_contador):
	'''Componente fuertemente conexa.'''

	visitados.add(v)
	orden[v] = orden_contador
	mb[v] = orden[v]
	orden_contador += 1
	pila.apilar(v)
	apilados.add(v)
	
	for w in grafo.adyacentes(v):
		if w not in visitados:
			visitados, apilados, orden, mb, todas_cfc, pila, orden_contador = _cfc(grafo, w, visitados, apilados, orden, mb, todas_cfc, pila, orden_contador)
 
		if w in apilados:
			mb[v] = min(mb[v], mb[w])
	
	if orden[v] == mb[v]:
		nueva_cfc = set()
		
		while True:
			w = pila.desapilar()
			apilados.remove(w)
			nueva_cfc.add(w)
				
			if w == v:
				break

		todas_cfc.append(nueva_cfc)

	return visitados, apilados, orden, mb, todas_cfc, pila, orden_contador

def cfc(grafo, origen):
	'''Dado un grafo dirigido y un origen, nos devuelve una lista de conjuntos en donde cada 
	conjunto corresponde a una CFC del grafo.'''

	visitados = set()
	apilados = set()
	orden = {}
	mb = {}
	todas_cfc = []
	pila = Pila()
	orden_contador = 0

	visitados, apilados, orden, mb, todas_cfc, pila, orden_contador = _cfc(grafo, origen, visitados, apilados, orden, mb, todas_cfc, pila, orden_contador)
	return todas_cfc

# ******************************************************************
# *                   ALGORITMO LABEL PROPAGATION                  *
# ******************************************************************

def padres_obtener(grafo):
    '''Dado un grafo y un vertice v, nos devuelve un diccionario de la forma {hijo: [padres]}, es decir 
    en donde cada hijo es un vertice y los llamados padres son aquellos vertices que tienen como adyacente al hijo.'''

    padres = {}

    for v in grafo.obtener_vertices():
        padres[v] = []

    for v in grafo.obtener_vertices():
        for w in grafo.adyacentes(v):
            padres[w] = padres.get(w, []) + [v]

    return padres

def max_freq(lista, label):
    '''Dado una lista de elementos, nos devuelve aquel elemento que sea mas frecuente.'''
    
    contador = {}
    for v in lista:
        contador[label[v]] = contador.get(label[v], 0) + 1

    resultado = random.choice(list(contador.keys()))
    for clave in contador:
        if contador[clave] > contador[resultado]:
            resultado = clave

    return resultado

def label_propagation(grafo, origen):
	'''Algoritmo Label Propagation. Recibe un grafo y un origen.
	Devuelve la comunidad a la que pertenece dicho origen.'''

	vertices = grafo.obtener_vertices()
	padres = padres_obtener(grafo)
	labels = {}

	i = 0
	for v in vertices:
		labels[v] = i
		i += 1

	labels_asincronico = labels
	condicion_corte = 0
	while condicion_corte != 75: 
		random.shuffle(vertices)

		for v in vertices:
			p = padres[v]

			if len(p) == 0:
				continue

			labels_asincronico[v] = max_freq(p, labels)

		labels = labels_asincronico
		condicion_corte += 1

	comunidad = []
	for v in labels:
		if labels[origen] == labels[v]:
			comunidad.append(v)
	return comunidad

# ******************************************************************
# *                   COEFICIENTE DE CLUSTERING                    *
# ******************************************************************

def grados_salida(grafo):
	'''Dado un grafo dirigido, nos devuelve el grado de salida de los vertices sin contar los posibles bucles.'''
	
	grados_salida = {}

	for v in grafo.obtener_vertices():
		for w in grafo.adyacentes(v):
			if not v == w:
				grados_salida[v] = grados_salida.get(v, 0) + 1

	return grados_salida

def clustering_particular(grafo, vertice, grado_salida):
	'''Dado un grafo y un vertice particular, nos devuelve el coeficiente
	de Clustering de dicho vertice.'''

	vertice_adyacentes = grafo.adyacentes(vertice)

	if vertice_adyacentes != None:
		if vertice in vertice_adyacentes:
			vertice_adyacentes.remove(vertice)

	if len(vertice_adyacentes) < 2:
		return 0

	cantidad_aristas = 0
	for w in vertice_adyacentes: 
		for u in vertice_adyacentes:

			if w == u:
				continue
			
			if grafo.estan_unidos(w,u):
				cantidad_aristas += 1

	clustering_v = (cantidad_aristas) / (grado_salida[vertice] * (grado_salida[vertice] - 1))
	return round(clustering_v, 3)

def clustering_promedio(grafo, grado_salida):
	'''Dado un grafo, nos devuelve el coeficiente de Clustering
	promedio de todo el grafo.'''

	suma = 0
	cantidad_vertices = 0
	for v in grafo.obtener_vertices():
		cantidad_vertices += 1
		suma += clustering_particular(grafo, v, grado_salida)

	clustering_promedio =  (1 / cantidad_vertices) * suma
	return round(clustering_promedio, 3)

# ******************************************************************
# *                           DIAMETRO                             *
# ******************************************************************

def diametro(grafo):
	'''Dado un grafo dirigido, nos devuelve el diametro de toda la red.
	Es decir, nos devuelve el camino minimo mas grande de toda la red.'''

	max_dist = 0

	for v in grafo.obtener_vertices(): 
		padres, distancias = bfs(grafo, v) 
		
		for w in distancias:
			if distancias[w] > max_dist:
				max_dist = distancias[w]
				origen = v
				destino = w
				padre = padres
				
	camino = reconstruir_camino(padre, origen, destino)
	return max_dist, camino

# ******************************************************************
# *                      ORDEN TOPOLOGICO                          *
# ******************************************************************

def grados_entrada(grafo, subconjunto):
	'''Dado un grafo dirigido, nos devuelve el grado de entrada del subconjunto.'''

	grado_entrada = {}

	for v in subconjunto:
		grado_entrada[v] = 0

	for v in subconjunto:
		for link in grafo.adyacentes(v):
			if link in subconjunto:
				grado_entrada[link] += 1

	return grado_entrada

def orden_topologico_subconjunto(grafo, subconjunto):
	'''Dado un grafo dirigido y un subconjunto de vertices del grafo, devuelve
	el orden topologico de los vertices del subconjunto.'''

	grado_entrada = grados_entrada(grafo, subconjunto) 
	cola = Cola()
	orden = []

	for v in subconjunto: 
		if grado_entrada[v] == 0:
			cola.encolar(v)

	while not cola.esta_vacia():
		v = cola.desencolar()
		orden.append(v)

		for w in grafo.adyacentes(v):
			if w in subconjunto:
				grado_entrada[w] -= 1
				if grado_entrada[w] == 0:
					cola.encolar(w)
     
	if len(orden) != len(subconjunto):
		return None

	return orden

# ******************************************************************
# *                       CICLO DE N VERTICES                      *
# ******************************************************************

def ciclo_n_vertices(grafo, origen, n, vertice, visitados, recorrido):
	'''Dado un grafo dirigido, un vertice origen y un entero n devuelve
	un ciclo de largo n que empieza y termina en el vertice origen.'''

	if n == 1:
		if origen in grafo.adyacentes(vertice):
			recorrido.append(origen)
			return True
		else:
			return False

	if len(grafo.adyacentes(vertice)) == 0:
		return False 

	for w in grafo.adyacentes(vertice):
		if w == origen and n > 0:
			continue

		if w not in visitados and w not in recorrido:
			visitados.add(w)
			if ciclo_n_vertices(grafo, origen, n - 1, w, visitados, recorrido) == True:
				if w not in recorrido:
					recorrido.append(w)
				return True