#ifndef DEEPLOOKROBOTTEST_H
#define DEEPLOOKROBOTTEST_H

#include <vector>
#include <QObject>
#include <QTest>
#include "maze.h"

class DeepLookRobotTest : public QObject
{
    Q_OBJECT
public:
    explicit DeepLookRobotTest(QObject *parent = 0);

signals:

private slots:
    void run();
    void encounter();
    void needWait();
};

#endif // DEEPLOOKROBOTTEST_H
