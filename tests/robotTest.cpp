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
    Step step;
    bool result = Robot::makeSimpleStep(&step, current, prev, neighbors);
    QCOMPARE(result, true);
    QCOMPARE(step, UP);
}

void RobotTest::makeSimpleStepResumeDirection()
{
    Point current(2,2);
    Point prev(1,2);
    set<Point> neighbors;
    neighbors.insert(Point(3,2));
    neighbors.insert(Point(1,2));
    Step step;
    bool result = Robot::makeSimpleStep(&step, current, prev, neighbors);
    QCOMPARE(result, true);
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
    Step step;
    bool result = Robot::makeSimpleStep(&step, current, prev, neighbors);
    QCOMPARE(result, false);
}

void RobotTest::makeSimpleStep2waysAndStayBefore()
{
    Point current(2,2);
    Point prev(2,2);
    set<Point> neighbors;
    neighbors.insert(Point(3,2));
    neighbors.insert(Point(1,2));
    Step step;
    bool result = Robot::makeSimpleStep(&step, current, prev, neighbors);
    QCOMPARE(result, false);
}

void RobotTest::getStepUp()
{
    Point current(2,2);
    Point next(2,1);
    Step step;
    bool result = Robot::getStep(&step, current, next);
    QCOMPARE(result, true);
    QCOMPARE(step, UP);
}

void RobotTest::getStepDown()
{
    Point current(2,2);
    Point next(2,3);
    Step step;
    bool result = Robot::getStep(&step, current, next);
    QCOMPARE(result, true);
    QCOMPARE(step, DOWN);
}

void RobotTest::getStepLeft()
{
    Point current(2,2);
    Point next(1,2);
    Step step;
    bool result = Robot::getStep(&step, current, next);
    QCOMPARE(result, true);
    QCOMPARE(step, LEFT);
}

void RobotTest::getStepRight()
{
    Point current(2,2);
    Point next(3,2);
    Step step;
    bool result = Robot::getStep(&step, current, next);
    QCOMPARE(result, true);
    QCOMPARE(step, RIGHT);
}

void RobotTest::getStepError()
{
    Point current(2,2);
    Point next(1,1);
    Step step;
    bool result = Robot::getStep(&step, current, next);
    QCOMPARE(result, false);
}
