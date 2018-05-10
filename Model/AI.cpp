#include "AI.h"

std::tuple<int,int,int,int> Normalize(Move_ai_test mat)
{
    return std::make_tuple(mat.sx,mat.sy,mat.ex,mat.ey);
}

AI::AI()
{

}

std::tuple<int,int,int,int> AI::getMove(std::shared_ptr<ChessBoard> cbdata, int p, int difficulty)
{
    Move_ai_test mv;
    player = p;
    initializeInfo(cbdata);
    generateMoveList(cb,mvlst,move_num,player);

    switch (difficulty) {
    case 0:
        mv = easyMode();
        break;
    case 1:
        mv = normalMode();
        break;
    default:
        mv = hardMode();
        break;
    }
    return Normalize(mv);
}

Move_ai_test AI::easyMode()
{
    return mvlst[rand()%move_num];
}

Move_ai_test AI::normalMode()
{
    return mvlst[rand()%move_num];
}

Move_ai_test AI::hardMode()
{
    return mvlst[rand()%move_num];
}

void AI::initializeInfo(std::shared_ptr<ChessBoard> c){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++)
            cb[i][j]=c->chess[i][j];
    }
}

void AI::generateMoveList(int tcb[8][8], Move_ai_test tmvlst[195], int &tmove_num, int p)
{
    tmove_num = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tcb[i][j]==p) {
                std::vector<std::pair<int, int>> pmp = GenerateMove(p, i, j, tcb);
                for(auto k : pmp){
                    tmvlst[tmove_num].sx=i;
                    tmvlst[tmove_num].sy=j;
                    tmvlst[tmove_num].ex=k.first;
                    tmvlst[tmove_num].ey=k.second;
                    tmove_num++;
                }
            }
        }
    }
}

    
std::vector<std::pair<int, int>> AI::GenerateMove(int player, int x, int y, int tcb[8][8])
{
    std::vector<std::pair<int, int>> ret;
    if(tcb[x][y] != player) return ret;
    std::pair<int, int> tp;
    int v=0, h=0, l=0, r=0;
    for (int i = 0; i < 8; i++) {
        if(tcb[i][y]!=ChessBoard::EMPTY) v++;
        if(tcb[x][i]!=ChessBoard::EMPTY) h++;
    }
    int x1=x, y1=y;
    while (x1 >= 0 && y1 >= 0) {
        if(tcb[x1][y1]!=ChessBoard::EMPTY) l++;
        x1--;
        y1--;
    }
    x1=x+1;
    y1=y+1;
    while (x1 <= 7 && y1 <= 7) {
        if(tcb[x1][y1]!=ChessBoard::EMPTY) l++;
        x1++;
        y1++;
    }
    x1=x;
    y1=y;
    while (x1 <= 7 && y1 >= 0) {
        if(tcb[x1][y1]!=ChessBoard::EMPTY) r++;
        x1++;
        y1--;
    }
    x1=x-1;
    y1=y+1;
    while (x1 >= 0 && y1 <= 7) {
        if(tcb[x1][y1]!=ChessBoard::EMPTY) r++;
        x1--;
        y1++;
    }
    if(x + v < 8 && tcb[x+v][y]!=player) {
        bool flag = true;
        for(int i = 1; i < v; i++){
            if(tcb[x+i][y]==!player){
                flag = false;
                break;
            }
        }
        if(flag){
            tp.first = x + v;
            tp.second = y;
            ret.push_back(tp);
        }
    }
    if(x - v >= 0 && tcb[x-v][y]!=player) {
        bool flag = true;
        for(int i = 1; i < v; i++){
            if(tcb[x-i][y]==!player){
                flag = false;
                break;
            }
        }
        if(flag){
            tp.first = x - v;
            tp.second = y;
            ret.push_back(tp);
        }
    }
    if(y + h < 8 && tcb[x][y+h]!=player) {
        bool flag = true;
        for(int i = 1; i < h; i++){
            if(tcb[x][y+i]==!player){
                flag = false;
                break;
            }
        }
        if(flag){
            tp.first = x;
            tp.second = y + h;
            ret.push_back(tp);
        }
    }
    if(y - h >= 0 && tcb[x][y-h]!=player) {
        bool flag = true;
        for(int i = 1; i < h; i++){
            if(tcb[x][y-i]==!player){
                flag = false;
                break;
            }
        }
        if(flag){
            tp.first = x;
            tp.second = y - h;
            ret.push_back(tp);
        }
    }
    if(y + l < 8 && x + l < 8 && tcb[x+l][y+l]!=player) {
        bool flag = true;
        for(int i = 1; i < l; i++){
            if(tcb[x+i][y+i]==!player){
                flag = false;
                break;
            }
        }
        if(flag){
            tp.first = x + l;
            tp.second = y + l;
            ret.push_back(tp);
        }
    }
    if(y - l >= 0 && x - l >= 0 && tcb[x-l][y-l]!=player) {
        bool flag = true;
        for(int i = 1; i < l; i++){
            if(tcb[x-i][y-i]==!player){
                flag = false;
                break;
            }
        }
        if(flag){
            tp.first = x - l;
            tp.second = y - l;
            ret.push_back(tp);
        }
    }
    if(x - r >= 0 && y + r < 8 && tcb[x-r][y+r]!=player) {
        bool flag = true;
        for(int i = 1; i < r; i++){
            if(tcb[x-i][y+i]==!player){
                flag = false;
                break;
            }
        }
        if(flag){
            tp.first = x - r;
            tp.second = y + r;
            ret.push_back(tp);
        }
    }
    if(x + r < 8 && y - r >= 0 && tcb[x+r][y-r]!=player) {
        bool flag = true;
        for(int i = 1; i < r; i++){
            if(tcb[x+i][y-i]==!player){
                flag = false;
                break;
            }
        }
        if(flag){
            tp.first = x + r;
            tp.second = y - r;
            ret.push_back(tp);
        }
    }
    return ret;
}
