#include "maze.h"
#include <QStringList>
#include <iostream>
#include <queue>
#include <QFile>
#include <QTextStream>
#include <algorithm>

Maze::Maze(QObject *parent) :
    QObject(parent)
{
}

set<Point> Maze::getNeighbors(Point point)
{
    set<Point> allNeighbors;
    allNeighbors.insert(Point(point.first, point.second-1));
    allNeighbors.insert(Point(point.first, point.second+1));
    allNeighbors.insert(Point(point.first-1, point.second));
    allNeighbors.insert(Point(point.first+1, point.second));
    set<Point> result;
    for (auto point = allNeighbors.begin(); point != allNeighbors.end(); ++point) {
        if (point->first < 0 || point->second < 0 || point->second >= (int) walls.size() || point->first >= (int) walls[0].size())
            continue;
        if (! walls[point->second][point->first])
            result.insert(*point);
    }
    return result;
}

set<Point> Maze::getGates()
{
    set<Point> gates;
    int lastRowInd = walls.size()-1;
    int rowSize = walls[0].size()-1;
    vector<bool> firstRow = walls[0], lastRow = walls[lastRowInd];
    for (int i=0; i<=rowSize; ++i) {
        if (!firstRow[i])
            gates.insert(Point(i, 0));
        if (!lastRow[i])
            gates.insert(Point(i, lastRowInd));
    }
    for (int i=1; i<lastRowInd; ++i) {
        if (!walls[i][0])
            gates.insert(Point(0, i));
        if (!walls[i][rowSize])
            gates.insert(Point(rowSize, i));
    }
    return gates;
}

bool Maze::checkPassability()
{
    // check gates numbers
    set<Point> gates = getGates();
    if (gates.size()==0)
        return false;
    // queue for wide algorithm
    queue<Point> points;
    points.push(*(gates.begin()));
    int x = walls.size(), y = walls[0].size();
    bool passedPoints[x][y];
    for (int i=0; i<x; ++i)
        for (int j=0; j<y; ++j)
            passedPoints[i][j] = walls[i][j];
    while(!points.empty()) {
        Point point = points.front();
        points.pop();
        passedPoints[point.second][point.first] = true;
        set<Point> neighbors = getNeighbors(point);
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it)
            if (!passedPoints[it->second][it->first])
                points.push(*it);
    }
    for (int i=0; i<x; ++i)
        for (int j=0; j<y; ++j)
            if (!passedPoints[i][j])
                return false;
    return true;
}

int Maze::getPersentWalls()
{
    int x = walls.size();
    int y = walls[0].size();
    int wallsCnt = 0;
    for (int i=1; i<x-1; ++i)
        for (int j=1; j<y-1; ++j)
            if (walls[i][j])
                ++wallsCnt;
    return wallsCnt*100/(x-2)/(y-2);
}

Maze * Maze::loadFromString(QString source)
{
    Maze * maze = new Maze();
    auto list = source.split("\n", QString::SplitBehavior::SkipEmptyParts);
    for (auto it = list.constBegin(); it != list.constEnd(); ++it) {
        vector<bool> row;
        for (auto ch = it->begin(); ch != it->end(); ++ch)
            if ((*ch) == '*')
                row.push_back(true);
            else
                row.push_back(false);
        maze->walls.push_back(row);
    }
    return maze;
}

Maze *Maze::loadFromFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    return loadFromString(in.readAll());
}

Maze *Maze::generate(int x, int y, int numGates, int persentWalls)
{
    Maze * maze = new Maze();
    // make borders
    vector<bool> fillRow;
    for (int i=0; i<x; ++i)
        fillRow.push_back(true);
    vector<bool> middleRow;
    middleRow.push_back(true);
    for (int i=1; i<x-1; ++i)
        middleRow.push_back(false);
    middleRow.push_back(true);
    maze->walls.push_back(vector<bool>(fillRow));
    for (int i=1; i<y-1; ++i)
        maze->walls.push_back(vector<bool>(middleRow));
    maze->walls.push_back(vector<bool>(fillRow));
    // make gates
    vector<Point> borders;
    for (int i=1; i<x-1; ++i) {
        borders.push_back(Point(i,0));
        borders.push_back(Point(i,y-1));
    }
    for (int i=1; i<y-1; ++i) {
        borders.push_back(Point(0,i));
        borders.push_back(Point(x-1,i));
    }
    std::random_shuffle(borders.begin(), borders.end());
    int effectiveGates = min(numGates, (int) borders.size());
    for (int i=0; i<effectiveGates; ++i)
        maze->walls[borders[i].second][borders[i].first] = false;
    // make walls
    int wallsCnt = (x-2)*(y-2)*persentWalls/100;
    vector<Point> walls;
    for (int i=1; i<x-1; ++i)
        for (int j=1; j<y-1; ++j)
            walls.push_back(Point(i,j));
    std::random_shuffle(walls.begin(), walls.end());
    for (int i=0; i<(int)walls.size()&&wallsCnt>0; ++i) {
        Point point = walls[i];
        maze->walls[point.second][point.first] = true;
        if (maze->checkPassability())
            --wallsCnt;
        else
            maze->walls[point.second][point.first] = false;
    }
    return maze;
}


QString Maze::convertToString()
{
    QStringList list;
    for (auto row = walls.begin(); row != walls.end(); ++row) {
        QString string;
        for (auto point = row->begin(); point != row->end(); ++point)
            if (*point)
                string.append('*');
            else
                string.append(' ');
        list.push_back(string);
    }
    return list.join("\n");
}

void Maze::writeToFile(QString fileName)
{
    QString data = convertToString();
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << data;
    out.flush();
}
