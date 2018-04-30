#include "AI.h"
#include <QDebug>

//#define KaiJuBiaoZhun 14
//#define CanJuBiaoZhun 5

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

//int AI::judgeMove(Move_ai_test mat)
//{
//    int tcb[8][8];
//    Pos_ai_test tcp[4][16];
//    Move_ai_test mvlst_next[195];
//    int move_num_next=0;
//    int value=0;
//
//    if(cb[mat.ex][mat.ey].type != -1 && cb[mat.ex][mat.ey].team != -1) value = chizifen[cb[mat.ex][mat.ey].type];
//    for(int i = 0; i < 23; i++) for(int j = 0; j < 23; j++) tcb[i][j] = cb[i][j];
//    for(int i = 0; i < 4; i++) for(int j = 0; j < 16; j++) tcp[i][j] = cp[i][j];
//    if(tcb[mat.ex][mat.ey].team != -1)
//        for(int i = 0; i < 16; i++)
//            if(tcp[tcb[mat.ex][mat.ey].team][i].x == mat.ex && tcp[tcb[mat.ex][mat.ey].team][i].y == mat.ey)
//                tcp[tcb[mat.ex][mat.ey].team][i].x = tcp[tcb[mat.ex][mat.ey].team][i].y = -1;
//    for(int i = 0; i < 16; i++)
//        if(tcp[tcb[mat.sx][mat.sy].team][i].x == mat.sx && tcp[tcb[mat.sx][mat.sy].team][i].y == mat.sy)
//        {
//            tcp[tcb[mat.sx][mat.sy].team][i].x = mat.ex; tcp[tcb[mat.sx][mat.sy].team][i].y = mat.ey;
//        }
//
//    tcb[mat.ex][mat.ey] = tcb[mat.sx][mat.sy]; tcb[mat.sx][mat.sy].team = tcb[mat.sx][mat.sy].type = -1;
//    generateMoveList(tcb, tcp, mvlst_next, move_num_next, player);
//
//    value += Evaluate(tcb, tcp, mvlst_next, move_num_next);
//    return value;
//}

//int AI::Evaluate(int tcb[23][23], Move_ai_test *tmvlst, int tmove_num)
//{
//    int value=0;
//qdebug()<<"@"<<value;
//    for(int i = 0; i < 16; i++)//子力
//        if(tcp[player][i].x != -1)
//            switch (i) {
//            case 0:
//                value = value + zili[0] + zishi[0][tcp[player][i].x][tcp[player][i].y];
//                break;
//            case 1:case 2:
//                value = value + zili[1] + zishi[1][tcp[player][i].x][tcp[player][i].y];
//                break;
//            case 3:case 4:
//                value = value + zili[2] + zishi[2][tcp[player][i].x][tcp[player][i].y];
//                break;
//            case 5:case 6:
//                value = value + zili[3] + zishi[3][tcp[player][i].x][tcp[player][i].y];
//                break;
//            case 7:case 8:
//                value = value + zili[4] + zishi[4][tcp[player][i].x][tcp[player][i].y];
//                break;
//            case 9:case 10:
//                value = value + zili[5] + zishi[5][tcp[player][i].x][tcp[player][i].y];
//                break;
//            default:
//                value = value + zili[6] + zishi[6][tcp[player][i].x][tcp[player][i].y];
//                break;
//            }
//qdebug()<<"#"<<value;
//    for(int i = 0; i < tmove_num; i++)
//    {
//        //qdebug()<<"$"<<tmvlst[i].sx<<" "<<tmvlst[i].sy<<" "<<tmvlst[i].ex<<" "<<tmvlst[i].ey;
//        value += jidong[tcb[tmvlst[i].sx][tmvlst[i].sy].type];
//        if(tcb[tmvlst[i].ex][tmvlst[i].ey].type != -1) value += kongzhi[tcb[tmvlst[i].ex][tmvlst[i].ey].type];
//    }
//    return value;
//}

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
        tp.first = x + v;
        tp.second = y;
        ret.push_back(tp);
    }
    if(x - v >= 0 && tcb[x-v][y]!=player) {
        tp.first = x - v;
        tp.second = y;
        ret.push_back(tp);
    }
    if(y + h < 8 && tcb[x][y+h]!=player) {
        tp.first = x;
        tp.second = y + h;
        ret.push_back(tp);
    }
    if(y - h >= 0 && tcb[x][y-h]!=player) {
        tp.first = x;
        tp.second = y - h;
        ret.push_back(tp);
    }
    if(y + l < 8 && x + l < 8 && tcb[x+l][y+l]!=player) {
        tp.first = x + l;
        tp.second = y + l;
        ret.push_back(tp);
    }
    if(y - l >= 0 && x - l >= 0 && tcb[x-l][y-l]!=player) {
        tp.first = x - l;
        tp.second = y - l;
        ret.push_back(tp);
    }
    if(x - r >= 0 && y + r < 8 && tcb[x-r][y+r]!=player) {
        tp.first = x - r;
        tp.second = y + r;
        ret.push_back(tp);
    }
    if(x + r < 8 && y - r >= 0 && tcb[x+r][y-r]!=player) {
        tp.first = x + r;
        tp.second = y - r;
        ret.push_back(tp);
    }
    return ret;
}

    
//void AI::readValue()
//{
//    int pl_num = (cp_num[0]!=0?1:0) + (cp_num[1]!=0?1:0) + (cp_num[2]!=0?1:0) + (cp_num[3]!=0?1:0);
//    int avg_cp_num = (cp_num[0]+cp_num[1]+cp_num[2]+cp_num[3]) / pl_num;
//
//    if(avg_cp_num >= KaiJuBiaoZhun) jushi = 0;//开局
//    else if(avg_cp_num <= CanJuBiaoZhun) jushi = 2;//残局
//    else jushi = 1;//中局
//
//    QFile fzili(":/value/src/value/zili"+QString::number(jushi)+".txt");
//    QFile fzishi(":/value/src/value/zishi"+QString::number(jushi)+".txt");
//    QFile fjidong(":/value/src/value/jidong"+QString::number(jushi)+".txt");
//    QFile fkongzhi(":/value/src/value/kongzhi"+QString::number(jushi)+".txt");
//    if(!fzili.open(QIODevice::ReadOnly | QIODevice::Text)) return;
//    if(!fzishi.open(QIODevice::ReadOnly | QIODevice::Text)) return;
//    if(!fjidong.open(QIODevice::ReadOnly | QIODevice::Text)) return;
//    if(!fkongzhi.open(QIODevice::ReadOnly | QIODevice::Text)) return;
//    QTextStream iszili(&fzili),iszishi(&fzishi),isjidong(&fjidong),iskongzhi(&fkongzhi);
//    for(int i = 0; i < 7; i++)
//    {
//        iszili >> zili[i];
//        for(int j = 0; j < 23; j++)
//            for(int k = 0; k < 23; k++)
//                iszishi >> zishi[i][j][k];
//        isjidong >> jidong[i];
//        iskongzhi >> kongzhi[i];
//    }
//    fzili.close();fzishi.close();fjidong.close();fkongzhi.close();
//
//    chizifen[0] = 3000; chizifen[1] = 300; chizifen[2] = 450; chizifen[3] = 1500; chizifen[4] = 900;
//    chizifen[5] = 1200; chizifen[6] = 300;
//}

