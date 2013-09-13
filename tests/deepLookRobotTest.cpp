#include "deepLookRobotTest.h"
#include "deepLookRobot.h"
#include "engine.h"

DeepLookRobotTest::DeepLookRobotTest(QObject *parent) :
    QObject(parent)
{
}

void DeepLookRobotTest::run()
{
    QString mazeString =
            "*****\n"
            "** **\n"
            "** **\n"
            "    *\n"
            "*****";

    vector<Point> points;
    points.push_back(Point(1,3));
    points.push_back(Point(2,3));
    points.push_back(Point(2,2));
    points.push_back(Point(2,1));
    points.push_back(Point(2,2));
//  points.push_back(Point(2,1));
//  points.push_back(Point(2,2));
//  These points are difference with DeterminRobot
    points.push_back(Point(2,3));
    points.push_back(Point(3,3));

    Maze* maze = Maze::loadFromString(mazeString);
    vector<Robot*> robots;
    robots.push_back(new DeepLookRobot(maze));
    Engine engine(maze, robots);
    engine.init();
    for (Point point : points) {
        engine.doStep();
        QCOMPARE(engine.robots[0].currentPosition, point);
    }
    QCOMPARE(engine.isAllKnownMaze(), true);
    delete maze;
}

void DeepLookRobotTest::encounter()
{
    QString mazeString =
            "* ******\n"
            "* ******\n"
            "* ******\n"
            "*     **\n"
            "* ******\n"
            "* ******\n"
            "*       \n"
            "********";

    vector<Point> points0, points1;
    points0.push_back(Point(1,1));
    points0.push_back(Point(1,2));
    points0.push_back(Point(1,3));
    points0.push_back(Point(1,4));
    points0.push_back(Point(1,5));
    points0.push_back(Point(1,6));

    points1.push_back(Point(6,6));
    points1.push_back(Point(5,6));
    points1.push_back(Point(4,6));
    points1.push_back(Point(3,6));
    points1.push_back(Point(2,6));
    points1.push_back(Point(1,6));

    //encounter!

    points0.push_back(Point(1,5));
    points0.push_back(Point(1,4));
    points0.push_back(Point(1,3));
    points0.push_back(Point(2,3));
    points0.push_back(Point(3,3));
    points0.push_back(Point(4,3));
    points0.push_back(Point(5,3));

    points1.push_back(Point(1,5));
    points1.push_back(Point(1,4));
    points1.push_back(Point(1,3));
    points1.push_back(Point(2,3));
    points1.push_back(Point(3,3));
    points1.push_back(Point(4,3));
    points1.push_back(Point(5,3));

    Maze* maze = Maze::loadFromString(mazeString);
    vector<Robot*> robots;
    robots.push_back(new DeepLookRobot(maze));
    robots.push_back(new DeepLookRobot(maze));
    vector<Point> initial;
    initial.push_back(Point(1,0));
    initial.push_back(Point(7,6));
    Engine engine(maze, robots, initial);
    engine.init();
    for (int i=0; i<points1.size(); ++i) {
        engine.doStep();
        engine.meets();
        QCOMPARE(engine.robots[0].currentPosition, points0[i]);
        QCOMPARE(engine.robots[1].currentPosition, points1[i]);
    }
    QCOMPARE(engine.isAllKnownMaze(), true);
    delete maze;
}
