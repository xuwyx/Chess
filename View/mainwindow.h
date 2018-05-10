#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QMenu>
#include <QPushButton>
#include <memory>
#include <vector>
#include <QDesktopServices>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include "getpkmode.h"
#include "chesspieces.h"
#include "../command.h"
#include "../ChessBoard.h"
#include "../possiblemoveposition.h"

class ViewModel;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void refresh();
    void contextMenuEvent(QContextMenuEvent *e);
    void ConnectStartCmd(std::shared_ptr<Command>);
    void ConnectMoveCmd(std::shared_ptr<Command>);
    void ConnectChooseCmd(std::shared_ptr<Command>);
    void ConnectChessBoard(std::shared_ptr<ChessBoard>);
    void ConnectPossibleMove(std::shared_ptr<PossibleMovePosition>);
    void ConnectGameOver(std::shared_ptr<int>);
    void ConnectTimer(std::shared_ptr<int>);
    void ConnectQuitGame(QApplication *a);

private slots:
    void newGame();
    void quitPro();
    void changeBackGroundWood();
    void changeBackGroundStarry();
    void changeBackGroundBeach();
    void changeBackGroundRandom();
    void pkMode();
    void authorInfo();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<viewChessBoard> vcb;
    std::shared_ptr<ChessPieces> cp;
    std::shared_ptr<Command> sc,mc,cc,oc;
    std::shared_ptr<ChessBoard> cb;
    std::shared_ptr<PossibleMovePosition> pmp;
    std::shared_ptr<int> go;
    std::shared_ptr<int> time;

    QMenu *Game, *Option, *ChangeChessBoard, *Help;
    QAction *New, *Quit, *ChangeChessBoardToWood, *ChangeChessBoardToStarry, *ChangeChessBoardToBeach,
            *ChangeChessBoardToRandom, *PK, *Rule, *Author;
    QLabel *TimeLabel;
    QApplication *QApp;
    int pl, difficulty;
};

#endif // MAINWINDOW_H
