#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <QWidget>
#include <QPainter>
#include <memory>
#include "viewchessboard.h"
#include "../ChessBoard.h"

namespace Ui {
class ChessPieces;
}

class ChessPieces : public QWidget
{
    Q_OBJECT

public:
    explicit ChessPieces(QWidget *parent = 0);
    ~ChessPieces();
    void paintEvent(QPaintEvent*);
    void ConnectChessBoard(std::shared_ptr<ChessBoard>);

private:
    void getColor(int,int,int&);

private:
    Ui::ChessPieces *ui;
    int pieceNum;
    std::shared_ptr<QPixmap> PicSrc[2];
    QFont font;
    std::shared_ptr<ChessBoard> cb;
};

#endif // CHESSPIECES_H
