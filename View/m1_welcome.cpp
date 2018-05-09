#include "m1_welcome.h"
#include "ui_m1_welcome.h"

M1_welcome::M1_welcome(QWidget *parent) : QWidget(parent), ui(new Ui::M1_welcome)
{
    ui->setupUi(this);

    setGeometry(0,0,QApplication::desktop()->width()*300/683,QApplication::desktop()->width()*5/32);
    move((QApplication::desktop()->width() - width())/2, (QApplication::desktop()->height() - height())/2);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    back = std::make_shared<QLabel>(this);
    back->setAttribute(Qt::WA_TranslucentBackground, true);
    back->setGeometry(0,0,width(),height());
    QPixmap pm;
    pm.load(":/pic/src/pic/welcome.png");
    pm = pm.scaled(back->width(), back->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    back->setPixmap(pm);

    opacity = 0;

    effect.setOpacity(opacity);
    back->setGraphicsEffect(&effect);
    setGraphicsEffect(&effect);

    connect(&timer,SIGNAL(timeout()),this,SLOT(fade_on_fade_out()));
    timer.start(50);

    show();

    stop = 0;
}

M1_welcome::~M1_welcome()
{
    delete ui;
}

void M1_welcome::fade_on_fade_out()
{
    if(opacity > 1.8)
    {
        timer.stop();
        stop = 1;
    }
    else
    {
        effect.setOpacity(opacity > 1? 1: opacity);
        back->setGraphicsEffect(&effect);
        setGraphicsEffect(&effect);
    }
    opacity += 0.02;
}

bool M1_welcome::Stop()
{
    return stop == 1;
}
