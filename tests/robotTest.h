#ifndef ROBOTTEST_H
#define ROBOTTEST_H

#include <QObject>
#include <QtTest>

class RobotTest : public QObject
{
    Q_OBJECT
public:
    explicit RobotTest(QObject *parent = 0);
    
signals:
    
private slots:
    void makeSimpleStep1way();
    void makeSimpleStepResumeDirection();
    void makeSimpleStep4ways();
    void makeSimpleStep2waysAndStayBefore();
    void getStepUp();
    void getStepDown();
    void getStepLeft();
    void getStepRight();
    void getStepError();
};

#endif // ROBOTTEST_H
