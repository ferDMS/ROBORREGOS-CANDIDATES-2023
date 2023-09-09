# Algoritmo Zona A
## Resumen
La Zona A es en muy poco detalle simplemente un laberinto. Para poder obtener más puntos en esta zona se debe de recorrer todo el laberinto, con el objetivo de conocer el único color que se repite EXACTAMENTE 5 veces. El tamaño del laberinto es siempre una zona de $3\cdot 5$, y adicionalmente la casilla de checkpoint. Siempre hay una casilla negra, por el cuál no se debe pasar.

Debido a esto, la aparición de los cuadros son:

| Color | Apariciones |
| :-: | :-: |
| Unique $(U)$ | $5$ |
| $A$ | $0 \rightarrow 8$ |
| $B$ | $0 \rightarrow 8$ |
| Black $(K)$ | $1$ |
| Start $(S)$ | $1$ |
| | |
| Total | $15$ |

Donde la aparición de los colores $A+B=8$

El problema radica en posibles paredes flotantes colocadas de manera aleatoria a lo largo del laberinto. Pueden haber dead ends. Se asegura que siempre existirá una salida del laberinto sin conflicto con el cuadro negro o un dead end.

## Pensamiento algorítmico

### Grafo

El sistema completo se puede ver como un grafo que puede o no tener conexiones entre sus diferentes nodos, dependiendo de la existencia de las paredes flotantes. Considerando que pueden existir estas paredes, cada nodo se conecta con otro siempre de manera octogonal, por lo que cada nodo puede tener máximo 4 nodos adyacentes. Considerando el laberinto en la convocatoria:

<div style="text-align: center;">
<img src="../Figures/zoneA_maze1.jpg" width="50%" alt="Original maze design">
<img src="../Figures/IMG_6484.jpg" width="50%" alt="OG maze representation as graph">
</div>

Se requiere un algoritmo que atraviese todos los nodos hasta llegar al último (que siempre será el mismo) con la menor cantidad de aristas posible. Esto asegura que se recorre el laberinto de la manera más eficiente posible.

## Referencias

[Convocatoria oficial](../Candidates%202023.pdf)