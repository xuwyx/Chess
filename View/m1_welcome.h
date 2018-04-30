#ifndef M1_WELCOME_H
#define M1_WELCOME_H

#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <memory>
#include "sleep.h"

namespace Ui {
class M1_welcome;
}

class M1_welcome : public QWidget
{
    Q_OBJECT

public:
    explicit M1_welcome(QWidget *parent = 0);
    ~M1_welcome();
    bool Stop();

private:
    Ui::M1_welcome *ui;
    std::shared_ptr<QLabel> back;
    float opacity;
    QTimer timer;
    QGraphicsOpacityEffect effect;
    int stop;

private slots:
    void fade_on_fade_out();
};

#endif // M1_WELCOME_H
