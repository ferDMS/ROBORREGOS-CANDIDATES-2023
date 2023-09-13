# Line Follower *TCRT5000*
## Descripción
Es un dispositivo que emite luz infrarroja hacia una superficie y detecta la cantidad de luz que regresa al sensor. Tiene un emisor (azul) y un detector (negro). Si detecta poca luz regresa 1, si detecta mucha regresa 0. El límite de luz se modifica con un destornillador.

<img src="https://http2.mlstatic.com/D_NQ_NP_2X_856153-MLM41695339939_052020-F.webp" width="60%">

Se tiene que usar muy de cerca con la superficie, generalmente con menos de 2-5 milímetros de distancia.

## Aplicación

Se puede hacer un setup de 2 sensores que estén a los costados del robot, y la linea que sigue en medio. Los 2 sensores regresan continuamente (0). Si el robot se empieza a salir del camino uno de los 2 sensores lo va a detectar (1) y se puede corregir la trayectoria. Lo malo de este diseño es que para vueltas muy pronunciadas el sensor puede salirse de la trayectoria fácilmente si no alcanza a mantener la línea entre ambos sensores (al no dar la vuelta tan pronunciada).

Se me ocurre que también se pueden usar 3 sensores y acomodarlos de manera que el del centro siempre detecte la línea (1) y los de los costados sirvan para enderezar al robot, marcando (0). Únicamente los siguientes casos pueden ocurrir:
1. Central (1): El robot sigue la línea correctamente:
    * Su dirección es casi paralela a línea.
2. Izquierda (1): Se desvió a la derecha
    * Se debe girar hacia la izquierda hasta que el robot pase de 2. -> 5. -> 1. y, cuando lo haga, seguir recto.
3. Derecha (1): Se desvió a la izquierda
    * Se debe girar hacia la derecha hasta que el robot pase de 3. -> 5. -> 1., y, cuando lo haga, seguir recto.
4. Todos los sensores (1): Línea 100% perpendicular al robot
5. Ningún sensor (1): La línea está entre sensores o se perdió la línea

<img src="https://cdn.nerdyelectronics.com/wp-content/uploads/2020/08/line-follower-sensor-logic.png" width="100%">




## Comprar
* Placa $45 [Electrónica para estudiantes](http://semty.mx/index.php?id_product=2708&controller=product)
* Sensor $18 [Electrónica para estudiantes](http://semty.mx/index.php?id_product=1715&controller=product)
* Placa de 5 $150 [Electrónica para estudiantes](http://semty.mx/index.php?id_product=2663&controller=product)