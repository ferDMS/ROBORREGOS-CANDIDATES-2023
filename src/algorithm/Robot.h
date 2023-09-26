#ifndef ROBOT
#define ROBOT

struct Robot {
    // Distance from the robot to any surface in each direction
    double left_d;
    double up_d;
    double right_d;
    double down_d;

    // Last traversed distance
    double last_traversed;

    // Current facing direction as angle
    int facing;  // 0 - right, 90 - up, 180 - left, 270 - down

    // Color below robot
    std::string color;

    // Constructor
    Robot();

    // Sensor and Components read and write methods
    double getDistance(std::string direction);
    std::string getColor();
    void face(int angle);
    void move(double distance);

    // Special movement methods
    
    // Move while checking front ultrasonic, MPU, and color sensor
    void smartMove(double distance);

    // Other methods
    void getAllDistances();
};

Robot::Robot() {
    // Get color of the square where the robot is located
    // Used to determine the algorithm to perform next
    color = getColor();
}

double Robot::getDistance(std::string direction) {}
std::string Robot::getColor() {}
void Robot::face(int angle) {}
void Robot::move(double distance) {}
void Robot::smartMove(double distance) {}

void Robot::getAllDistances() {
    if (facing == 180) {
        down_d = getDistance("left");
        left_d = getDistance("front");
        up_d = getDistance("right");
        right_d += last_traversed;
    } else if (facing == 90) {
        left_d = getDistance("left");
        up_d = getDistance("front");
        right_d = getDistance("right");
        down_d += last_traversed;
    } else if (facing == 0) {
        up_d = getDistance("left");
        right_d = getDistance("front");
        down_d = getDistance("right");
        left_d += last_traversed;
    } else if (facing == 270) {
        right_d = getDistance("left");
        down_d = getDistance("front");
        left_d = getDistance("right");
        up_d += last_traversed;
    }

    last_traversed = 0.0;
}

#endif