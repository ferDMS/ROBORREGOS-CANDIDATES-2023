#ifndef ROBOT
#define ROBOT

#ifndef ARDUINOSTL_H
#define ARDUINOSTL_H
#include "ArduinoSTL.h"
#endif

struct Robot {
    // Distance from the robot to any surface in each direction
    double left_d;
    double up_d;
    double right_d;
    double down_d;

    // Last traversed distance
    double last_traversed;

    // Current facing direction as angle
    String facing;  // "right", "up", "left", or "down"

    // Color below robot
    String color;

    // Constructor
    Robot();

    // Read methods (that store values into the corresponding attributes)
    double getDistance(String distance);
    String getColor();

    // Write methods
    void face(String direction);
    void move(double distance);
    void rgb(String color);

    // Special movement methods
    // Move while checking front ultrasonic and color sensor
    bool smartColorMove(double distance, String color);

    // Other methods
    void getAllDistances();
};

Robot::Robot() {
    // Get color of the square where the robot is located
    // Used to determine the algorithm to perform next
    color = getColor();
}

double Robot::getDistance(String distance) {return 10.0;}
String Robot::getColor() {return String("");}

// Inside the method, the current facing is considered so that it turns in the least demanding direction (left or right)
void Robot::face(String direction) {}

// When called, the last_traversed value gets updated to the distance value
// Uses the ultrasonics to detect the initial_d to the front wall and stops when initial_d - distance = now_d
void Robot::move(double distance) {}

void Robot::rgb(String color) {}

// Returns whether the smartMove has been completed successfully (1) or not (0)
// When called, with each iteration, the last_traversed value keeps increasing until the iterations break or until getting to the distance value
// Also, the iteration will break BUT RETURN TRUE if the front ultrasonic detects a distance of less than a specified limit, so that the gripper doesn't collide with a possible front wall (this does not apply if ale fixes the robot's size)
// During the run of the method the RGB LED must detect change in color if it passes white color at any iteration. If it does, then it prepares to turn the LED on with any color detected after white.
bool Robot::smartColorMove(double distance, String color) { return 0; }

void Robot::getAllDistances() {
    if (facing == "left") {
        down_d = getDistance("left");
        left_d = getDistance("front");
        up_d = getDistance("right");
        right_d += last_traversed;
    } else if (facing == "up") {
        left_d = getDistance("left");
        up_d = getDistance("front");
        right_d = getDistance("right");
        down_d += last_traversed;
    } else if (facing == "right") {
        up_d = getDistance("left");
        right_d = getDistance("front");
        down_d = getDistance("right");
        left_d += last_traversed;
    } else if (facing == "down") {
        right_d = getDistance("left");
        down_d = getDistance("front");
        left_d = getDistance("right");
        up_d += last_traversed;
    }

    last_traversed = 0.0;
}

#endif