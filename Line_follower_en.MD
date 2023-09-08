# Line Follower
## TCRT5000
### Description
It is a device that emits infrared light towards a surface and detects the amount of light that returns to the sensor. It has an emitter (blue) and a detector (black). If it detects low light, it returns 1; if it detects a lot of light, it returns 0. The light threshold is adjusted with a screwdriver.

<img src="https://http2.mlstatic.com/D_NQ_NP_2X_856153-MLM41695339939_052020-F.webp" width="60%">

It should be used very close to the surface, generally within a distance of less than 2-5 millimeters.

### Application

You can set up 2 sensors on the sides of the robot, with the line it follows in the middle. The 2 sensors continuously return (0). If the robot starts to deviate from the path, one of the 2 sensors will detect it (1), and the trajectory can be corrected. The downside of this design is that for very sharp turns, the sensor can easily go off track if it cannot maintain the line between both sensors (when making the sharp turn).

I also think you can use 3 sensors and arrange them so that the center one always detects the line (1), while the ones on the sides are used to straighten the robot, indicating (0). Only the following cases can occur:
1. Center (1): The robot follows the line correctly:
    * Its direction is almost parallel to the line.
2. Left (1): It has deviated to the right:
    * It should turn left until the robot goes from 2. -> 5. -> 1., and when it does, continue straight.
3. Right (1): It has deviated to the left:
    * It should turn right until the robot goes from 3. -> 5. -> 1., and when it does, continue straight.
4. All sensors (1): Line 100% perpendicular to the robot.
5. No sensor (1): The line is between sensors or the line is lost.

<img src="https://cdn.nerdyelectronics.com/wp-content/uploads/2020/08/line-follower-sensor-logic.png" width="100%">

### Buy
* Board $45 [Electronics for Students](http://semty.mx/index.php?id_product=2708&controller=product)
* Sensor $18 [Electronics for Students](http://semty.mx/index.php?id_product=1715&controller=product)
* Set of 5 sensors $150 [Electronics for Students](http://semty.mx/index.php?id_product=2663&controller=product)
