#include <QCoreApplication>
#include <QStringList>
#include <QString>
#include <iostream>
#include "maze.h"

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

void printHelp() {
    std::cout << "Usage: mazeExplorer command [agruments]\n"
                 "Available commands are:\n"
                 "  gen\n"
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
    else
        printHelp();
    return 0;
}
