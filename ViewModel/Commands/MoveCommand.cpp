//
// Created by QZQ on 10/07/2017.
//

#include "MoveCommand.h"
#include "../ViewModel.h"
//#include<QDebug>

using namespace std;

bool MoveCommand::execute()
{
	cout << "execute MoveCommand" << endl;
	auto v = any_cast<std::vector<int>>(*param);
	sx = v[0];
	sy = v[1];
	ex = v[2];
	ey = v[3];
	player = view_model->chess_board->chess[sx][sy];
    view_model->possible_move_pos->clear();
	bool rt = view_model->MoveChessPiece(player, sx, sy, ex, ey);
//	view_model->Update();
	return rt;
}
