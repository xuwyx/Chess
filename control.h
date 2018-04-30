#ifndef CONTROL_H
#define CONTROL_H

#include <memory>
#include "View/view.h"
#include "ViewModel/ViewModel.h"
#include "Model/Model.h"
#include "command.h"

class Control
{
public:
    Control(QApplication*);
private:
    std::shared_ptr<View> v;
    std::shared_ptr<ViewModel> vm;
    std::shared_ptr<Model> m;
};

#endif // CONTROL_H
