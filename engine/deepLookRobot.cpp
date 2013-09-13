#include "deepLookRobot.h"
#include <algorithm>
#include <QQueue>

DeepLookRobot::DeepLookRobot()
{
}

DeepLookRobot::DeepLookRobot(Maze * maze)
{
    this->maze = maze;
    // it is not fair but quickly for implementation
}

DeepLookRobot::~DeepLookRobot()
{
    for (int i=0; i<x; ++i) {
        for (int j=0; j<y; ++j) {
            if (prevPointMap[i][j] != NULL) {
                delete prevPointMap[i][j];
            }
        }
        delete [] prevPointMap[i];
        delete [] visitsMap[i];
    }
    delete [] prevPointMap;
    delete [] visitsMap;
}

#define processPoint if (f >= 0 && s >= 0 && f < x && s < y) \
if (!maze->walls[s][f] && !passedPoints[f][s]) { \
    resetPPCell(new Point(point->first, point->second), f, s); \
    if (!visitsMap[f][s]) { \
        destination = new Point(f, s); \
        break; \
    }; \
    points.push_back(new Point(f, s)); \
};

Step DeepLookRobot::makeStep(const Point &current, const Point &prev, const set<Point> &neighbors)
{
    visitsMap[prev.first][prev.second] = true;
    visitsMap[current.first][current.second] = true;
    if (!steps.isEmpty()) {
        Point * point = steps.pop();
        Step step = getStep(current, *point);
        delete point;
        return step;
    }
    for (Point point : neighbors) {
        if (!visitsMap[point.first][point.second])
            return getStep(current, point);
    }
    resetPPCell(NULL, current.first, current.second);
    QQueue<Point*> points;
    points.push_back(new Point(current.first, current.second));
    Point *destination;
    bool passedPoints[x][y];
    for (int i=0; i<x; ++i)
        for (int j=0; j<y; ++j)
            passedPoints[i][j] = false;
    while(!points.isEmpty()) {
        Point * point = points.front();
        points.pop_front();
        passedPoints[point->first][point->second] = true;
        int f = point->first - 1,
            s = point->second;
        processPoint
        f = point->first + 1;
        s = point->second;
        processPoint
        f = point->first;
        s = point->second + 1;
        processPoint
        f = point->first;
        s = point->second - 1;
        processPoint
        delete point;
    }
    Step step;
    if (destination == NULL) {
        step = STOP;
        while (!points.isEmpty()) {
            Point * point = points.front();
            points.pop_front();
            delete point;
        }
    } else {
        Point * pIter = destination;
        while (true) {
            Point * point = prevPointMap[pIter->first][pIter->second];
            prevPointMap[pIter->first][pIter->second] = NULL;
            if (point == NULL)
                break;
            steps.push(point);
            pIter = point;
        }
        delete destination;
        while (!points.isEmpty()) {
            Point * point = points.front();
            points.pop_front();
            delete point;
        }
        destination = steps.pop();
        delete destination;
        //this is a point where is robot right now
        destination = steps.pop();
        step = getStep(current, *destination);
        delete destination;
    }
    return step;
}

void DeepLookRobot::mergeKnowledge(const Robot &robot)
{
    bool ** rvm = ((DeepLookRobot*)&robot)->visitsMap;
    for (int i=0; i<x; ++i)
        for (int j=0; j<y; ++j)
            visitsMap[i][j] |= rvm[i][j];
    while (!steps.isEmpty()) {
        Point * point = steps.pop();
        delete point;
    }
}

void DeepLookRobot::resetPPCell(Point * point, int i, int j) {
    if (prevPointMap[i][j] != NULL) {
        delete prevPointMap[i][j];
    }
    prevPointMap[i][j] = point;
}

void DeepLookRobot::init(int x, int y)
{
    this->x = x;
    this->y = y;
    visitsMap = new bool*[x];
    prevPointMap = new Point**[x];
    for (int i=0; i<x; ++i) {
        visitsMap[i] = new bool[y];
        std::fill(visitsMap[i], visitsMap[i]+y, false);
        prevPointMap[i] = new Point*[y];
        for (int j=0; j<y; ++j) {
            prevPointMap[i][j] = NULL;
        }
    }
}
