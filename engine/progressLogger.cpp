#include "progressLogger.h"


ProgressLogger::ProgressLogger()
{
    file = new QFile("progress.csv");
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    textStream = new QTextStream(file);
}

ProgressLogger::~ProgressLogger() {
    textStream->flush();
    delete textStream;
    delete file;
}

void ProgressLogger::onStep(std::vector<RobotContainer> &robots) {
    for (RobotContainer &robotContainer : robots)
        *textStream << robotContainer.robot->visitedPoints.size() << ",";
    *textStream << "\n";
}
