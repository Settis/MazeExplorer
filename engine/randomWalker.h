#ifndef RANDOMWALKER_H
#define RANDOMWALKER_H
#include "robot.h"

class RandomWalker : public Robot
{
public:
    RandomWalker();
    virtual Step makeStep(const Point &current, const Point &prev, const set<Point> &neighbors);
};

#endif // RANDOMWALKER_H
