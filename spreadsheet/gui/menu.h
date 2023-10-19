#pragma once
#include <QtWidgets>
#include <QObject>

class Menu : public QObject{
    Q_OBJECT
public:
    Menu(QWidget * parent = nullptr);
    ~Menu();
    void run();
    int getWidth();
    int getHeight();
public slots:
    void fileOpen();
    void fileSave();
private:
    void createMenu();
    void createFileMenu();
    void createAboutMenu();
private:
    QMenuBar * menu_;
    QWidget * parent_;
};
