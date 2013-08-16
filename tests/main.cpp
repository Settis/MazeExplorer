#include <QTest>
#include "robotTest.h"
#include "mazeTest.h"
#include "engineTest.h"

int main(int argc, char *argv[])
{
    int retval(0);
    retval +=QTest::qExec(new MazeTest(), argc, argv);
    retval +=QTest::qExec(new RobotTest(), argc, argv);
    retval +=QTest::qExec(new EngineTest(), argc, argv);
    return (retval ? 1 : 0);
}
