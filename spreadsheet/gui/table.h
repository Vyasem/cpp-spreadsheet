#pragma once
#include <memory>
#include "../sheet.h"
#include <QObject>
#include <QtWidgets>

class Table : public QObject{
    Q_OBJECT
public:
    Table(int rows, int cols, QWidget * parent = nullptr);
    ~Table();
    void run();
    void posResize(int width = 0, int height = 0, int x = 0, int y = 0);
public slots:
    void cellChange(QTableWidgetItem * item);
    void cellDoubleClick(QTableWidgetItem * item);
private:
    void fillEmptyTable();
private:
    QTableWidget * table_;
    std::unique_ptr<SheetInterface> sheet_;
    QWidget * parent_;
    QString controlValue;
    bool doubleClick = false;
};
