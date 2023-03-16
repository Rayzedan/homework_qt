#include "mainwindow.h"
#include <QPushButton>
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

    //Создаём кнопки и добавляем их в виджеты
    m_timeButton = new QPushButton(this);
    m_createButton = new QPushButton(this);
    m_deleteButton = new QPushButton(this);
    m_rgbButton = nullptr;
    m_mainLayout->addWidget(m_timeButton);
    m_horizontalLayout->addWidget(m_createButton);
    m_horizontalLayout->addWidget(m_deleteButton);
    m_mainLayout->addLayout(m_horizontalLayout);

    //Начальная настройка отображения кнопок
    m_timeButton->setText("Время");
    m_createButton->setText("Создать");
    m_deleteButton->setText("Удалить");

    //Подключение сигнал-слотов
    connect(m_createButton, &QPushButton::clicked, this, &MainWindow::createButton);
    connect(m_deleteButton, &QPushButton::clicked, this, &MainWindow::deleteButton);
    connect(m_timeButton, &QPushButton::clicked, this, &MainWindow::printTime);
}

void MainWindow::createButton()
{
    if (m_rgbButton == nullptr) {
        m_rgbButton = new QPushButton(this);
        connect(m_rgbButton, &QPushButton::clicked, this, &MainWindow::changeColor, Qt::UniqueConnection);
        m_mainLayout->addWidget(m_rgbButton);
        changeColor();
    }
}

void MainWindow::deleteButton()
{
    if (m_rgbButton != nullptr) {
        delete m_rgbButton;
        m_rgbButton = nullptr;
    }
}

void MainWindow::printTime()
{
    qDebug() << QDateTime::currentDateTime().toString("dd.MM HH::mm::ss") << '\n';
}

void MainWindow::changeColor()
{
    const QColor newColor{QRandomGenerator::global()->bounded(255),QRandomGenerator::global()->bounded(255),QRandomGenerator::global()->bounded(255)};
    if (newColor.isValid()) {
        const QString background = QString("background-color: %1").arg(newColor.name());
        m_rgbButton->setText(newColor.name());
        m_rgbButton->setStyleSheet(background);
    }
}

MainWindow::~MainWindow()
{

}
