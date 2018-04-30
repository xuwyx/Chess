//
// Created by QZQ on 10/07/2017.
//

#ifndef CHINESECHESS_POSSIBLEMOVECOMMAND_H
#define CHINESECHESS_POSSIBLEMOVECOMMAND_H

#include "DerivedCommand.h"

class PossibleMoveCommand : public DerivedCommand
{
public:
	PossibleMoveCommand(ViewModel * vm);

	virtual bool execute() override;

private:
	int sx, sy, player;
};


#endif //CHINESECHESS_POSSIBLEMOVECOMMAND_H
