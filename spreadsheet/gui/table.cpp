#include "table.h"
#include <memory>
#include <variant>
#include "../common.h"
#include "../sheet.h"
#include <QtWidgets>
#include <string>

Table::Table(int rows, int cols, QWidget * parent):table_(new QTableWidget(rows, cols, parent)), sheet_(CreateSheet()), parent_(parent){}

Table::~Table(){
    delete table_;
    sheet_.~unique_ptr();
}

void Table::run(){
    fillTable();
    table_->show();   
    QObject::connect(table_, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(cellChange(QTableWidgetItem *)));
    QObject::connect(table_, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(cellDoubleClick(QTableWidgetItem *)));
}

void Table::posResize(int width, int height, int x, int y){
    if(width == 0){
        width = parent_->width();
    }

    if(height == 0){
        height = parent_->height();
    }

    table_->move(x, y);
    table_->resize(width, height);
}

void Table::cellChange(QTableWidgetItem * item){
    if(controlValue != item->text() && !doubleClick){
        std::string cellText = item->text().toStdString();
        sheet_->SetCell({item->row(), item->column()}, cellText);
        CellInterface::Value val = sheet_->GetCell({item->row(), item->column()})->GetValue();
        QString res;
        if(std::holds_alternative<double>(val)){
            res = QString::number(std::get<double>(val));
        }else if(std::holds_alternative<std::string>(val)){
            res = QString::fromStdString(std::get<std::string>(val));
        }else{
            res = "!ERROR";
        }
        controlValue = res;        
        item->setText(res);
    }

    if(doubleClick){
        doubleClick = false;
    }
}

void Table::cellDoubleClick(QTableWidgetItem * item){
    QString cellText = item->text();
    if(cellText.size() > 0){
        doubleClick = true;
        item->setText(QString::fromStdString(sheet_->GetCell({item->row(), item->column()})->GetText()));
    }
}

void Table::fillTable(){
    QStringList lstH;
    QStringList lstV;

    for(char i = 'A'; i <= 'Z'; ++i){
        lstH << QString(i);
    }

    for(unsigned i = 1; i <= 1000; ++i){
        lstV << QString::number(i);
    }


    for(int i = 0; i < table_->rowCount(); ++i){
        for(int j = 0; j < table_->columnCount(); ++j){
            table_->setItem(i, j, new QTableWidgetItem);
        }
    }

    table_->setHorizontalHeaderLabels(lstH);
    table_->setVerticalHeaderLabels(lstV);
}
