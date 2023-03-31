#include "mainwindow.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPalette color;
    color.setColor(QPalette::Window, Qt::red);
    setCentralWidget(new QWidget(this));

    QTimer *timer = new QTimer(this);

    connect(timer,&QTimer::timeout,[this, timer, color](){
        QPushButton *button = new QPushButton(this);
        QTimer *buttonTimer = new QTimer(this);

        const int x = QRandomGenerator::global()->bounded(0,width());
        const int y = QRandomGenerator::global()->bounded(0,100);
        const int speed = QRandomGenerator::global()->bounded(1,5);

        button->setFixedSize(25,25);

        connect(buttonTimer, &QTimer::timeout, [this, button, speed, color]() {
            if (button->underMouse())
                button->move(button->x(), button->y() + 2*speed);
            else
                button->move(button->x(), button->y() + speed);

            if (button->y() + 25 >= height()) {
                setWindowTitle("YOU LOSE!");
                setPalette(color);
            }
        });

        connect(button, &QPushButton::clicked,[button]{
            button->close();
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

