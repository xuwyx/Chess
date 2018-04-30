//
// Created by QZQ on 06/07/2017.
//

#ifndef CHINESECHESS_COMMAND_H
#define CHINESECHESS_COMMAND_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Any.h"

class Command
{
public:
	virtual bool execute() {return true;}
	std::shared_ptr<Any> param;
};


#endif //CHINESECHESS_COMMAND_H
