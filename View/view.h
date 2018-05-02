#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include <vector>
#include "m1_welcome.h"
#include "mainwindow.h"
#include "../Observer.h"
#include "../command.h"
#include "../ChessBoard.h"
#include "../possiblemoveposition.h"

class ViewModel;

class View : public Observer
{
public:
    View();
    ~View();
    void ConnectStartCmd(std::shared_ptr<Command>);
    void ConnectMoveCmd(std::shared_ptr<Command>);
    void ConnectChooseCmd(std::shared_ptr<Command>);
    void ConnectChessBoard(std::shared_ptr<ChessBoard>);
    void ConnectPossibleMove(std::shared_ptr<PossibleMovePosition>);
    void ConnectOnlineCmd(std::shared_ptr<Command>);
    void ConnectGameOver(std::shared_ptr<int>);
    void ConnectQuitGame(QApplication *a);
    void ObserveUpdate();
    void run();

private:
    M1_welcome *wel;
    MainWindow *w;
    std::shared_ptr<Command> sc,mc,cc,oc;
    std::shared_ptr<ChessBoard> cb;
    std::shared_ptr<PossibleMovePosition> pmp;
};

#endif // VIEW_H
