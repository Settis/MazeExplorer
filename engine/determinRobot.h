#ifndef DETERMINROBOT_H
#define DETERMINROBOT_H
#include "robot.h"

class DeterminRobot : public Robot
{
    int x,y;
public:
    DeterminRobot();
    ~DeterminRobot();
    virtual void init(int x, int y);
    virtual Step makeStep(const Point &current, const Point &prev, const set<Point> &neighbors);
    virtual void mergeKnowledge(const Robot &robot);
    unsigned int** visitsMap;
};

#endif // DETERMINROBOT_H
