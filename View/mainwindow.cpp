#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

int plChange(int pl)
{
    if(pl == 2) return -1;
    return pl;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QDesktopWidget* desktop = QApplication::desktop();
    setMinimumSize(500*desktop->width()/683, 25*desktop->height()/32+23);
    ui->setupUi(this);
    hide();

    sc = mc = cc = NULL;
    cb = NULL;
    pmp = NULL;
    pl = 0; difficuly = 0;

    setGeometry(0,0,500*desktop->width()/683, 25*desktop->height()/32+23);
    move((desktop->width() - width())/2, (desktop->height() - height())/2);
    setWindowTitle("Chess");

    vcb = std::make_shared<viewChessBoard>(this);
    cp = std::make_shared<ChessPieces>(vcb.get());

    {Game = new QMenu("游戏", this);
    New = new QAction("新游戏", this);
    New->setShortcut(QKeySequence("Ctrl+N"));
    Quit = new QAction("退出游戏",this);
    Quit->setShortcut(QKeySequence("Ctrl+Q"));
    Game->addAction(New);
    Game->addSeparator();
    Game->addAction(Quit);
    ui->menuBar->addMenu(Game);

    Option = new QMenu("选项",this);
    ChangeChessBoard = new QMenu("棋盘",this);
    ChangeChessBoardToWood = new QAction("木纹棋盘",this);
    ChangeChessBoardToWood->setShortcut(QKeySequence("Ctrl+W"));
    ChangeChessBoardToStarry = new QAction("星空棋盘",this);
    ChangeChessBoardToStarry->setShortcut(QKeySequence("Ctrl+S"));
    ChangeChessBoardToBeach = new QAction("沙滩棋盘",this);
    ChangeChessBoardToBeach->setShortcut(QKeySequence("Ctrl+B"));
    ChangeChessBoardToRandom = new QAction("随机切换",this);
    ChangeChessBoardToRandom->setShortcut(QKeySequence("Ctrl+R"));
    ChangeChessBoard->addAction(ChangeChessBoardToWood);
    ChangeChessBoard->addAction(ChangeChessBoardToStarry);
    ChangeChessBoard->addAction(ChangeChessBoardToBeach);
    ChangeChessBoard->addAction(ChangeChessBoardToRandom);
    PK = new QAction("人机对战",this);
    PK->setShortcut(QKeySequence("Ctrl+P"));
    Option->addMenu(ChangeChessBoard);
    Option->addAction(PK);
    ui->menuBar->addMenu(Option);

    Help = new QMenu("帮助",this);
    Author = new QAction("作者信息",this);
    Author->setShortcut(QKeySequence("Ctrl+A"));
    Help->addAction(Author);
    ui->menuBar->addMenu(Help);}

    connect(New,SIGNAL(triggered()),this,SLOT(newGame()));
    connect(Quit,SIGNAL(triggered()),this,SLOT(quitPro()));
    connect(ChangeChessBoardToWood,SIGNAL(triggered()),this,SLOT(changeBackGroundWood()));
    connect(ChangeChessBoardToStarry,SIGNAL(triggered()),this,SLOT(changeBackGroundStarry()));
    connect(ChangeChessBoardToBeach,SIGNAL(triggered()),this,SLOT(changeBackGroundBeach()));
    connect(ChangeChessBoardToRandom,SIGNAL(triggered()),this,SLOT(changeBackGroundRandom()));
    connect(PK,SIGNAL(triggered()),this,SLOT(pkMode()));
    connect(Author,SIGNAL(triggered()),this,SLOT(authorInfo()));
}

MainWindow::~MainWindow()
{
    delete Game;
    delete Option;
    delete ChangeChessBoard;
    delete Help;
    delete New;
    delete Quit;
    delete ChangeChessBoardToWood;
    delete ChangeChessBoardToStarry;
    delete ChangeChessBoardToBeach,
    delete ChangeChessBoardToRandom;
    delete PK;
    delete Rule;
    delete Author;
    delete ui;
}

void MainWindow::refresh()
{
    if(*go != -1)
    {
        QMessageBox::StandardButton reply;
        if(*go == 0) reply = QMessageBox::information(this, tr("黑棋获胜!"), "黑棋获胜!重新开始？", QMessageBox::Yes | QMessageBox::No);
        else reply = QMessageBox::information(this, tr("白棋获胜!"), "白棋获胜!重新开始？", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            pl = 0;
            newGame();
        }
        else quitPro();
    }
    else
    {
        vcb->repaint();
        cp->repaint();
    }
}

void MainWindow::newGame()
{
    std::vector<int> vi(2);
    vi[0] = pl; vi[1] = difficuly;
    std::shared_ptr<Any> param = std::make_shared<Any>();
    *param = vi;
    sc->param = param;
    sc->execute();
}

void MainWindow::quitPro()
{
    QApp->quit();
}

void MainWindow::changeBackGroundWood()
{
    vcb->changeBackGround(viewChessBoard::Wood);
}

void MainWindow::changeBackGroundStarry()
{
    vcb->changeBackGround(viewChessBoard::Starry);
}

void MainWindow::changeBackGroundBeach()
{
    vcb->changeBackGround(viewChessBoard::Beach);
}

void MainWindow::changeBackGroundRandom()
{
    vcb->changeBackGround(viewChessBoard::Random);
}

void MainWindow::pkMode()
{
    std::shared_ptr<getPKMode> a(new getPKMode(QApplication::desktop()));

    a->getMode(pl,difficuly);
    a->hide();
    //send command
//    newGame();
}

void MainWindow::authorInfo()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Author");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Group Member:<br>"
                   "徐维亚(xuwyx@qq.com)<br>"
                   "姚婧()<br>"
                   "<br>"
                   "Instructor:<br>"
                   "郑能干");
    msgBox.exec();
}

void MainWindow::contextMenuEvent(QContextMenuEvent* e)
{
    QMenu *menu = new QMenu();
    menu->addMenu(Game);
    menu->addMenu(Option);
    menu->addMenu(Help);
    menu->exec(e->globalPos());
    delete menu;
}

void MainWindow::ConnectStartCmd(std::shared_ptr<Command> psc)
{
    sc = psc;
}

void MainWindow::ConnectMoveCmd(std::shared_ptr<Command> pmc)
{
    mc = pmc;
    vcb->ConnectMoveCmd(mc);
}

void MainWindow::ConnectChooseCmd(std::shared_ptr<Command> pcc)
{
    cc = pcc;
    vcb->ConnectChooseCmd(cc);
}

void MainWindow::ConnectChessBoard(std::shared_ptr<ChessBoard> pcb)
{
    cb = pcb;
    cp->ConnectChessBoard(cb);
}

void MainWindow::ConnectPossibleMove(std::shared_ptr<PossibleMovePosition> ppmp)
{
    pmp = ppmp;
    vcb->ConnectPossibleMove(pmp);
}

void MainWindow::ConnectGameOver(std::shared_ptr<int> pgo)
{
    go = pgo;
}

void MainWindow::ConnectQuitGame(QApplication *a)
{
    QApp = a;
}
