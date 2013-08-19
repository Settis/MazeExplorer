#include "pureRandomRobot.h"

Step PureRandomRobot::makeStep(const Point &current, const Point &prev, const set<Point> &neighbors) {
    switch (rand() % 4) {
    case 0:
        return DOWN;
    case 1:
        return UP;
    case 2:
        return LEFT;
    case 3:
        return RIGHT;
    }
    return UP;
}
