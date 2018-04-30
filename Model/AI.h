#ifndef AI_TEST_H
#define AI_TEST_H

#include <tuple>
#include <memory>
#include <QFile>
#include <cstdlib>
#include <iostream>
#include "../ChessBoard.h"

typedef struct move_ai_test
{
    int sx, sy, ex, ey;
} Move_ai_test;

class AI
{
public:
    AI();
    std::tuple<int,int,int,int> getMove(std::shared_ptr<ChessBoard>,int,int);

private://func
    void initializeInfo(std::shared_ptr<ChessBoard>);
    void generateMoveList(int tcb[8][8], Move_ai_test tmvlst[195], int &tmove_num,int p);
    Move_ai_test normalizeMove(move_ai_test);
//    int Evaluate(int tcb[8][8], Move_ai_test tmvlst[195], int tmove_num);
//    int judgeMove(Move_ai_test mat);
//    void readValue();
    Move_ai_test easyMode();
    Move_ai_test normalMode();
    Move_ai_test hardMode();
    std::vector<std::pair<int, int>> GenerateMove(int player, int x, int y, int tcb[8][8]);

private://var
    int cb[8][8];
    Move_ai_test mvlst[195];
    int cp_num[4];
    int move_num;
    int player;
    int jushi;
};

#endif // AI_TEST_H
