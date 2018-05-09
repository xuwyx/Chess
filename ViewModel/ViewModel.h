//
// Created by QZQ on 07/07/2017.
//

#ifndef CHINESECHESS_VIEWMODEL_H
#define CHINESECHESS_VIEWMODEL_H


#include "../command.h"
#include "../ChessBoard.h"
#include "../Model/Model.h"
#include "../Observer.h"
#include "../possiblemoveposition.h"
#include <memory>

class Model;

class AI;

class ViewModel : public Observer
{
public:
    std::shared_ptr<int> game_over;
    std::shared_ptr<int> time;
    std::shared_ptr<Command> start_command, move_command, possible_move_command;
	std::shared_ptr<ChessBoard> chess_board;
//    std::vector<std::pair<int, int>> possible_move_pos;
	std::shared_ptr<PossibleMovePosition> possible_move_pos;

	ViewModel();

	~ViewModel()
	{
		std::cout << "dstc ViewModel" << std::endl;
	}

	void Update()
	{
		for (auto i : register_list) i->ObserveUpdate();
	}

	void RegisterObserver(std::shared_ptr<Observer> ob)
	{ register_list.push_back(ob); }

	bool GameIsOver();

	void SetAIPlayer(int player, bool is_AI);

	void ConnectModel(std::shared_ptr<Model> model);

	bool StartGame(int x0, int x1)
    {
        return c_model->StartGame(x0, x1);
	}

	bool MoveChessPiece(int player, int sx, int sy, int ex, int ey)
	{
		return c_model->PlayerMoveChessPiece(player, sx, sy, ex, ey);
	}

	bool PossibleMove(int player, int sx, int sy)
	{
		return c_model->PossibleMove(player, sx, sy);
	}

	virtual void ObserveUpdate() override;

//    void GenerateCommands(std::shared_ptr<ViewModel> vm);
private:
	std::vector<std::shared_ptr<Observer>> register_list;
	std::shared_ptr<Model> c_model;
};


#endif //CHINESECHESS_VIEWMODEL_H
