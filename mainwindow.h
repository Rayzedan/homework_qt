#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createButton();
    void deleteButton();
    void printTime();
    void changeColor();

private:
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_horizontalLayout;
    QPushButton *m_timeButton;
    QPushButton *m_createButton;
    QPushButton *m_deleteButton;
    QPushButton *m_rgbButton;
};

#endif // MAINWINDOW_H
