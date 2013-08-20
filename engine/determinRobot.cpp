#include "determinRobot.h"
#include <climits>
#include <algorithm>

DeterminRobot::DeterminRobot()
{
}

DeterminRobot::~DeterminRobot()
{
    for (int i=0; i<x; ++i)
        delete [] visitsMap[i];
    delete [] visitsMap;
}

void DeterminRobot::init(int x, int y)
{
    this->x = x;
    this->y = y;
    visitsMap = new unsigned int*[x];
    for (int i=0; i<x; ++i) {
        visitsMap[i] = new unsigned int[y];
        std::fill(visitsMap[i], visitsMap[i]+y, 0);
    }
}

Step DeterminRobot::makeStep(const Point &current, const Point &prev, const set<Point> &neighbors)
{
    ++visitsMap[current.first][current.second];
    unsigned int minVis = UINT_MAX;
    Point next;
    for (Point point : neighbors)
        if (visitsMap[point.first][point.second] < minVis) {
            minVis = visitsMap[point.first][point.second];
            next = point;
        }
    return getStep(current, next);
}
