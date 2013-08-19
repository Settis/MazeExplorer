#ifndef ILISTENER_H
#define ILISTENER_H

#include <vector>
#include "robotcontainer.h"

class IListener
{
public:
    IListener();
    virtual void onStep(std::vector<RobotContainer> &robots);
    virtual ~IListener();
    
signals:
    
public slots:
    
};

#endif // ILISTENER_H
