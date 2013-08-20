#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <maze.h>

enum Step{
    UP, DOWN, LEFT, RIGHT, STOP, NA
};

class Robot : public QObject
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = 0);
    virtual void init(int x, int y);
    virtual Step makeStep(const Point &current, const Point &prev, const set<Point> &neighbors);
    static Step makeSimpleStep(const Point &current, const Point &prev, const set<Point> &neighbors);
    set<Point> visitedPoints;
    void _mergeKnowledge(const Robot &robot);
    virtual void mergeKnowledge(const Robot &robot);
    static Step getStep(const Point &from, const Point &to);
    void _wasMovedTo(const Point &point);
    virtual void wasMotedTo(const Point &point);
    virtual ~Robot();
signals:
    
public slots:
    
};

#endif // ROBOT_H
