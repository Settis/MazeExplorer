#include "mazeTest.h"
#include "maze.h"

using namespace std;

template <class T>
vector<T>& operator<<(vector<T>& vec, const T& x) {
    vec.push_back(x);
    return vec;
}

MazeTest::MazeTest(QObject *parent) :
    QObject(parent)
{
}

void MazeTest::loadFromString()
{
    QString mazeString =
            "*****\n"
            "*   *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    vector<vector<bool> > inner;
    inner << (*(new vector<bool>) << true << true << true << true << true);
    inner << (*(new vector<bool>) << true << false << false << false << true);
    inner << (*(new vector<bool>) << true << true << true << false << true);

    QCOMPARE(maze->walls, inner);
    delete maze;
}

void MazeTest::convertToString()
{
    QString mazeString =
            "*****\n"
            "*   *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    QCOMPARE(maze->convertToString(), mazeString);
    delete maze;
}

void MazeTest::getNeighbors()
{
    QString mazeString =
            "*****\n"
            "*   *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    set<Point> neighbors;
    neighbors.insert(Point(1,1));
    neighbors.insert(Point(3,1));
    QCOMPARE(maze->getNeighbors(Point(2,1)), neighbors);
    delete maze;
}

void MazeTest::get4Neighbors()
{
    QString mazeString =
            "*****\n"
            "*   *\n"
            "*   *\n"
            "*   *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    set<Point> neighbors;
    neighbors.insert(Point(2,1));
    neighbors.insert(Point(1,2));
    neighbors.insert(Point(3,2));
    neighbors.insert(Point(2,3));
    QCOMPARE(maze->getNeighbors(Point(2,2)), neighbors);
    delete maze;
}

void MazeTest::getNeighborsNealestWall()
{
    QString mazeString =
            "*****\n"
            "*   *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    set<Point> neighbors;
    neighbors.insert(Point(3,1));
    QCOMPARE(maze->getNeighbors(Point(3,2)), neighbors);
    delete maze;
}

void MazeTest::getGates()
{
    QString mazeString =
            "**** \n"
            " *  *\n"
            "***  ";
    Maze* maze = Maze::loadFromString(mazeString);
    set<Point> gates;
    gates.insert(Point(0,1));
    gates.insert(Point(4,0));
    gates.insert(Point(3,2));
    gates.insert(Point(4,2));
    QCOMPARE(maze->getGates(), gates);
    delete maze;
}

void MazeTest::checkPassabilitySimple()
{
    QString mazeString =
            "*****\n"
            "*   *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    QCOMPARE(maze->checkPassability(), true);
    delete maze;
}

void MazeTest::checkPassabilityWithoutGates()
{
    QString mazeString =
            "*****\n"
            "*   *\n"
            "*****";
    Maze* maze = Maze::loadFromString(mazeString);
    QCOMPARE(maze->checkPassability(), false);
    delete maze;
}

void MazeTest::checkPassabilityNegative()
{
    QString mazeString =
            "*****\n"
            "* * *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    QCOMPARE(maze->checkPassability(), false);
    delete maze;
}

void MazeTest::getRooms()
{
    QString mazeString =
            "*****\n"
            "* * *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    QCOMPARE(maze->getRooms(), 3);
    delete maze;
}

void MazeTest::isRoomAvailable()
{
    QString mazeString =
            "*****\n"
            "* * *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    QCOMPARE(maze->isRoomAvailable(Point(3, 1)), true);
    delete maze;
}

void MazeTest::isRoomAvailableOutOfBorder()
{
    QString mazeString =
            "*****\n"
            "* * *\n"
            "*** *";
    Maze* maze = Maze::loadFromString(mazeString);
    QCOMPARE(maze->isRoomAvailable(Point(0, -1)), false);
    delete maze;
}
