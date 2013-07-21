#include <QTest>
#include "mazeTest.h"

int main(int argc, char *argv[])
{
    int retval(0);
    retval +=QTest::qExec(new MazeTest(), argc, argv);

    return (retval ? 1 : 0);
}
