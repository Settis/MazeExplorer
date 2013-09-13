#ifndef DEEPLOOKROBOT_H
#define DEEPLOOKROBOT_H
#include "robot.h"
#include "maze.h"
#include <QStack>

class DeepLookRobot : public Robot
{
    Maze * maze;
    Point *** prevPointMap;
    int x,y;
    void resetPPCell(Point * point, int i, int j);
    QStack<Point*> steps;
public:
    DeepLookRobot();
    DeepLookRobot(Maze * maze);
    ~DeepLookRobot();
    virtual void init(int x, int y);
    virtual Step makeStep(const Point &current, const Point &prev, const set<Point> &neighbors);
    virtual void mergeKnowledge(const Robot &robot);
    bool ** visitsMap;

};

#endif // DEEPLOOKROBOT_H

