#include "start.h"
#include "ui_start.h"
#include<QPainter>
#include<QDialog>
#include<QObject>
#include<QMessageBox>
#include"mainwindow.h" //游戏窗口
#include <QApplication>
#include"finished_dialog.h"
start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start),a(nullptr)
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
connect(a,&MainWindow::return_start,this,&start::backtostart);
}

void start::on_rule_btn_clicked()
{
    QMessageBox::about(this,"关于","华中科技大学计算机学院软件工程大作业\n\n\n"
                                 "游戏规则注意事项：\n"
                                 "1.用尽量少的时间完成数独游戏,不同等级的提示次数有限；\n"
                                 "2.在您选择使用提示前需要三思，因为提示功能会把数独结果引向一个唯一结果，这可能与您填入的数字相冲突；\n"
                                 "3.在提示功能与您所填数字（即便这个数字符合要求）冲突时，系统会将新提示的数字视为错误；\n"
                                 "4.考虑到以上三点，在游戏过程中就要选择性地使用提示功能，同时认真思考数独的多结果性以追求快速、低错误的游戏目标。");
}


void start::backtostart()
{
    this->show();
    a->close();
    delete a;
}

