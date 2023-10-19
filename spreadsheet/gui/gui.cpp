#include "gui.h"
#include "table.h"
#include "menu.h"
#include <QtWidgets>

Gui::Gui(int &argc, char** argv):app_(new QApplication(argc, argv)), parent_(new QMainWindow){};

Gui::~Gui(){
    delete tbl_;
    delete parent_;
}

int Gui::run(){
    parent_->resize(width_, height_);
    parent_->show();
    menuShow();
    tableShow();
    return app_->exec();
}

void Gui::menuShow(){
    mn_ = new Menu(parent_);
    mn_->run();
}

void Gui::tableShow(){
    tbl_ = new Table(rows_, cols_, parent_);
    tbl_->run();
}
