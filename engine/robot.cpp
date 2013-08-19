#include "robot.h"

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

Robot::Robot(QObject *parent) :
    QObject(parent)
{
    isMakeSimpleStep = false;
}

Step Robot::_makeStep(const Point &current, const Point &prev, const set<Point> &neighbors)
{
    if (isMakeSimpleStep) {
        Step step = makeSimpleStep(current, prev, neighbors);
        if (step == NA)
            return makeStep(current, prev, neighbors);
        else
            return step;
    } else
        return makeStep(current, prev, neighbors);
}

Step Robot::makeStep(const Point &UNUSED(current), const Point &UNUSED(prev), const set<Point> &UNUSED(neighbors))
{
    return UP;
}


Step Robot::makeSimpleStep(const Point &current, const Point &prev, const set<Point> &neighbors)
{
    if (neighbors.size() == 1)
        return getStep(current, *neighbors.begin());
    if (neighbors.size() == 2 && current != prev) {
        set<Point> copy(neighbors);
        copy.erase(prev);
        if (copy.size() == 1)
            return getStep(current, *copy.begin());
    }
    return NA;
}

void Robot::_mergeKnowledge(const Robot &robot)
{
    visitedPoints.insert(robot.visitedPoints.begin(), robot.visitedPoints.end());
    mergeKnowledge(robot);
}


Step Robot::getStep(const Point &from, const Point &to)
{
    int dx = to.first - from.first;
    int dy = to.second - from.second;
    if (dx == -1 && dy == 0)
        return LEFT;
    if (dx == 1 && dy == 0)
        return RIGHT;
    if (dx == 0 && dy == -1)
        return UP;
    if (dx == 0 && dy == 1)
        return DOWN;
    return NA;
}

void Robot::_wasMovedTo(const Point &point)
{
    visitedPoints.insert(point);
    wasMotedTo(point);
}


void Robot::mergeKnowledge(const Robot &UNUSED)
{
}


void Robot::wasMotedTo(const Point &UNUSED)
{
}

Robot::~Robot()
{
}

//inline bool operator ==(const Robot &r1, const Robot &r2) {
//    return r1.visitedPoints == r2.visitedPoints;
//}
