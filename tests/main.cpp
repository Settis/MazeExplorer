#include <QTest>
#include "robotTest.h"
#include "mazeTest.h"
#include "engineTest.h"
#include "determinRobotTest.h"
#include "deepLookRobotTest.h"
#include <iostream>

int main(int argc, char *argv[])
{
    int retval(0);
    retval +=QTest::qExec(new MazeTest(), argc, argv);
    retval +=QTest::qExec(new RobotTest(), argc, argv);
    retval +=QTest::qExec(new EngineTest(), argc, argv);
    retval +=QTest::qExec(new DeterminRobotTest(), argc, argv);
    retval +=QTest::qExec(new DeepLookRobotTest(), argc, argv);
    if (retval)
        std::cout << "Something is bad.\n";
    else
        std::cout << "All OK!\n";
    return (retval ? 1 : 0);
}
