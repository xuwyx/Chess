//
// Created by QZQ on 10/07/2017.
//

#include "PossibleMoveCommand.h"
#include "../ViewModel.h"

PossibleMoveCommand::PossibleMoveCommand(ViewModel * vm) : DerivedCommand(vm)
{

}

bool PossibleMoveCommand::execute()
{
	auto v = any_cast<std::vector<int>>(*param);
	sx = v[0];
	sy = v[1];
	player = view_model->chess_board->chess[sx][sy];
    if(player == ChessBoard::EMPTY) return false;
	bool rt = view_model->PossibleMove(player, sx, sy);
//	view_model->Update();
	return rt;
}
