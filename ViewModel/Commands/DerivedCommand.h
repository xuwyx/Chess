//
// Created by QZQ on 10/07/2017.
//

#ifndef CHINESECHESS_DERIVEDCOMMAND_H
#define CHINESECHESS_DERIVEDCOMMAND_H
#include "../../command.h"
#include <memory>
#include <vector>

class ViewModel;

class DerivedCommand : public Command
{
public:
	virtual bool execute() override = 0;
	DerivedCommand(ViewModel * v) : view_model(v) {}
protected:
	ViewModel * view_model;
};


#endif //CHINESECHESS_DERIVEDCOMMAND_H
