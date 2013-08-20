#ifndef DETERMINROBOT_H
#define DETERMINROBOT_H
#include "robot.h"

class DeterminRobot : public Robot
{
    unsigned int** visitsMap;
    int x,y;
public:
    DeterminRobot();
    ~DeterminRobot();
    virtual void init(int x, int y);
    virtual Step makeStep(const Point &current, const Point &prev, const set<Point> &neighbors);
};

#endif // DETERMINROBOT_H
