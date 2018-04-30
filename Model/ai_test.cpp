#include "ai_test.h"
#include <cstdlib>
using namespace std;
AI_test::AI_test()
{

}

tuple<int, int, int, int> AI_test::getMove(std::shared_ptr<ChessBoard> cbdata, int p)
{
    initializeInfo(cbdata);
    generateMoveList(p);

    return mvlst[rand() % move_num].normalize();
}

void AI_test::initializeInfo(std::shared_ptr<ChessBoard> cbdata)
{
    int i, j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 16; j++) cp[i][j].x = cp[i][j].y = -1;
    for(i = 0; i < 23; i++)
        for(j = 0; j < 23; j++)
        {
            if(i<2 || i>20 || j<2 || j>20 || (i<7&&j<7) || (i<7&&j>15) || (i>15&&j<7) || (i>15&&j>15))
                cb[i][j].valid = 100;//unarrivable
            else
            {
                if((i<5&&j>9&&j<13) || (j<5&&i>9&&i<13) || (i>17&&j>9&&j<13) || (j>17&&i>9&&i<13)) cb[i][j].valid = 0; //九宫
                else if((i<7) || (j<7) || (i>15) || (j>15)) cb[i][j].valid = 2; //象可走
                else cb[i][j].valid = 3;
                cb[i][j].team = cbdata->chess[i-2][j-2];
                cb[i][j].type = cbdata->chess[i-2][j-2];
                if(cb[i][j].team != -1)
                {
                    int k = cbdata->chess[i-2][j-2];
                    switch (k) {
                    case 0:
                        cp[cb[i][j].team][0].x = i;
                        cp[cb[i][j].team][0].y = j;
                        break;
                    case 1:
                        if(cp[cb[i][j].team][1].x == -1)
                        {
                            cp[cb[i][j].team][1].x = i;
                            cp[cb[i][j].team][1].y = j;
                        }
                        else
                        {
                            cp[cb[i][j].team][2].x = i;
                            cp[cb[i][j].team][2].y = j;
                        }
                        break;
                    case 2:
                        if(cp[cb[i][j].team][3].x == -1)
                        {
                            cp[cb[i][j].team][3].x = i;
                            cp[cb[i][j].team][3].y = j;
                        }
                        else
                        {
                            cp[cb[i][j].team][4].x = i;
                            cp[cb[i][j].team][4].y = j;
                        }
                        break;
                    case 3:
                        if(cp[cb[i][j].team][5].x == -1)
                        {
                            cp[cb[i][j].team][5].x = i;
                            cp[cb[i][j].team][5].y = j;
                        }
                        else
                        {
                            cp[cb[i][j].team][6].x = i;
                            cp[cb[i][j].team][6].y = j;
                        }
                        break;
                    case 4:
                        if(cp[cb[i][j].team][7].x == -1)
                        {
                            cp[cb[i][j].team][7].x = i;
                            cp[cb[i][j].team][7].y = j;
                        }
                        else
                        {
                            cp[cb[i][j].team][8].x = i;
                            cp[cb[i][j].team][8].y = j;
                        }
                        break;
                    case 5:
                        if(cp[cb[i][j].team][9].x == -1)
                        {
                            cp[cb[i][j].team][9].x = i;
                            cp[cb[i][j].team][9].y = j;
                        }
                        else
                        {
                            cp[cb[i][j].team][10].x = i;
                            cp[cb[i][j].team][10].y = j;
                        }
                        break;
                    case 6:
                        if(cp[cb[i][j].team][11].x == -1)
                        {
                            cp[cb[i][j].team][11].x = i;
                            cp[cb[i][j].team][11].y = j;
                        }
                        else if(cp[cb[i][j].team][12].x == -1)
                        {
                            cp[cb[i][j].team][12].x = i;
                            cp[cb[i][j].team][12].y = j;
                        }
                        else if(cp[cb[i][j].team][13].x == -1)
                        {
                            cp[cb[i][j].team][13].x = i;
                            cp[cb[i][j].team][13].y = j;
                        }
                        else if(cp[cb[i][j].team][14].x == -1)
                        {
                            cp[cb[i][j].team][14].x = i;
                            cp[cb[i][j].team][14].y = j;
                        }
                        else
                        {
                            cp[cb[i][j].team][15].x = i;
                            cp[cb[i][j].team][15].y = j;
                        }
                        break;
                    }
                }
            }
        }
}

void AI_test::generateMoveList(int p)
{
    move_num = 0;
    for(int i = 0; i < 1; i++)//将
        if(cp[p][i].x != -1)
        {
            int l[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};
            for(int j = 0; j < 4; j++)
            {
                int x = cp[p][i].x + l[j][0], y = cp[p][i].y + l[j][1];
                if(cb[x][y].valid<=0 && cb[x][y].team != p)
                {
                    mvlst[move_num].sx = cp[p][i].x; mvlst[move_num].sy = cp[p][i].y;
                    mvlst[move_num].ex = x; mvlst[move_num].ey = y;
                    move_num++;
                }
            }
        }
    for(int i = 1; i < 3; i++)//士
        if(cp[p][i].x != -1)
        {
            int l[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
            for(int j = 0; j < 4; j++)
            {
                int x = cp[p][i].x + l[j][0], y = cp[p][i].y + l[j][1];
                if(cb[x][y].valid<=1 && cb[x][y].team != p)
                {
                    mvlst[move_num].sx = cp[p][i].x; mvlst[move_num].sy = cp[p][i].y;
                    mvlst[move_num].ex = x; mvlst[move_num].ey = y;
                    move_num++;
                }
            }
        }
    for(int i = 3; i < 5; i++)//象
        if(cp[p][i].x != -1)
        {
            int l[4][2] = {{2,2},{2,-2},{-2,2},{-2,-2}};
            for(int j = 0; j < 4; j++)
            {
                int x = cp[p][i].x + l[j][0], y = cp[p][i].y + l[j][1];
                if(cb[x][y].valid<=2 && cb[x][y].team != p)
                {
                    mvlst[move_num].sx = cp[p][i].x; mvlst[move_num].sy = cp[p][i].y;
                    mvlst[move_num].ex = x; mvlst[move_num].ey = y;
                    move_num++;
                }
            }
        }
    for(int i = 5; i < 7; i++)//车
        if(cp[p][i].x != -1)
        {
            int l[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};
            for(int j = 0; j < 4; j++)
            {
                int x = cp[p][i].x + l[j][0], y = cp[p][i].y + l[j][1];
                while(cb[x][y].valid<=3 && cb[x][y].team != p)
                {
                    mvlst[move_num].sx = cp[p][i].x; mvlst[move_num].sy = cp[p][i].y;
                    mvlst[move_num].ex = x; mvlst[move_num].ey = y;
                    move_num++;
                    if(cb[x][y].team != -1) break;
                    x = x + l[j][0]; y = y + l[j][1];
                }
            }
        }
    for(int i = 7; i < 9; i++)//马
        if(cp[p][i].x != -1)
        {
            int l[8][2] = {{2,1},{2,-1},{1,2},{1,-2},{-1,2},{-1,-2},{-2,-1},{-2,1}};
            for(int j = 0; j < 8; j++)
            {
                int x = cp[p][i].x + l[j][0], y = cp[p][i].y + l[j][1];
                if(cb[x][y].valid<=4 && cb[x][y].team != p)
                {
                    mvlst[move_num].sx = cp[p][i].x; mvlst[move_num].sy = cp[p][i].y;
                    mvlst[move_num].ex = x; mvlst[move_num].ey = y;
                    move_num++;
                }
            }
        }
    for(int i = 9; i < 11; i++)//炮
        if(cp[p][i].x != -1)
        {
            int l[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};
            for(int j = 0; j < 4; j++)
            {
                int x = cp[p][i].x + l[j][0], y = cp[p][i].y + l[j][1];
                while(cb[x][y].valid<=5 && cb[x][y].team == -1)
                {
                    mvlst[move_num].sx = cp[p][i].x; mvlst[move_num].sy = cp[p][i].y;
                    mvlst[move_num].ex = x; mvlst[move_num].ey = y;
                    move_num++;
                    x = x + l[j][0]; y = y + l[j][1];
                }
                do
                {
                    x = x + l[j][0]; y = y + l[j][1];
                } while(cb[x][y].valid<=5 && cb[x][y].team == -1);
                if(cb[x][y].valid<=5 && cb[x][y].team != p)
                {
                    mvlst[move_num].sx = cp[p][i].x; mvlst[move_num].sy = cp[p][i].y;
                    mvlst[move_num].ex = x; mvlst[move_num].ey = y;
                    move_num++;
                }
            }
        }
    for(int i = 11; i < 16; i++)//兵
        if(cp[p][i].x != -1)
        {
            int l[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};
            int x = cp[p][i].x, y = cp[p][i].y;
            if((p==0&&y<7) || (p==1&&x>15) || (p==2&&y>15) || (p==4&&x<7))
            {
                int ex = x + l[p][0], ey = y + l[p][1];
                if(cb[ex][ey].valid<=5 && cb[ex][ey].team != p)
                {
                    mvlst[move_num].sx = x; mvlst[move_num].sy = y;
                    mvlst[move_num].ex = ex; mvlst[move_num].ey = ey;
                    move_num++;
                }
            }
            else if(x>=7 && y>=7 && x<=15 && y<=15)
            {
                for(int j=-1; j<2; j++)
                {
                    int ex = x + l[(p+j+4)%4][0], ey = y + l[(p+j+4)%4][1];
                    if(cb[ex][ey].valid<=5 && cb[ex][ey].team != p)
                    {
                        mvlst[move_num].sx = x; mvlst[move_num].sy = y;
                        mvlst[move_num].ex = ex; mvlst[move_num].ey = ey;
                        move_num++;
                    }
                }
            }
            else
            {
                int tp;
                if(y<7) tp=2;if(x<7) tp=1;if(x>15) tp=3;if(y>15) tp=0;
                for(int j=-1; j<2; j++)
                {
                    int ex = x + l[(tp+j+4)%4][0], ey = y + l[(tp+j+4)%4][1];
                    if(cb[ex][ey].valid<=5 && cb[ex][ey].team != p)
                    {
                        mvlst[move_num].sx = x; mvlst[move_num].sy = y;
                        mvlst[move_num].ex = ex; mvlst[move_num].ey = ey;
                        move_num++;
                    }
                }
            }
        }
}
