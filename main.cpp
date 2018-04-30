#include <QApplication>
#include <memory>
#include "control.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<Control> c(new Control(&a));
    return a.exec();
}
