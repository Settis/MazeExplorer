#include "randomWalker.h"

RandomWalker::RandomWalker()
{
    isMakeSimpleStep = true;
}

Step RandomWalker::makeStep(const Point &current, const Point &prev, const set<Point> &neighbors)
{
    vector<Point> points;
    for (Point point : neighbors)
        if (prev != point)
            points.push_back(point);
    return getStep(current, points[rand() % points.size()]);
}
