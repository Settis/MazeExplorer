#include "engine.h"
#include <cstdlib>

Engine::Engine(Maze * maze, vector<Robot *> robots) : QObject()
{
    this->maze = maze;
    mazeRooms = maze->getRooms();
    set<Point> gates = maze->getGates();
    vector<Point> gatesVector;
    std::copy(gates.begin(), gates.end(), std::back_inserter(gatesVector));
    for (Robot *robot : robots) {
        Point initial = gatesVector[rand() % gatesVector.size()];
        RobotContainer container;
        container.robot = robot;
        container.currentPosition = initial;
        container.lastPosition = initial;
        robot->_wasMovedTo(initial);
        this->robots.push_back(container);
    }
}

Engine::Engine(Maze *maze, vector<Robot *> robots, vector<Point> initials) : QObject() {
    this->maze = maze;
    mazeRooms = maze->getRooms();
    for (int i=0; i<robots.size(); ++i) {
        Point initial = initials[i];
        RobotContainer container;
        container.robot = robots[i];
        container.currentPosition = initial;
        container.lastPosition = initial;
        robots[i]->_wasMovedTo(initial);
        this->robots.push_back(container);
    }
}

Engine::~Engine()
{
    for (RobotContainer container : robots)
        delete container.robot;
    for (IListener* listener : listeners)
        delete listener;
}

Point operator +(const Point &point, Step &step) {
    switch(step){
        case STOP: return point;
        case UP: return Point(point.first, point.second-1);
        case DOWN: return Point(point.first, point.second+1);
        case LEFT: return Point(point.first-1, point.second);
        case RIGHT: return Point(point.first+1, point.second);
    }
    return Point(-1,-1);
}

void Engine::doStep()
{
    for (RobotContainer &container : robots) {
        Step step = container.robot->makeStep(container.currentPosition, container.lastPosition, maze->getNeighbors(container.currentPosition));
        Point nextPoint = container.currentPosition + step;
        container.lastPosition = container.currentPosition;
        if (maze->isRoomAvailable(nextPoint)) {
            container.currentPosition = nextPoint;
            container.robot->_wasMovedTo(nextPoint);
        }
    }
}


bool Engine::isAllKnownMaze()
{
    for (const RobotContainer & robotContainer : robots) {
        if (robotContainer.robot->visitedPoints.size() != mazeRooms)
            return false;
    }
    return true;
}

void Engine::meets()
{
    for (int i=0; i<robots.size(); ++i)
        for (int j=i+1; j<robots.size(); ++j) {
            Point currentI = robots[i].currentPosition;
            Point currentJ = robots[j].currentPosition;
            if (currentI == currentJ || (
                        currentI == robots[j].lastPosition &&
                        currentJ == robots[i].lastPosition
                        )) {
                robots[i].robot->_mergeKnowledge(*(robots[j].robot));
                robots[j].robot->_mergeKnowledge(*(robots[i].robot));
            }
        }
}

void Engine::init()
{
    for (const RobotContainer & robotContainer : robots)
        robotContainer.robot->init(maze->walls[0].size(), maze->walls.size());
}

void Engine::doMainLogic()
{
    init();
    do {
        doStep();
        meets();
        for (IListener* listener : listeners)
            listener->onStep(robots);
    } while (!isAllKnownMaze());
}
