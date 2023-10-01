#ifndef ROBOT
#define ROBOT

#ifndef ARDUINOSTL_H
#define ARDUINOSTL_H
#include "ArduinoSTL.h"
#endif

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Functions.h"
#endif

#include <utility>

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
    double getDistance(String direction);
    void getColor();

    // Write methods
    bool face(String direction);
    void move(double distance);
    void rgb(String color);
    void ledH();
    void ledL();

    // Special movement methods
    // Move while checking front ultrasonic and color sensor
    bool smartColorMove(double distance, String color);

    // Other methods
    void getAllDistances();
    std::vector<std::pair<String, double> > convertPath(std::vector<Vertex *> path_v);
};

Robot::Robot() {
    // Get color of the square where the robot is located
    // Used to determine the algorithm to perform next
    getColor();
}

double Robot::getDistance(String direction) {

    long distance;

    if (direction == "left") {
        distance = ultrasonic_left();
    } else if (direction == "right") {
        distance = ultrasonic_right();
    } else if (direction == "front") {
        distance = ultrasonic_front();
    }

    return (double)distance;

}

void Robot::getColor() {
    // possible colors:
        // red
        // green
        // blue
        // cyan
        // pink
        // violet
        // yellow
        // black
        // aluminium
    
    int color = color_check();

    if (color == 1) {
        return "red";
    } else if (color == 2) {
        return "green";
    } else if (color == 3) {
        return "blue";
    } else if (color == 4) {
        return "cyan";
    } else if (color == 5) {
        return "pink";
    } else if (color == 6) {
        return "violet";
    } else if (color == 7) {
        return "yellow";
    } else if (color == 8) {
        return "black";
    } else if (color == 9) {
        return "aluminium";
    } else {
        return "None";
    }
     
    this->color = color;
}

// Inside the method, the current facing is considered so that it turns in the least demanding direction (left or right)
bool Robot::face(String direction) {

    if (facing == direction) {
        return 1;
    }

    if (direction == "up") {
        if (facing == "right") {
            turn_left();
        } else if (facing == "down") {
            turn_left();
            turn_left();
        } else if (facing == "left") {
            turn_right();
        }
    } else if (direction == "down") {
        if (facing == "right") {
            turn_right();
        } else if (facing == "up") {
            turn_left();
            turn_left();
        } else if (facing == "left") {
            turn_left();
        }
    } else if (direction == "left") {
        if (facing == "right") {
            turn_left();
            turn_left();
        } else if (facing == "up") {
            turn_left();
        } else if (facing == "down") {
            turn_right();
        }
    } else if (direction == "right") {
        if (facing == "left") {
            turn_left();
            turn_left();
        } else if (facing == "up") {
            turn_right();
        } else if (facing == "down") {
            turn_left();
        }
    }

    return 1;
}

// When called, the last_traversed value gets updated to the distance value
// Uses the ultrasonics to detect the initial_d to the front wall and stops when initial_d - distance = now_d
void Robot::move(double distance) {
    last_traversed = 0;
    getAllDistances();
    double s_distance = getDistance("front");
    if (distance > 0.0) {

        // The 2.0 centimeters account for the distance between the ultrasonic and the limit of the car on the front direction
        if (s_distance + 3.0 > distance) {
            while (last_traversed < distance - 0.5) {
                front(speed);
                delay(10);
                stop();
                delay(10);
                last_traversed = s_distance - getDistance("front");
            }
        }

    } else {

        // The 2.0 centimeters account for the distance between the ultrasonic and the limit of the car on the front direction
        while (-1.0 * last_traversed < -1.0 * distance - 0.5) {
            back(speed);
            delay(10);
            stop();
            delay(10);
            last_traversed = s_distance - getDistance("front");
        }
    }
    
}

void Robot::rgb(String color) {
    // possible colors:
        // red
        // green
        // blue
        // cyan
        // pink
        // violet
        // yellow
        // black
        // aluminium
    if (color == "red") {
        led_red();
    } else if (color == "green") {
        led_green();
    } else if (color == "blue") {
        led_blue();
    }
}

void Robot::ledH() {
    digitalWrite(13, HIGH);
}

void Robot::ledL() {
    digitalWrite(13, LOW);
}

// Returns whether the smartMove has been completed successfully (1) or not (0)
// When called, with each iteration, the last_traversed value keeps increasing until the iterations break or until getting to the distance value
// Also, the iteration will break BUT RETURN TRUE if the front ultrasonic detects a distance of less than a specified limit, so that the gripper doesn't collide with a possible front wall (this does not apply if ale fixes the robot's size)
// During the run of the method the RGB LED must detect change in color if it passes white color at any iteration. If it does, then it prepares to turn the LED on with any color detected after white.
bool Robot::smartColorMove(double distance, String color)
{ 
    last_traversed = 0;
    getAllDistances();
    getColor();
    double s_distance = getDistance("front");

    // The 2.0 centimeters account for the distance between the ultrasonic and the limit of the car on the front direction
    if (s_distance + 3.0 > distance) {
        while (last_traversed < distance - 0.5) {
            front(speed);
            delay(30);
            stop();
            delay(10);
            getColor();
            last_traversed = s_distance - getDistance("front");
            if (this->color == color) {return 0;}
        }
    }

    return 1;
}

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

std::vector<std::pair<String, double> > Robot::convertPath(std::vector<Vertex *> path_v)
{

    std::vector<std::pair<String, double> > path_d;
    String direction;

    // Get direction for the next move according to the last vertices' move
    for (int i = 0; i < path_v.size()-1; i++)
    {
        
        if (path_v[i]->left() == *path_v[i+1]) {
            direction = "left";
        } else if (path_v[i]->up() == *path_v[i+1]) {
            direction = "up";
        } else if (path_v[i]->right() == *path_v[i+1]) {
            direction = "right";
        } else if (path_v[i]->down() == *path_v[i+1]) {
            direction = "down";
        }

        path_d.push_back({direction, 30.0});
        // Serial.print("Pushed: Direction: ");
        // Serial.print(path_d[path_d.size()-1].first);
        // Serial.print("        Distance:  ");
        // Serial.println(path_d[path_d.size()-1].second);
    }

    // // Simplify moves so that same direction moves can be chained, not counting the final move
    // for (int i = 0; i < path_v.size()-2; i++)
    // {
    //     if (path_d[i].first == path_d[i+1].first) {
    //         path_d[i+1].second = path_d[i+1].second * 2.0;
    //         path_d.erase(path_d.begin() + i);
    //         i--;
    //     }
    // }

    return path_d;
}
    

#endif