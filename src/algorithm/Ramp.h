#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

#ifndef ROBOT_H
#define ROBOT_H
#include "Robot.h"
#endif

void ramp(Robot &r) {
    r.facing = "down";
    r.getAllDistances();
    double s_left = r.left_d;
    // The 2.0 centimeters account for the distance between the ultrasonic and the limit of the car on the front direction
    while (r.down_d > 15) {
        front(speed);
        delay(20);
        stop();
        delay(20);
        r.getAllDistances();
        if (r.left_d > s_left) {
            right(speed);
            delay(10);
            stop();
            delay(30);
        } else if (r.left_d < s_left) {
            left(speed);
            delay(10);
            stop();
            delay(30);
        }
    }
    turn_left();
    stop();
}