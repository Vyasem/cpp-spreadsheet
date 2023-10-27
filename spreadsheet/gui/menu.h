#pragma once
#include <QtWidgets>
#include <QObject>

class Menu{
public:
    Menu(QWidget * parent = nullptr, QObject * reciver = nullptr);
    ~Menu();
    void run();
    int getWidth();
    int getHeight();
private:
    void createMenu();
    void createFileMenu();
    void createAboutMenu();
private:
    QMenuBar * menu_;
    QWidget * parent_;
    QObject * reciver_;
};
