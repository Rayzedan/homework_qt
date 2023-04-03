#include "mainwindow.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QPushButton>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Game");

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this, timer](){
        QPushButton* button = new QPushButton("*", this);
        QTimer* buttonTimer = new QTimer(this);
        const int x = QRandomGenerator::global()->bounded(0,width());
        const int y = QRandomGenerator::global()->bounded(0,100);
        const int speed = QRandomGenerator::global()->bounded(1,5);

        button->setFixedSize(25,25);

        connect(button, &QPushButton::clicked, this, [button, buttonTimer]() {
            button->deleteLater();
            buttonTimer->stop();
        });

        connect(buttonTimer, &QTimer::timeout, this, [this, button, speed]() {
            if (button->underMouse())
                button->move(button->x(), button->y() + 2*speed);
            else
                button->move(button->x(), button->y() + speed);

            if (button->y() + 25 >= height()) {
                button->deleteLater();
                setWindowTitle("YOU LOSE!");
                setStyleSheet("background-color: red;");
            }
        });

        button->setGeometry(x, y, button->width(), button->height());
        button->show();

        const int interval = QRandomGenerator::global()->bounded(100,1000);
        timer->start(interval);
        buttonTimer->start(100);
    });
    timer->start(0);
}

MainWindow::~MainWindow()
{

}

