#pragma once
#include "table.h"
#include "menu.h"
#include <QtWidgets>

class Gui{
public:
    Gui(int &argc, char** argv);
    ~Gui();
    int run();
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
