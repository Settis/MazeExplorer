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
}

Step Robot::makeStep(const Point &UNUSED(current), const Point &UNUSED(prev), const set<Point> &UNUSED(neighbors))
{
    return UP;
}


bool Robot::makeSimpleStep(Step *step, const Point &current, const Point &prev, const set<Point> &neighbors)
{
    if (neighbors.size() == 1)
        return getStep(step, current, *neighbors.begin());
    if (neighbors.size() == 2 && current != prev) {
        set<Point> copy(neighbors);
        copy.erase(prev);
        if (copy.size() == 1)
            return getStep(step, current, *copy.begin());
    }
    return false;
}

void Robot::_mergeKnowledge(const Robot &robot)
{
    visitedPoints.insert(robot.visitedPoints.begin(), robot.visitedPoints.end());
    mergeKnowledge(robot);
}


bool Robot::getStep(Step *step, const Point &from, const Point &to)
{
    int dx = to.first - from.first;
    int dy = to.second - from.second;
    if (dx == -1 && dy == 0) {
        *step = LEFT;
        return true;
    }
    if (dx == 1 && dy == 0) {
        *step = RIGHT;
        return true;
    }
    if (dx == 0 && dy == -1) {
        *step = UP;
        return true;
    }
    if (dx == 0 && dy == 1) {
        *step = DOWN;
        return true;
    }
    return false;
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
