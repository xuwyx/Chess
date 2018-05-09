#include "view.h"

#define welcome 1

View::View()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    if(welcome) wel = new M1_welcome;
    w = new MainWindow;
}

View::~View()
{
    delete w;
}

void View::ObserveUpdate()
{
    w->refresh();
}

void View::ConnectStartCmd(std::shared_ptr<Command> psc)
{
    sc = psc;
    w->ConnectStartCmd(sc);
}

void View::ConnectMoveCmd(std::shared_ptr<Command> pmc)
{
    mc = pmc;
    w->ConnectMoveCmd(mc);
}

void View::ConnectChooseCmd(std::shared_ptr<Command> pcc)
{
    cc = pcc;
    w->ConnectChooseCmd(cc);
}

void View::ConnectChessBoard(std::shared_ptr<ChessBoard> pcb)
{
    cb = pcb;
    w->ConnectChessBoard(cb);
}

void View::ConnectPossibleMove(std::shared_ptr<PossibleMovePosition> ppmp)
{
    pmp = ppmp;
    w->ConnectPossibleMove(pmp);
}

void View::ConnectGameOver(std::shared_ptr<int> pgo)
{
    w->ConnectGameOver(pgo);
}

void View::ConnectTimer(std::shared_ptr<int> t)
{
    w->ConnectTimer(t);
}

void View::ConnectQuitGame(QApplication *a)
{
    w->ConnectQuitGame(a);
}

void View::run()
{
    if(welcome)
    {
        while(!(wel->Stop())) sleep(100);
        delete wel;
        wel = NULL;
    }
    w->show();
}
