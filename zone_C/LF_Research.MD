# Line Follower *TCRT5000*
## Description
It is a device that emits infrared light towards a surface and detects the amount of light that returns to the sensor. It has an emitter (blue) and a detector (black). If the emitted IR rays return to the detector, it returns 1; if the emitted IR rays do not return to the detector, it returns 0. The light digital output threshold is adjusted with a screwdriver.

![TCRT5000 Module](https://http2.mlstatic.com/D_NQ_NP_2X_856153-MLM41695339939_052020-F.webp)

If the module is used as a proximity sensor, it can detect objects up to a distance of 3 to 5 centimeters. Using it as a line follower it has to be at a distance of at least 2 to 5 millimeters from the surface.

## Application

You can set up 2 sensors on the sides of the robot, with the line it follows in the middle between both. The sensors continuously return (0). If the robot starts to deviate from the path, one of the 2 sensors will detect it (1), and the trajectory can be corrected. The drawback of this design is that for very sharp turns, the sensor can easily deviate from the path if it cannot maintain the line in between both sensors (when the turn is too sharp).

It occurs to me that you can also use 3 sensors and arrange them so that the center one always detects the line (1), and the ones on the sides are used to straighten the robot, marking (0). Only the following cases can occur:

1. Center returns $1$: The robot follows the line correctly:
   * Its direction is almost parallel to the line.
2. Left returns $1$: It deviated to the right
   * It should turn left until the robot goes from 2. -> 5. -> 1. and when it does, continue straight.
3. Right returns $1$: It deviated to the left
   * It should turn right until the robot goes from 3. -> 5. -> 1., and when it does, continue straight.
4. All sensors return $1$: Line 100% perpendicular to the robot
5. All sensors return $0$: The line is between two sensors or the line was lost

![Line Follower Cases](https://cdn.nerdyelectronics.com/wp-content/uploads/2020/08/line-follower-sensor-logic.png)

## Buy
* Board $45 [Electronics for Students](http://semty.mx/index.php?id_product=2708&controller=product)
* Sensor $18 [Electronics for Students](http://semty.mx/index.php?id_product=1715&controller=product)
* Set of 5 boards $150 [Electronics for Students](http://semty.mx/index.php?id_product=2663&controller=product)
