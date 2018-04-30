//
// Created by QZQ on 10/07/2017.
//

#ifndef CHINESECHESS_MOVECOMMAND_H
#define CHINESECHESS_MOVECOMMAND_H

#include "DerivedCommand.h"

class MoveCommand : public DerivedCommand
{
public:
	MoveCommand(ViewModel * vm) : DerivedCommand(vm)
	{}

	virtual bool execute() override;


private:
	int sx, sy, ex, ey, player;
};


#endif //CHINESECHESS_MOVECOMMAND_H

