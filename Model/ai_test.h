#ifndef AI_TEST_H
#define AI_TEST_H

#include <tuple>
#include <memory>
#include "../ChessBoard.h"

typedef struct posinfo_ai_test
{
    int team, type, valid;
} Posinfo_ai_test;
typedef struct pos_ai_test
{
    int x, y;
} Pos_ai_test;
typedef struct move_ai_test
{
    int sx, sy, ex, ey;
    std::tuple<int,int,int,int> normalize() { return std::make_tuple(sx,sy,ex,ey); }
} Move_ai_test;

class AI_test
{
public:
    AI_test();
    std::tuple<int, int, int, int> getMove(std::shared_ptr<ChessBoard>,int);

private://func
    void initializeInfo(std::shared_ptr<ChessBoard>);
    void generateMoveList(int);
    move_ai_test normalizeMove(move_ai_test);

private://var
    Posinfo_ai_test cb[23][23];
    Pos_ai_test cp[4][16];
    move_ai_test mvlst[195];
    int move_num;
};

#endif // AI_TEST_H
