#include "start.h"
#include "ui_start.h"
#include<QPainter>
#include<QDialog>
#include<QObject>
#include<QMessageBox>
#include"mainwindow.h" //游戏窗口
#include <QApplication>
start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
 this->ui->start_btn->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(230,230,230);}"
                                    "QPushButton:hover{border-color:green; background:transparent;}");
 this->ui->rule_btn->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(230,230,230);}"
                                   "QPushButton:hover{border-color:green; background:transparent;}");

}

start::~start()
{
    delete ui;
    delete a;
}



void start::on_start_btn_clicked()
{
    this->hide();
     a=new MainWindow(nullptr,this->ui->level->currentIndex()+1);//在初始化时即设置难度
     a->show();

}
