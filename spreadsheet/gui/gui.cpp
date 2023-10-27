#include "gui.h"
#include "table.h"
#include "menu.h"
#include <QtWidgets>
#include <QDialog>

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

void Gui::fileOpen(){
    QFileDialog* pdlg = new QFileDialog;
    pdlg->setWindowTitle("Открыть файл");
    if (pdlg->exec() == QDialog::Accepted){

    }
    delete pdlg;
}

void Gui::fileSave(){
    QFileDialog* pdlg = new QFileDialog;
    pdlg->setWindowTitle("Сохранить файл как");
    pdlg->setAcceptMode(QFileDialog::AcceptSave);
    if (pdlg->exec() == QDialog::Accepted){

    }
    delete pdlg;
}


void Gui::appQuit(){
    app_->quit();
}

void Gui::menuShow(){
    mn_ = new Menu(parent_, this);
    mn_->run();
}

void Gui::tableShow(){
    tbl_ = new Table(rows_, cols_, parent_);
    tbl_->run();
    int menuHeight = mn_->getHeight();
    tbl_->posResize(parent_->width(), parent_->height() - menuHeight, 0, menuHeight);
}
