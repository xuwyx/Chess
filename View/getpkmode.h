#ifndef GETPKMODE_H
#define GETPKMODE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "sleep.h"

namespace Ui {
class getPKMode;
}

class getPKMode : public QWidget
{
    Q_OBJECT

public:
    getPKMode(QWidget *parent = 0);
    ~getPKMode();
    void getMode(int&,int&);

private slots:
    void first();
    void second();

private:
    Ui::getPKMode *ui;
    int chosen;
//    QComboBox pl1, pl2, pl3, pl4;
//    QLabel play1, play2, play3, play4, player1, player2, player3, player4;
    QPushButton bt1, bt2;
};

#endif // GETPKMODE_H
