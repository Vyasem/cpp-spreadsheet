#pragma once
#include "table.h"
#include "menu.h"
#include <QtWidgets>
#include <QObject>

class Gui : public QObject{
    Q_OBJECT
public:
    Gui(int &argc, char** argv);
    ~Gui();
    int run();
public slots:
    void fileOpen();
    void fileSave();
    void appQuit();
private:
    void menuShow();
    void tableShow();
private:
    QApplication * app_;
    QMainWindow * parent_;
    Table * tbl_ = nullptr;
    Menu * mn_ = nullptr;
    int width_ = 1300;
    int height_ = 760;
    int rows_ = 1000;
    int cols_ = 26;
};
