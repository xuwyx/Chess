#include <QApplication>
#include <memory>
#include "control.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Control c(&a);
    return a.exec();
}
