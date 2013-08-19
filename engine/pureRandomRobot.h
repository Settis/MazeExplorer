#ifndef PURERANDOMROBOT_H
#define PURERANDOMROBOT_H

#include "robot.h"


class PureRandomRobot : public Robot
{
public:
    virtual Step makeStep(const Point &current, const Point &prev, const set<Point> &neighbors);
};

#endif // PURERANDOMROBOT_H
