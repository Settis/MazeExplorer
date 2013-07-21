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
    static Maze* loadFromString(const QString &source);
    static Maze* loadFromFile(const QString &fileName);
    static Maze* generate(int x, int y, int numGates, int persentWalls);
    QString convertToString();
    void writeToFile(const QString &fileName);
    vector<vector<bool> > walls;
    set<Point> getNeighbors(const Point &point);
    set<Point> getGates();
    bool checkPassability();
    int getPersentWalls();
signals:

public slots:

};

#endif // MAZE_H
