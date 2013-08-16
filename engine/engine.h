#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "robot.h"
#include <vector>
#include "maze.h"
#include "ilistener.h"
#include "robotcontainer.h"

using namespace std;

class Engine : public QObject
{
    Q_OBJECT
    Maze * maze;
    unsigned int mazeRooms;
    vector<RobotContainer> robots;
public:
    vector<IListener *> listeners;
    Engine(Maze *maze, vector<Robot*> robots);
    Engine(Maze *maze, vector<Robot*> robots, vector<Point> initials);
    ~Engine();
    void doStep();
    void doMainLogic();
    bool isAllKnownMaze();
    void meets();
};

#endif // ENGINE_H
