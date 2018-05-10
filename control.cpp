#include "control.h"

using namespace std;

Control::Control(QApplication *a)
{
    v = make_shared<View>();
    m = make_shared<Model>();
    vm = make_shared<ViewModel>();
    
    vm->ConnectModel(m);
    m->RegisterObserver(vm);
    vm->RegisterObserver(v);
    v->ConnectStartCmd(vm->start_command);
    v->ConnectMoveCmd(vm->move_command);
    v->ConnectChooseCmd(vm->possible_move_command);
    v->ConnectChessBoard(vm->chess_board);
    v->ConnectPossibleMove(vm->possible_move_pos);
    v->ConnectGameOver(vm->game_over);
    v->ConnectTimer(vm->time);
    v->ConnectQuitGame(a);
    v->run();
}
