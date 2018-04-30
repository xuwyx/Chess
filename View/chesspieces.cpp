#include "chesspieces.h"
#include "ui_chesspieces.h"

ChessPieces::ChessPieces(QWidget *parent) : QWidget(parent), ui(new Ui::ChessPieces)
{
    ui->setupUi(this);

    cb = NULL;

    setGeometry(0,0,parent->width(),parent->height());
    setParent(parent);

    PicSrc[0] = std::make_shared<QPixmap>(":/chesspiece/src/pic/black.png");
    PicSrc[1] = std::make_shared<QPixmap>(":/chesspiece/src/pic/white.png");
}

ChessPieces::~ChessPieces()
{
    delete ui;
}

void ChessPieces::paintEvent(QPaintEvent *pEvent)
{
    QPainter painter(this);
    painter.setFont(font);

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
        {
            int color;
            getColor(i, j, color);
            if(color != ChessBoard::EMPTY)
            {
                double w = width() / 18.0;
                double h = height() / 18.0;
                painter.drawPixmap(i*(2*w)+w, j*(2*h)+h, w*2, h*2, *(PicSrc[color]));
            }
        }
}

void ChessPieces::getColor(int x, int y, int &color)
{
    if(cb == NULL)
    {
        color = ChessBoard::EMPTY;
        return;
    }
    color = cb->chess[x][y];
}

void ChessPieces::ConnectChessBoard(std::shared_ptr<ChessBoard> pcb)
{
    cb = pcb;
}
