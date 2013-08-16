#ifndef ROBOTCONTAINER_H
#define ROBOTCONTAINER_H
#include "robot.h"
#include "maze.h"

struct RobotContainer {
    Robot * robot;
    Point currentPosition, lastPosition;
};

#endif // ROBOTCONTAINER_H
