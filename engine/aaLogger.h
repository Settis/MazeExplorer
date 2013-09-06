#ifndef AALOGGER_H
#define AALOGGER_H

#include "ilistener.h"
#include "maze.h"
#include <QFile>
#include <QTextStream>

class aaLogger : public IListener
{
    QFile * file;
    QTextStream * textStream;
    int x, y, step;
    Maze *maze;
    char **forPrint;
public:
    aaLogger();
    virtual ~aaLogger();
    void init(Maze *maze);
    virtual void onStep(std::vector<RobotContainer> &robots);
};

#endif // AALOGGER_H
