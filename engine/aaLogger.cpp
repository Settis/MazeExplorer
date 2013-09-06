#include "aaLogger.h"
#include <iostream>

aaLogger::aaLogger()
{
    file = new QFile("aaVideo.txt");
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    textStream = new QTextStream(file);
    step = 0;
}


void aaLogger::init(Maze *maze)
{
    x = maze->walls.size();
    y = maze->walls[0].size();
    forPrint = new char*[x];
    for (int i=0; i<x; ++i) {
        forPrint[i] = new char[y];
        for (int j=0; j<y; ++j)
            if (maze->walls[i][j])
                forPrint[i][j] = '#';
            else
                forPrint[i][j] = ' ';
    }
}

aaLogger::~aaLogger()
{
    textStream->flush();
    for (int i=0; i<x; ++i)
        delete [] forPrint[i];
    delete [] forPrint;
    delete textStream;
    delete file;
}

void aaLogger::onStep(std::vector<RobotContainer> &robots)
{
    for (int i=0; i<robots.size(); ++i)
        forPrint[robots[i].currentPosition.second][robots[i].currentPosition.first] = '1' + i;
    for (int i=0; i<x; ++i) {
        for (int j=0; j<y; ++j)
            *textStream << forPrint[i][j];
        *textStream << "\n";
    }
    *textStream << "Step: " << ++step << "\n" << flush;
    for (int i=0; i<robots.size(); ++i)
        *textStream << "Robot '" << (char)('1' + i) << "' : " << robots[i].robot->visitedPoints.size() << "\n" << flush;
    *textStream << "\n\n";
    for (int i=0; i<robots.size(); ++i)
        forPrint[robots[i].currentPosition.second][robots[i].currentPosition.first] = ' ';
}
