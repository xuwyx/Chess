//
// Created by QZQ on 10/07/2017.
//

#include "StartCommand.h"
#include "../ViewModel.h"

bool StartCommand::execute()
{
	std::vector<int> v = any_cast<std::vector<int>>(*param);
	bool rt = view_model->StartGame(v[0], v[1]);
//	view_model->Update();
	return rt;
}
