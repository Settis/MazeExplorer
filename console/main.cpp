#include <QCoreApplication>
#include <QStringList>
#include <QString>
#include <iostream>
#include "maze.h"
#include "pureRandomRobot.h"
#include "engine.h"
#include "progressLogger.h"
#include "randomWalker.h"
#include "determinRobot.h"
#include "aaLogger.h"
#include "deepLookRobot.h"

int tryReadInt(QString string) {
    bool isOk;
    int i = string.toInt(&isOk);
    if (isOk)
        return i;
    std::cout << "ERROR: Can not convert '" << string.toStdString() << "' to integer.";
    exit(1);
}

void printGenMazeHelp() {
    std::cout << "This command generate new maze and save it into file.\n"
                 "Usage: mazeExplorer gen fileName x_size y_size num_gates persent_of_walls\n";
}

void printAvailableRobots() {
    std::cout << "Available robots are:\n"
                 "  pureRandom\n"
                 "  randomWalker\n"
                 "  determin\n"
                 "  deepLook\n";
}

void printRunHelp() {
    std::cout << "This command run simulator.\n"
                 "Usage: mazeExplorer run robotName robotCount mazeFile [aaLog]\n";
    printAvailableRobots();
}

void printHelp() {
    std::cout << "Usage: mazeExplorer command [agruments]\n"
                 "Available commands are:\n"
                 "  gen\n"
                 "  run\n"
                 "  help\n";
}

void generateMaze(QStringList &args) {
    if (args.length() == 2 || args.at(2) == "help") {
        printGenMazeHelp();
        return;
    }
    QString fileName = args.at(2);
    int x = tryReadInt(args.at(3));
    int y = tryReadInt(args.at(4));
    int gates = tryReadInt(args.at(5));
    int walls = tryReadInt(args.at(6));
    Maze * maze = Maze::generate(x, y, gates, walls);
    maze->writeToFile(fileName);
    std::cout << "generation complete with " << maze->getPersentWalls() << "% of walls.\n";
    delete maze;
}

void run(QStringList &args) {
    if (args.length() == 2 || args.at(2) == "help") {
        printRunHelp();
        return;
    }
    QString robotName = args.at(2);
    int robotCount = tryReadInt(args.at(3));
    QString mazeFile = args.at(4);
    vector<Robot*> robots;
    Maze * maze = Maze::loadFromFile(mazeFile);
    for (int i=0; i<robotCount; ++i) {
        if (robotName == "pureRandom")
            robots.push_back(new PureRandomRobot());
        else if (robotName == "randomWalker")
            robots.push_back(new RandomWalker());
        else if (robotName == "determin")
            robots.push_back(new DeterminRobot());
        else if (robotName == "deepLook")
            robots.push_back(new DeepLookRobot(maze));
        else {
            printAvailableRobots();
            exit(1);
        }
    }
    Engine engine(maze, robots);
    engine.listeners.push_back(new ProgressLogger());
    if (args.length() >= 6 && args.at(5) == "aaLog") {
        aaLogger * aaLog = new aaLogger();
        aaLog->init(maze);
        engine.listeners.push_back(aaLog);
    }
    engine.doMainLogic();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    if (args.length()<2) {
        printHelp();
        exit(1);
    }
    QString command = args.at(1);
    if (command == "gen")
        generateMaze(args);
    else if (command == "run")
        run(args);
    else
        printHelp();
    return 0;
}
