#include "robotTest.h"
#include "robot.h"

RobotTest::RobotTest(QObject *parent) :
    QObject(parent)
{
}

void RobotTest::makeSimpleStep1way()
{
    Point current(2,2);
    Point prev(2,2);
    set<Point> neighbors;
    neighbors.insert(Point(2,1));
    Step step = Robot::makeSimpleStep(current, prev, neighbors);
    QCOMPARE(step, UP);
}

void RobotTest::makeSimpleStepResumeDirection()
{
    Point current(2,2);
    Point prev(1,2);
    set<Point> neighbors;
    neighbors.insert(Point(3,2));
    neighbors.insert(Point(1,2));
    Step step = Robot::makeSimpleStep(current, prev, neighbors);
    QCOMPARE(step, RIGHT);
}

void RobotTest::makeSimpleStep4ways()
{
    Point current(2,2);
    Point prev(1,2);
    set<Point> neighbors;
    neighbors.insert(Point(3,2));
    neighbors.insert(Point(1,2));
    neighbors.insert(Point(2,1));
    neighbors.insert(Point(2,3));
    Step step = Robot::makeSimpleStep(current, prev, neighbors);
    QCOMPARE(step, NA);
}

void RobotTest::makeSimpleStep2waysAndStayBefore()
{
    Point current(2,2);
    Point prev(2,2);
    set<Point> neighbors;
    neighbors.insert(Point(3,2));
    neighbors.insert(Point(1,2));
    Step step = Robot::makeSimpleStep(current, prev, neighbors);
    QCOMPARE(step, NA);
}

void RobotTest::getStepUp()
{
    Point current(2,2);
    Point next(2,1);
    Step step = Robot::getStep(current, next);
    QCOMPARE(step, UP);
}

void RobotTest::getStepDown()
{
    Point current(2,2);
    Point next(2,3);
    Step step = Robot::getStep(current, next);
    QCOMPARE(step, DOWN);
}

void RobotTest::getStepLeft()
{
    Point current(2,2);
    Point next(1,2);
    Step step = Robot::getStep(current, next);
    QCOMPARE(step, LEFT);
}

void RobotTest::getStepRight()
{
    Point current(2,2);
    Point next(3,2);
    Step step = Robot::getStep(current, next);
    QCOMPARE(step, RIGHT);
}

void RobotTest::getStepError()
{
    Point current(2,2);
    Point next(1,1);
    Step step = Robot::getStep(current, next);
    QCOMPARE(step, NA);
}
