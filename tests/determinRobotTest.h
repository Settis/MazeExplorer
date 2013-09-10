#ifndef DETERMINROBOTTEST_H
#define DETERMINROBOTTEST_H
#include <vector>
#include <QObject>
#include <QTest>
#include "maze.h"

class DeterminRobotTest : public QObject
{
    Q_OBJECT
    vector<Point> points;
public:
    explicit DeterminRobotTest(QObject *parent = 0);

signals:

private slots:
    void run();

};

#endif // DETERMINROBOTTEST_H
