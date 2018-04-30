#include "sleep.h"

void sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime() < reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}
