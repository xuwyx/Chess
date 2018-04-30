//
//  ChessBoard.h
//  cppshortterm
//
//  Created by mac on 2017/7/6.
//  Copyright © 2017年 mac. All rights reserved.
//

#ifndef ChessBoard_h
#define ChessBoard_h

class ChessBoard
{
public:
	int chess[8][8];
    static const int WHITE = 0;
    static const int BLACK = 1;
    static const int EMPTY = -1;
public:
	ChessBoard()
	{
		initialize();
	}

	~ChessBoard() = default;

	void initialize()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				chess[i][j] = EMPTY;
			}
		}
        for(int i = 1; i <= 6; i++){
            chess[0][i] = WHITE;
            chess[7][i] = WHITE;
            chess[i][0] = BLACK;
            chess[i][7] = BLACK;
        }
	}
};

#endif /* ChessBoard_h */
