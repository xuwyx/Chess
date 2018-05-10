#include "getpkmode.h"
#include "ui_getpkmode.h"

getPKMode::getPKMode(QWidget *parent) : QWidget(parent), ui(new Ui::getPKMode)
{
    ui->setupUi(this);
    hide();
    setParent(parent);
    setWindowFlags(Qt::WindowTitleHint);
    setWindowTitle("对战模式");
    setAutoFillBackground(true);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(windowFlags() &~ Qt::WindowCloseButtonHint);

    bt1.setParent(this);
    bt1.setText("先手");
    bt1.setGeometry(width()/4, height()*9/10, width()/4, height()/10);
    connect(&bt1,SIGNAL(clicked()),this,SLOT(first()));

    bt2.setParent(this);
    bt2.setText("后手");
    bt2.setGeometry(width()*3/4, height()*9/10, width()/4, height()/10);
    connect(&bt2,SIGNAL(clicked()),this,SLOT(second()));
    chosen = 0;
    show();
}

getPKMode::~getPKMode()
{
    delete ui;
}

void getPKMode::getMode(int &a, int &b)
{
    while(!chosen) sleep(200);

    if(chosen == 1)
    {
        a = 0;
        b = 0;
    }
    else {
        a = 1;
        b = 0;
    }

}

void getPKMode::first()
{
    chosen = 1;
    hide();
}

void getPKMode::second()
{
    chosen = 2;
    hide();
}
