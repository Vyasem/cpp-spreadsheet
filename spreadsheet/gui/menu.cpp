#include "menu.h"
#include <fstream>
#include <QtWidgets>

Menu::Menu(QWidget * parent, QObject * reciver): menu_(new QMenuBar(parent)), parent_(parent), reciver_(reciver){}
Menu::~Menu() = default;

void Menu::run(){
    createMenu();
    createAboutMenu();
    menu_->show();
}

int Menu::getWidth(){
    return menu_->width();
}

int Menu::getHeight(){
    return menu_->height();
}

void Menu::createMenu(){
    createFileMenu();
}

void Menu::createFileMenu(){
    QMenu * mn = new QMenu("Файл");
    mn->addAction("Открыть", reciver_, SLOT(fileOpen()));
    mn->addAction("Сохранить", reciver_, SLOT(fileSave()));
    mn->addSeparator();
    mn->addAction("Выйти", reciver_, SLOT(appQuit()));
    menu_->addMenu(mn);
}

void Menu::createAboutMenu(){
    QMenu * mn = new QMenu("Помощь");
    mn->addAction("О компании");
    menu_->addMenu(mn);
    menu_->resize(menu_->width() + mn->width(), menu_->height());
}
