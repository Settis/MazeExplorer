#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> Point;

class Maze : public QObject
{
    Q_OBJECT
    explicit Maze(QObject *parent = 0);
public:
    static Maze* loadFromString(QString source);
    static Maze* loadFromFile(QString fileName);
    static Maze* generate(int x, int y, int numGates, int persentWalls);
    QString convertToString();
    void writeToFile(QString fileName);
    int x, y;
    vector<vector<bool> > walls;
    set<Point> getNeighbors(Point point);
    set<Point> getGates();
    bool checkPassability();
    int getPersentWalls();
signals:

public slots:

};

#endif // MAZE_H
