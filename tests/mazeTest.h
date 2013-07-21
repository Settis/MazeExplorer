#ifndef MAZETEST_H
#define MAZETEST_H

#include <QObject>
#include <QtTest>

class MazeTest : public QObject
{
    Q_OBJECT
public:
    explicit MazeTest(QObject *parent = 0);
    
signals:
    
private slots:
    void loadFromString();
    void convertToString();
    void getNeighbors();
    void get4Neighbors();
    void getNeighborsNealestWall();
    void getGates();
    void checkPassabilitySimple();
    void checkPassabilityWithoutGates();
    void checkPassabilityNegative();
};

#endif // MAZETEST_H
