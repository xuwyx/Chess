//
// Created by QZQ on 07/07/2017.
//

#include "Model.h"
#include "AI.h"
#include "../ViewModel/ViewModel.h"
#include "../View/sleep.h"
#include <utility>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

//Model model;
//AI ai;
//extern ViewModel view_model;

extern bool AtHome(int player, int x, int y);

extern bool InBoard(int x, int y);

extern bool AtOwnSide(int player, int x, int y);

extern bool AtOwnSide(int player, int x, int y);

bool Model::EndGame()
{
	cout << "Game Over" << endl;
	return true;
}
bool Model::GameIsOver(){
    return !(alive[0] && alive[1]);
}

void Model::KillPlayer(int player)
{
	int dead_color = player;
	alive[dead_color] = false;
//    for (int i = 0; i < 19; i++)
//        for (int j = 0; j < 19; j++)
//        {
//            if (chess_board->chess[i][j] == dead_color)
//            {
//                chess_board->chess[i][j] = ChessBoard::EMPTY;
//            }
//        }
	GameOver();
}

bool Model::StartGame(int x0, int x1)
{
//	set human player first
	chess_board->initialize();
	for (int i = 0; i < 2; i++)
	{
		AI_play[i] = alive[i] = true;
	}
	AI_play[0] = x0;
    AI_play[1] = ~x0;
    difficulty = x1;
	game_over = false;

	active_player = 0;
    
	AIPlay();
	Update();
	return true;
}

bool Model::IsValidMove(int player, int start_x, int start_y, int end_x, int end_y)
{
	if (player != active_player) return false;
	if (chess_board->chess[start_x][start_y] != player) return false;
	if (chess_board->chess[end_x][end_y] == chess_board->chess[start_x][start_y]) return false;
	return true;
}

void Model::GameOver()
{
	cout << "Game Over!" << endl;
	Update();
}

void Model::MoveChessPiece(int sx, int sy, int ex, int ey)
{
//    if (chess_board->chess[ex][ey] == ChessPiece::Jiang) KillPlayer(chess_board->chess[ex][ey].color);
	chess_board->chess[ex][ey] = chess_board->chess[sx][sy];
	chess_board->chess[sx][sy] = -1;
}

bool Model::PlayerMoveChessPiece(int player, int start_x, int start_y, int end_x, int end_y)
{
	cout << "Local Human Move" << endl;
	if (player != active_player)
	{
		cout << "Error: You are NOT active player." << endl;
		return false;
	}
	if (!alive[player])
	{
		cout << "Error: current player is dead." << endl;
		active_player++;
		active_player %= 2;
		return false;
	}
	if (AI_play[player])
	{
		cout << "Error: That is AI player." << endl;
		return false;
	}
	if (!IsValidMove(player, start_x, start_y, end_x, end_y))
	{
		cout << "Invalid Move." << endl;
		return false;
	}
	auto M = GenerateMove(player, start_x, start_y, chess_board);
	printf("generated possible moves(%d, %d, %d):\n", player, start_x, start_y);
	for (auto i : M) cout << i.first << ' ' << i.second << endl;
	if (find(M.begin(), M.end(), pair<int, int>(end_x, end_y)) == M.end())
	{
		cout << "Invalid human move." << endl;
		return false;
	}
	MoveChessPiece(start_x, start_y, end_x, end_y);

	active_player++;
	active_player %= 2;
	Update();
    AIPlay();
    return true;
}

void Model::AIPlay()
{
	if(AI_play[active_player])
	{
		if (alive[active_player])
		{
            tuple<int, int, int, int> mv = c_AI->getMove(chess_board, active_player, difficulty);
			if (get<0>(mv) == -1)
			{
				alive[active_player] = false;
                KillPlayer(active_player);
//                GameOver();
                return;
			}
			else MoveChessPiece(get<0>(mv), get<1>(mv), get<2>(mv), get<3>(mv));
		}
        Update();
		active_player++;
		active_player %= 2;
	}
}

bool Model::PossibleMove(int player, int x, int y)
{
    *(this->possible_move_pos) = move(GenerateMove(player, x, y, chess_board));
	for (auto i : *possible_move_pos) cout << i.first << ' '  << i.second << endl;
	Update();
    return this->possible_move_pos->size() > 0;
}

PossibleMovePosition Model::GenerateMove(int player, int x, int y, shared_ptr<ChessBoard> chess_board)
{
	vector<pair<int, int>> ret;
	pair<int, int> tp;
    int v=0, h=0, l=0, r=0;
    for (int i = 0; i < 8; i++) {
        if(chess_board->chess[i][y]!=ChessBoard::EMPTY) v++;
        if(chess_board->chess[x][i]!=ChessBoard::EMPTY) h++;
    }
    int x1=x, y1=y;
    while (x1 >= 0 && y1 >= 0) {
        if(chess_board->chess[x1][y1]!=ChessBoard::EMPTY) l++;
        x1--;
        y1--;
    }
    x1=x+1;
    y1=y+1;
    while (x1 <= 7 && y1 <= 7) {
        if(chess_board->chess[x1][y1]!=ChessBoard::EMPTY) l++;
        x1++;
        y1++;
    }
    x1=x;
    y1=y;
    while (x1 <= 7 && y1 >= 0) {
        if(chess_board->chess[x1][y1]!=ChessBoard::EMPTY) r++;
        x1++;
        y1--;
    }
    x1=x-1;
    y1=y+1;
    while (x1 >= 0 && y1 <= 7) {
        if(chess_board->chess[x1][y1]!=ChessBoard::EMPTY) r++;
        x1--;
        y1++;
    }
    if(x + v < 8 && chess_board->chess[x+v][y]!=player) {
        tp.first = x + v;
        tp.second = y;
        ret.push_back(tp);
    }
    if(x - v >= 0 && chess_board->chess[x-v][y]!=player) {
        tp.first = x - v;
        tp.second = y;
        ret.push_back(tp);
    }
    if(y + h < 8 && chess_board->chess[x][y+h]!=player) {
        tp.first = x;
        tp.second = y + h;
        ret.push_back(tp);
    }
    if(y - h >= 0 && chess_board->chess[x][y-h]!=player) {
        tp.first = x;
        tp.second = y - h;
        ret.push_back(tp);
    }
    if(y + l < 8 && x + l < 8 && chess_board->chess[x+l][y+l]!=player) {
        tp.first = x + l;
        tp.second = y + l;
        ret.push_back(tp);
    }
    if(y - l >= 0 && x - l >= 0 && chess_board->chess[x-l][y-l]!=player) {
        tp.first = x - l;
        tp.second = y - l;
        ret.push_back(tp);
    }
    if(x - r >= 0 && y + r < 8 && chess_board->chess[x-r][y+r]!=player) {
        tp.first = x - r;
        tp.second = y + r;
        ret.push_back(tp);
    }
    if(x + r < 8 && y - r >= 0 && chess_board->chess[x+r][y-r]!=player) {
        tp.first = x + r;
        tp.second = y - r;
        ret.push_back(tp);
    }
	return ret;
}
