//
// Created by QZQ on 07/07/2017.
//

#include "ViewModel.h"
#include "Commands/MoveCommand.h"
#include "Commands/PossibleMoveCommand.h"
#include "Commands/StartCommand.h"
#include <memory>

using namespace std;

bool ViewModel::GameIsOver()
{ return c_model->GameIsOver(); }

void ViewModel::SetAIPlayer(int player, bool is_AI)
{ c_model->setAI(player, is_AI); }

void ViewModel::ConnectModel(shared_ptr<Model> model)
{
	c_model = model;
	chess_board = model->chess_board;
	possible_move_pos = model->possible_move_pos;
}

ViewModel::ViewModel()
{
	start_command = make_shared<StartCommand>(this);
	possible_move_command = make_shared<PossibleMoveCommand>(this);
	move_command = make_shared<MoveCommand>(this);
    game_over = make_shared<bool>(false);
}

void ViewModel::ObserveUpdate()
{
    *game_over = c_model->GameIsOver();
	Update();
}

