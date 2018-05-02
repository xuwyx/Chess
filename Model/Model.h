//
// Created by QZQ on 07/07/2017.
//

#ifndef CHINESECHESS_MODEL_H
#define CHINESECHESS_MODEL_H


#include "../ChessBoard.h"
#include "../possiblemoveposition.h"
#include <iostream>
#include "AI.h"
#include "../Observer.h"
#include <QtNetwork/QTcpSocket>
#include <memory>


class Model : public QObject
{
    Q_OBJECT
public:
	std::shared_ptr<ChessBoard> chess_board;
	std::shared_ptr<PossibleMovePosition> possible_move_pos;
	std::shared_ptr<AI> c_AI;
    bool AI_play[2];
    int difficulty;
	bool alive[2];
    int cnt[2]; // 记录棋子数目

	Model()
	{
		possible_move_pos = std::make_shared<PossibleMovePosition>();
		chess_board = std::make_shared<ChessBoard>();
		c_AI = std::make_shared<AI>();
		for (int i = 0; i < 2; i++)
		{
			AI_play[i] = alive[i] = true;
            cnt[i]=12;
		}
		AI_play[0] = false;
//        game_over = false;
	}

	~Model(){}

	void setAI(int player, bool is_AI)
	{
		if (player < 0 || player > 1)
		{
			std::cerr << "wrong player" << std::endl;
		}
		AI_play[player] = is_AI;
	}

	bool StartGame(int x0, int x1);

	void KillPlayer(int player);

//	not complete
	bool EndGame();

//	only local human player call this function
	bool PlayerMoveChessPiece(int player, int start_x, int start_y, int end_x, int end_y);

	void MoveChessPiece(int sx, int sy, int ex, int ey);

	void AIPlay();

	bool PossibleMove(int player, int x, int y);

	bool IsValidMove(int player, int start_x, int start_y, int end_x, int end_y);

    std::vector<std::pair<int, int>> GenerateMove(int player, int x, int y, std::shared_ptr<ChessBoard> chess_board);

	void Update()
	{
		for (auto i : register_list) i->ObserveUpdate();
	}

	void RegisterObserver(std::shared_ptr<Observer> ob)
	{ register_list.push_back(ob); }
    
    int GameIsOver();
    
    bool isBlock(int p);
private:
	int active_player;
//    bool game_over;

	std::vector<std::shared_ptr<Observer>> register_list;

};


#endif //CHINESECHESS_MODEL_H
