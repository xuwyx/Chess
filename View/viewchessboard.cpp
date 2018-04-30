#include "viewchessboard.h"
#include "ui_viewchessboard.h"
#include <QDebug>

#define TestViewChessBoard 0

int dis(int x1,int y1, int x2, int y2)
{
    int k = (int)sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return k;
}

viewChessBoard::viewChessBoard(QWidget *parent) : QWidget(parent), ui(new Ui::viewChessBoard)
{
if(TestViewChessBoard) qDebug("Construct: viewChessBoard.");
    ui->setupUi(this);

    mc = cc = NULL;
    pmp = NULL;

    setParent(parent);
    setGeometry(3*parent->width()/200, (parent->height()-23)/40+23,57*parent->width()/100,57*parent->width()/100);
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);

    wood = std::make_shared<QPixmap>(":/chessboard/src/pic/wood.png");
    *wood = wood->scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    starry = std::make_shared<QPixmap>(":/chessboard/src/pic/starry.png");
    *starry = starry->scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    beach = std::make_shared<QPixmap>(":/chessboard/src/pic/beach.png");
    *beach = beach->scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    line = std::make_shared<QColor>(QColor(0, 0, 0, 255));
    chosen = std::make_shared<QColor>(QColor(255,125,0,255));
    arrivable = std::make_shared<QColor>(QColor(100,255,100,255));

    setAutoFillBackground(true);

    changeBackGround(viewChessBoard::Random);

    chooseStatus = 0;
    cx = cy = -1;
    if(TestViewChessBoard) qDebug("Construct: viewChessBoard. Finish.");
}

viewChessBoard::~viewChessBoard()
{
    if(TestViewChessBoard) qDebug("Destruct: viewChessBoard.");
        delete ui;
    if(TestViewChessBoard) qDebug("Destruct: viewChessBoard. Finish.");
}

void viewChessBoard::changeBackGround(viewChessBoard::backPicture bkp)
{
if(TestViewChessBoard) qDebug("viewChessBoard: changeBackGround.");
    QPalette palette;

    switch (bkp) {
    case Wood:
        palette.setBrush(QPalette::Background,QBrush(*wood));
        bp = Wood;
        break;
    case Starry:
        palette.setBrush(QPalette::Background,QBrush(*starry));
        bp = Starry;
        break;
    case Beach:
        palette.setBrush(QPalette::Background,QBrush(*beach));
        bp = Beach;
        break;
    case Random:
    {
        int stop = 0;
        while(!stop)
        {
            switch(rand()%3){
            case 0:
                palette.setBrush(QPalette::Background,QBrush(*wood));
                if(bp != Wood)
                {
                    bp = Wood;
                    stop = 1;
                }
                break;
            case 1:
                palette.setBrush(QPalette::Background,QBrush(*starry));
                if(bp != Starry)
                {
                    bp = Starry;
                    stop = 1;
                }
                break;
            case 2:
                palette.setBrush(QPalette::Background,QBrush(*beach));
                if(bp != Beach)
                {
                    bp = Beach;
                    stop = 1;
                }
                break;
            }
        }
        break;
    }
    default:
        return;
    }
    setPalette(palette);
if(TestViewChessBoard) qDebug("viewChessBoard: changeBackGround. Finish.");
}

void viewChessBoard::paintEvent(QPaintEvent *pEvent)
{
if(TestViewChessBoard) qDebug("viewChessBoard: paintEvent.");
    QPainter painter(this);
    //draw line
    double k1 = width()/18.0, k2 = height()/18.0;
    painter.setPen(*line);

    for(int i = 0; i < 9; i++){
        painter.drawLine(k1, (1+i*2)*k2, 17 * k1, (1+i*2)*k2);
        painter.drawLine((1+i*2)*k1, k2, (1+i*2)*k1, 17*k2);
    }

    if(cx >= 0 && cy >= 0)
    {
        painter.setPen(*chosen);
        double frame[8][4] = {{-14.0/15.0,-14.0/15.0,-14.0/15.0,-4.0/15.0},{-14.0/15.0,-14.0/15.0,-4.0/15.0,-14.0/15.0},{14.0/15.0,-14.0/15.0,14.0/15.0,-4.0/15.0},{14.0/15.0,-14.0/15.0,4.0/15.0,-14.0/15.0},
                           {-14.0/15.0,14.0/15.0,-14.0/15.0,4.0/15.0},{-14.0/15.0,14.0/15.0,-4.0/15.0,14.0/15.0},{14.0/15.0,14.0/15.0,14.0/15.0,4.0/15.0},{14.0/15.0,14.0/15.0,4.0/15.0,14.0/15.0}};
        for(int i = 0; i < 8; i++)
            painter.drawLine((2+cx*2+frame[i][0])*k1, (2+cy*2+frame[i][1])*k2,
                             (2+cx*2+frame[i][2])*k1, (2+cy*2+frame[i][3])*k2);
    }

    if(pmp == NULL)
    {
        if(TestViewChessBoard) qDebug("viewChessBoard: paintEvent: Error: pmp is NULL. Finish.");
        return;
    }
    if(TestViewChessBoard) qDebug() << pmp->size();
    PossibleMovePosition::iterator iter;
    for(iter = pmp->begin(); iter != pmp->end(); iter++)
    {
        painter.setPen(*arrivable);
        double frame[8][4] = {{-14.0/15.0,-14.0/15.0,-14.0/15.0,-4.0/15.0},{-14.0/15.0,-14.0/15.0,-4.0/15.0,-14.0/15.0},{14.0/15.0,-14.0/15.0,14.0/15.0,-4.0/15.0},{14.0/15.0,-14.0/15.0,4.0/15.0,-14.0/15.0},
            {-14.0/15.0,14.0/15.0,-14.0/15.0,4.0/15.0},{-14.0/15.0,14.0/15.0,-4.0/15.0,14.0/15.0},{14.0/15.0,14.0/15.0,14.0/15.0,4.0/15.0},{14.0/15.0,14.0/15.0,4.0/15.0,14.0/15.0}};
        for(int i = 0; i < 8; i++)
            painter.drawLine((2+ (iter->first) *2+frame[i][0])*k1, (2+ (iter->second) *2+frame[i][1])*k2,
                             (2+ (iter->first) *2+frame[i][2])*k1, (2+ (iter->second) *2+frame[i][3])*k2);
    }
if(TestViewChessBoard) qDebug("viewChessBoard: paintEvent. Finish.");
}

void viewChessBoard::mouseReleaseEvent(QMouseEvent *event)
{
if(TestViewChessBoard) qDebug("viewChessBoard: mouseReleaseEvent.");
    if(Qt::RightButton == event->button()) return;
    int x=event->x(), y=event->y(), i=0, j=0;
    int stop=0;
    
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(dis(x,y,(2+i*2)*width()/18,(2+j*2)*height()/18) <= width()/18) stop = 1;
            if(stop) break;
        }
        if(stop) break;
    }
    if(stop)
    {
        if(chooseStatus == 0)
        {
            if(choose(i,j)) chooseStatus = 1;
        }
        else
        {
            chooseStatus = 0;
            move(i,j);
        }
    }
if(TestViewChessBoard) qDebug("viewChessBoard: mouseReleaseEvent.");
}

int viewChessBoard::choose(int x, int y)
{
if(TestViewChessBoard) qDebug("viewChessBoard: choose.");
    cx = x;
    cy = y;

    //choose command
    std::vector<int> vi(2);
    vi[0] = x;
    vi[1] = y;
    std::shared_ptr<Any> param = std::make_shared<Any>();
    *param = vi;
    cc->param = param;
    vi = any_cast<std::vector<int>>(*param);
    cc->execute();
if(TestViewChessBoard) qDebug("viewChessBoard: choose. Finish.");
    return 1;
}

void viewChessBoard::move(int x, int y)
{
if(TestViewChessBoard) qDebug("viewChessBoard: move.");
    //move command
    std::vector<int> vi(4);
    vi[0] = cx;
    vi[1] = cy;
    vi[2] = x;
    vi[3] = y;
    cx = -1;
    cy = -1;

    std::shared_ptr<Any> param = std::make_shared<Any>();
    *param = vi;
    mc->param = param;
    vi = any_cast<std::vector<int>>(*param);
    mc->execute();
if(TestViewChessBoard) qDebug("viewChessBoard: move. Finish");
}

void viewChessBoard::ConnectMoveCmd(std::shared_ptr<Command> pmc)
{
    mc = pmc;
}

void viewChessBoard::ConnectChooseCmd(std::shared_ptr<Command> pcc)
{
    cc = pcc;
}

void viewChessBoard::ConnectPossibleMove(std::shared_ptr<PossibleMovePosition> ppmp)
{
    pmp = ppmp;
}
