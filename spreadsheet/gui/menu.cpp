#include "menu.h"
#include <QtWidgets>


Menu::Menu(QWidget * parent): menu_(new QMenuBar(parent)), parent_(parent){}
Menu::~Menu() = default;

void Menu::run(){
    createMenu();
    createAboutMenu();
    menu_->show();
}

void Menu::fileOpen(){}

void Menu::fileSave(){}


void Menu::createMenu(){
    createFileMenu();
}

void Menu::createFileMenu(){
    QMenu * mn = new QMenu("Файл");
    mn->addAction("Открыть");
    mn->addAction("Сохранить");
    mn->addSeparator();
    mn->addAction("Выйти");
    menu_->addMenu(mn);
}

void Menu::createAboutMenu(){
    QMenu * mn = new QMenu("Помощь");
    mn->addAction("О компании");
    menu_->addMenu(mn);
    menu_->resize(menu_->width() + mn->width(), menu_->height());
}
