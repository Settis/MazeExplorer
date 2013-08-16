#include "engineTest.h"
#include <vector>
#include "maze.h"
#include "robot.h"
#include "engine.h"

EngineTest::EngineTest(QObject *parent) :
    QObject(parent)
{
}

void EngineTest::aSimpleRobotGowsUp()
{
    QString mazeString =
            "***\n"
            "* *\n"
            "* *\n"
            "* *";
    Maze* maze = Maze::loadFromString(mazeString);
    vector<Robot*> robots;
    robots.push_back(new Robot());
    Engine engine(maze, robots);
    for (int i=0; i<2; ++i) {
        QCOMPARE(engine.isAllKnownMaze(), false);
        engine.doStep();
    }
    QCOMPARE(engine.isAllKnownMaze(), true);
    delete maze;
}

class DownRobot : public Robot {
    virtual Step makeStep(const Point &current, const Point &prev, const set<Point> &neighbors) {
        return DOWN;
    }
};

void EngineTest::meetsInOnePoint()
{
    QString mazeString =
            "* *\n"
            "* *\n"
            "* *\n"
            "* *\n"
            "* *";
    Maze* maze = Maze::loadFromString(mazeString);
    vector<Robot*> robots;
    robots.push_back(new Robot());
    robots.push_back(new DownRobot());
    vector<Point> initials;
    initials.push_back(Point(1,4));
    initials.push_back(Point(1,0));
    Engine engine(maze, robots, initials);
    for (int i=0; i<2; ++i) {
        QCOMPARE(engine.isAllKnownMaze(), false);
        engine.doStep();
        QCOMPARE(engine.isAllKnownMaze(), false);
        engine.meets();
    }
    QCOMPARE(engine.isAllKnownMaze(), true);
    delete maze;
}

void EngineTest::meetsAcross()
{
    QString mazeString =
            "* *\n"
            "* *\n"
            "* *\n"
            "* *";
    Maze* maze = Maze::loadFromString(mazeString);
    vector<Robot*> robots;
    robots.push_back(new Robot());
    robots.push_back(new DownRobot());
    vector<Point> initials;
    initials.push_back(Point(1,3));
    initials.push_back(Point(1,0));
    Engine engine(maze, robots, initials);
    for (int i=0; i<2; ++i) {
        QCOMPARE(engine.isAllKnownMaze(), false);
        engine.doStep();
        QCOMPARE(engine.isAllKnownMaze(), false);
        engine.meets();
    }
    QCOMPARE(engine.isAllKnownMaze(), true);
    delete maze;
}

class TestListener : public IListener {
public:
    int i;
    TestListener() : IListener() {
        i = 0;
    }

    vector<vector<RobotContainer> > robotStates;
    void onStep(vector<RobotContainer> &robots) {
        vector<RobotContainer> container = robotStates[i++];
// TODO fix it
//        QCOMPARE(robots, container);
        QCOMPARE(robots.size(), container.size());
        for (int j=0; j<robots.size(); ++j) {
            QCOMPARE(robots[j].currentPosition, container[j].currentPosition);
            QCOMPARE(robots[j].lastPosition, container[j].lastPosition);
            QCOMPARE(robots[j].robot->visitedPoints, container[j].robot->visitedPoints);
        }
    }
};

void EngineTest::listeners()
{
    QString mazeString =
            "* *\n"
            "* *\n"
            "* *\n"
            "* *";
    Maze* maze = Maze::loadFromString(mazeString);
    vector<Robot*> robots;
    robots.push_back(new Robot());
    robots.push_back(new DownRobot());
    vector<Point> initials;
    initials.push_back(Point(1,3));
    initials.push_back(Point(1,0));
    TestListener testListener;
    vector<RobotContainer> step1;
    Robot buttomRobot1;
    buttomRobot1.visitedPoints.insert(Point(1,3));
    buttomRobot1.visitedPoints.insert(Point(1,2));
    RobotContainer buttomRobot1Container;
    buttomRobot1Container.robot = &buttomRobot1;
    buttomRobot1Container.currentPosition = Point(1,2);
    buttomRobot1Container.lastPosition = Point(1,3);
    step1.push_back(buttomRobot1Container);
    DownRobot topRobot1;
    topRobot1.visitedPoints.insert(Point(1,0));
    topRobot1.visitedPoints.insert(Point(1,1));
    RobotContainer topRobot1Container;
    topRobot1Container.robot = &topRobot1;
    topRobot1Container.currentPosition = Point(1,1);
    topRobot1Container.lastPosition = Point(1,0);
    step1.push_back(topRobot1Container);
    vector<RobotContainer> step2;
    Robot buttomRobot2;
    buttomRobot2.visitedPoints.insert(Point(1,3));
    buttomRobot2.visitedPoints.insert(Point(1,2));
    buttomRobot2.visitedPoints.insert(Point(1,1));
    buttomRobot2.visitedPoints.insert(Point(1,0));
    RobotContainer buttomRobot2Container;
    buttomRobot2Container.robot = &buttomRobot2;
    buttomRobot2Container.currentPosition = Point(1,1);
    buttomRobot2Container.lastPosition = Point(1,2);
    step2.push_back(buttomRobot2Container);
    DownRobot topRobot2;
    topRobot2.visitedPoints.insert(Point(1,0));
    topRobot2.visitedPoints.insert(Point(1,1));
    topRobot2.visitedPoints.insert(Point(1,2));
    topRobot2.visitedPoints.insert(Point(1,3));
    RobotContainer topRobot2Container;
    topRobot2Container.robot = &topRobot2;
    topRobot2Container.currentPosition = Point(1,2);
    topRobot2Container.lastPosition = Point(1,1);
    step2.push_back(topRobot2Container);
    testListener.robotStates.push_back(step1);
    testListener.robotStates.push_back(step2);
    Engine engine(maze, robots, initials);
    engine.listeners.push_back(&testListener);
    engine.doMainLogic();
    delete maze;
}
