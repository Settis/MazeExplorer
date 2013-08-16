#ifndef ENGINETEST_H
#define ENGINETEST_H

#include <QObject>
#include <QtTest>

class EngineTest : public QObject
{
    Q_OBJECT
public:
    explicit EngineTest(QObject *parent = 0);
    
signals:
    
private slots:
    void aSimpleRobotGowsUp();
    void meetsInOnePoint();
    void meetsAcross();
    void listeners();
};

#endif // ENGINETEST_H
