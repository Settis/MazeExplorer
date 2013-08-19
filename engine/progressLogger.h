#ifndef PROGRESSLOGGER_H
#define PROGRESSLOGGER_H
#include <QTextStream>
#include <QFile>
#include "ilistener.h"

class ProgressLogger : public IListener
{
    QFile * file;
    QTextStream * textStream;
public:
    ProgressLogger();
    ~ProgressLogger();
    virtual void onStep(std::vector<RobotContainer> &robots);
};

#endif // PROGRESSLOGGER_H
