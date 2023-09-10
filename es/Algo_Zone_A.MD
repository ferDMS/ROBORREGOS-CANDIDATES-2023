# Algoritmo Zona A
## Resumen
La Zona A es en muy poco detalle simplemente un laberinto. Para poder obtener más puntos en esta zona se debe de recorrer todo el laberinto, con el objetivo de conocer el único color que se repite EXACTAMENTE 5 veces $(U)$. El tamaño del laberinto es siempre una zona de $3\cdot 5$, $+1$ contando la casilla del checkpoint de salida $(E)$. Adicionalmente, hay una casilla negra $(K)$, por la cuál no se debe pasar.

Debido a esto, la cuenta de los colores son:

| Color | Apariciones |
| :-: | :-: |
| Unique $(U)$ | $5$ |
| $A$ | $0 \rightarrow 9$ |
| $B$ | $0 \rightarrow 9$ |
| Black $(K)$ | $1$ |
| Start $(S)$ | $1$ |
| | |
| Total | $16$ |

Donde la aparición de los colores $A+B=9$ y el checkpoint final $E$ puede ser $E\in A|E\in B|E\in C$.

El problema radica en posibles paredes flotantes colocadas de manera aleatoria a lo largo del laberinto. Pueden haber dead ends. Se asegura que siempre existirá una salida del laberinto sin conflicto con $K$ o un dead end.

## Algoritmo: Grafo

### Planteamiento

El sistema completo se puede ver como un grafo que puede o no tener conexiones entre sus diferentes nodos, dependiendo de la existencia de las paredes flotantes. Considerando que pueden existir estas paredes, cada nodo se conecta con otro siempre de manera octogonal, por lo que un nodo puede tener máximo 4 nodos adyacentes. Considerando el laberinto en la convocatoria:

<div style="text-align: center;">
<img src="../Figures/zoneA_maze1.jpg" width="50%" alt="Original maze design">
<img src="../Figures/IMG_6484.jpg" width="50%" alt="OG maze representation as graph">
</div>

Se requiere un algoritmo que explore todos los nodos, incluso si se llega a encontrar la casilla de salida $(E)$. Esto se debe a que primero se tiene que determinar el color que tiene exactamente 5 apariciones $(U)$. El nodo $K$ no se debe acceder y por tanto no deben de existir caminos hacia el mismo.

### Depth First Search (DFS)

###  Desarrollo de eficiencia particular

Se puede alcanzar mayor eficiencia al:

1. Guardar al inicio un hashmap de nodos ```max_v``` con su cantidad máxima de aristas (i.e.: cantidad máxima de visitas desde diferentes nodos).
    * Llave: nodo $y$
    * Valor: cantidad máxima de aristas $x$
2. Guardar con cada exploración un hashmap de nodos ```found_v``` con la cantidad de aristas adyacentes encontradas al momento (i.e.: cantidad de veces que se ha encontrado hasta el momento desde diferentes nodos.)
    * Llave: nodo $y$
    * Valor: cantidad de aristas encontradas al momento $a$
3. Comparar ambos valores con cada visita al nodo.
    * Si $x=a$, ya no es necesario explorar el nodo encontrado debido a que ya no hay más por encontrar. Se marca el nodo encontrado como explorado y no se tiene que pasar por el mismo.


Tomando en cuenta el anterior razonamiento, se puede alcanzar mayor eficiencia si se plantea un peso para cada arista que corresponda con el nivel de profundidad del grafo. Esto se propone con el objetivo de marcar como visitados y explorados la mayor cantidad de nodos a la derecha del laberinto antes de avanzar hacia la izquierda. Por ello, se prioriza explorar nodos encontrados con la siguiente jerarquía:

1. Derecha, con peso $-1$
2. Abajo o Arriba, con peso $0$
3. Izquierda, con peso $1$

Donde los números con menor peso tienen mayor prioridad.

### Implementación en C++

### Escalabilidad


## Dudas y suposiciones
1. ¿Cuál es el mínimo y máximo número de apariciones de un color en las casillas? ¿Puede un color no aparecer, o incluso llegar a aparecer más de 5 veces?
    * Se supone que un color puede no aparecer o aparecer todas las veces posibles mientras permita que otro tenga exactamente 5 apariciones.
2. ¿El color aleatorio del checkpoint al final de la Zona A (inicio de la rampa) cuenta para el número de apariciones de un color? ¿Por qué en la convocatoria aparece con un azul más claro?
    * Se supone que si se incluye en la cuenta y que el color cambia para que haga contraste con la representación del cubo en la imagen.

## Referencias

[Convocatoria oficial](../Candidates%202023.pdf)
[Pensamiento algorítmico de DFS & BFS](https://www.youtube.com/watch?v=pcKY4hjDrxk&ab_channel=AbdulBari)