﻿#include "mainwindow.h"
#include <QDateTime>
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Создаём компоновщики
    m_mainLayout = new QVBoxLayout();
    m_horizontalLayout = new QHBoxLayout();
    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(m_mainLayout);

    //Создаём кнопки
    m_timeButton = new QPushButton("Время",this);
    m_createButton = new QPushButton("Создать",this);
    m_deleteButton = new QPushButton("Удалить",this);
    m_rgbButton = new QPushButton(this);

    //Добавляем их в layout
    m_mainLayout->addWidget(m_timeButton);
    m_horizontalLayout->addWidget(m_createButton);
    m_horizontalLayout->addWidget(m_deleteButton);
    m_mainLayout->addLayout(m_horizontalLayout);
    m_mainLayout->addWidget(m_rgbButton);

    m_rgbButton->hide();

    //Подключение сигнал-слотов
    connect(m_createButton, &QPushButton::clicked, this, &MainWindow::createButton);
    connect(m_deleteButton, &QPushButton::clicked, this, &MainWindow::deleteButton);
    connect(m_timeButton, &QPushButton::clicked, this, &MainWindow::printTime);
    connect(m_rgbButton, &QPushButton::clicked, this, &MainWindow::changeColor);
}

void MainWindow::createButton()
{
    if (m_rgbButton->isHidden()) {
        changeColor();
        m_rgbButton->show();
    }
}

void MainWindow::deleteButton()
{
    if (!m_rgbButton->isHidden())
        m_rgbButton->hide();
}

void MainWindow::printTime()
{
    qDebug() << QDateTime::currentDateTime().toString("dd.MM HH::mm::ss") << '\n';
}

void MainWindow::changeColor()
{
    const QColor newColor(QRandomGenerator::global()->generate());
    if (newColor.isValid()) {
        const QString background = QString("background-color: %1").arg(newColor.name());
        m_rgbButton->setText(newColor.name());
        m_rgbButton->setStyleSheet(background);
    }
}

MainWindow::~MainWindow()
{

}
