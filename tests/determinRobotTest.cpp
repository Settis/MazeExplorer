#include "determinRobotTest.h"
#include "determinRobot.h"
#include "robot.h"
#include "engine.h"

DeterminRobotTest::DeterminRobotTest(QObject *parent) :
    QObject(parent)
{
    points.push_back(Point(1,3));
    points.push_back(Point(2,3));
    points.push_back(Point(2,2));
    points.push_back(Point(2,1));
    points.push_back(Point(2,2));
    points.push_back(Point(2,1));
    points.push_back(Point(2,2));
    points.push_back(Point(2,3));
    points.push_back(Point(3,3));
}

void DeterminRobotTest::run()
{
    QString mazeString =
            "*****\n"
            "** **\n"
            "** **\n"
            "    *\n"
            "*****";
    Maze* maze = Maze::loadFromString(mazeString);
    vector<Robot*> robots;
    robots.push_back(new DeterminRobot());
    Engine engine(maze, robots);
    engine.init();
    for (Point point : points) {
        engine.doStep();
        QCOMPARE(engine.robots[0].currentPosition, point);
    }
    QCOMPARE(engine.isAllKnownMaze(), true);
}
