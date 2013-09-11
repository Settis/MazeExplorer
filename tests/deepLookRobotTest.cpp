#include "deepLookRobotTest.h"
#include "deepLookRobot.h"
#include "engine.h"

DeepLookRobotTest::DeepLookRobotTest(QObject *parent) :
    QObject(parent)
{
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
}

void DeepLookRobotTest::run()
{
    QString mazeString =
            "*****\n"
            "** **\n"
            "** **\n"
            "    *\n"
            "*****";
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
