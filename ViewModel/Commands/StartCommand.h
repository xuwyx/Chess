//
// Created by QZQ on 10/07/2017.
//

#ifndef CHINESECHESS_STARTCOMMAND_H
#define CHINESECHESS_STARTCOMMAND_H

#include "DerivedCommand.h"

class StartCommand : public DerivedCommand
{
public:
	virtual bool execute() override;
	StartCommand(ViewModel * c): DerivedCommand(c)
	{
	}

private:
	int player[2];
};



#endif //CHINESECHESS_STARTCOMMAND_H
