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
public slots:
    void cellChange(QTableWidgetItem * item);
    void cellDoubleClick(QTableWidgetItem * item);
private:
    void fillTable();
private:
    QTableWidget * table_;
    std::unique_ptr<SheetInterface> sheet_;
    QWidget * parent_;
    QString controlValue;
    bool doubleClick = false;
};
