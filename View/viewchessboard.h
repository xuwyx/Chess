#ifndef VIEWCHESSBOARD_H
#define VIEWCHESSBOARD_H

#include <QWidget>
#include <QLabel>
#include <QTime>
#include <memory>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <vector>
#include <utility>
#include "../command.h"
#include "../possiblemoveposition.h"

namespace Ui {
class viewChessBoard;
}

class viewChessBoard : public QWidget
{
    Q_OBJECT

public:
    friend class ChessPieces;
    explicit viewChessBoard(QWidget *parent = 0);
    ~viewChessBoard();
    enum backPicture{Wood, Starry, Beach, Random};
    void changeBackGround(viewChessBoard::backPicture);
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    int choose(int,int);
    void move(int,int);
    void ConnectMoveCmd(std::shared_ptr<Command>);
    void ConnectChooseCmd(std::shared_ptr<Command>);
    void ConnectPossibleMove(std::shared_ptr<PossibleMovePosition>);

private:
    Ui::viewChessBoard *ui;
    std::shared_ptr<QPixmap> wood, starry, beach;
    enum backPicture bp;
    std::shared_ptr<QColor> line, chosen, arrivable;
    std::shared_ptr<Command> mc,cc;
    std::shared_ptr<PossibleMovePosition> pmp;
    int chooseStatus, cx, cy;
};

#endif // VIEWCHESSBOARD_H
