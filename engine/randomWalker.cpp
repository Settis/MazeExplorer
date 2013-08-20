#include "randomWalker.h"

RandomWalker::RandomWalker()
{
}

Step RandomWalker::makeStep(const Point &current, const Point &prev, const set<Point> &neighbors)
{
    Step step = makeSimpleStep(current, prev, neighbors);
    if (step != NA)
        return step;
    vector<Point> points;
    for (Point point : neighbors)
        if (prev != point)
            points.push_back(point);
    return getStep(current, points[rand() % points.size()]);
}
