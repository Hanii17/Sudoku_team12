#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QObject>
#include<QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //用QButtonGroup类来管理九宫格的81个按钮属性
    buttonGroup = new QButtonGroup;
    //设置互斥属性
    buttonGroup->setExclusive(true);
    //利用findchild查找81个按钮，然后添加到Group里，与编号对应
    for (int i=1;i<=81;i++) {
        buttonGroup->addButton(findChild<QPushButton*>("btn_"+QString::number(i)),i);
    }
   //设置选择按钮的样式
    ui->d_1->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
    ui->d_2->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
    ui->d_3->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
    ui->d_4->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
    ui->d_5->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
    ui->d_6->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
    ui->d_7->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
    ui->d_8->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
    ui->d_9->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:green; background:transparent;}");
   //设置九宫格样式
    for(int i=1;i<=81;i++)
    {
        buttonGroup->button(i)->setCheckable(true);
        //设置右上边框
        if(i==3||i==30||i==57||i==6||i==33||i==60||i==9||i==36||i==63)
        {
            buttonGroup->button(i)->setStyleSheet("QPushButton{border-right:2px outset black;border-left:1px outset lightgray;"
                                                  " border-top:2px outset black;border-bottom:1px outset lightgray;background:rgb(236,236,236);}"
                                                  "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                                  "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");
        }
        //设置左上边框
        else if(i==1||i==28||i==55||i==4||i==31||i==58||i==7||i==34||i==61)
        {
            buttonGroup->button(i)->setStyleSheet("QPushButton{border-left:2px outset black;border-right:1px outset lightgray;"
                                                  " border-top:2px outset black;border-bottom:1px outset lightgray;background:rgb(236,236,236);}"
                                                  "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                                  "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");
        }
        //设置左下边框
        else if(i==19||i==46||i==73||i==22||i==49||i==76||i==25||i==52||i==79)
        {
            buttonGroup->button(i)->setStyleSheet("QPushButton{border-left:2px outset black;border-right:1px outset lightgray;"
                                                  " border-bottom:2px outset black;border-top:1px outset lightgray;background:rgb(236,236,236);}"
                                                  "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                                  "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");
        }
        //设置右下边框
        else if(i==21||i==24||i==27||i==48||i==51||i==54||i==75||i==78||i==81)
        {
            buttonGroup->button(i)->setStyleSheet("QPushButton{border-right:2px outset black;border-left:1px outset lightgray;"
                                                  " border-bottom:2px outset black;border-top:1px outset lightgray;background:rgb(236,236,236);}"
                                                  "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                                  "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");
        }
        //设置上边框
        else if(i==2||i==5||i==8||i==29||i==32||i==35||i==59||i==56||i==62)
        {
            buttonGroup->button(i)->setStyleSheet("QPushButton{border-top:2px outset black;border-left:1px outset lightgray;"
                                                  " border-right:1px outset lightgray;border-bottom:1px outset lightgray;background:rgb(236,236,236);}"
                                                  "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                                  "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");
        }
        //设置左边框
        else if(i==10||i==13||i==16||i==37||i==40||i==43||i==64||i==67||i==70)
        {
            buttonGroup->button(i)->setStyleSheet("QPushButton{border-left:2px outset black;border-right:1px outset lightgray;"
                                                  " border-top:1px outset lightgray;border-bottom:1px outset lightgray;background:rgb(236,236,236);}"
                                                  "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                                  "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");
        }
        //设置下边框
        else if(i==74||i==77||i==80||i==47||i==50||i==53||i==20||i==23||i==26)
        {
            buttonGroup->button(i)->setStyleSheet("QPushButton{border-bottom:2px outset black;border-right:1px outset lightgray;"
                                                  " border-top:1px outset lightgray;border-left:1px outset lightgray;background:rgb(236,236,236);}"
                                                  "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                                  "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");
        }
       //设置右边框
        else if(i==18||i==45||i==72||i==12||i==39||i==66||i==42||i==15||i==69)
        {
            buttonGroup->button(i)->setStyleSheet("QPushButton{border-right:2px outset black;border-bottom:1px outset lightgray;"
                                                  " border-top:1px outset lightgray;border-left:1px outset lightgray;background:rgb(236,236,236);}"
                                                  "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                                  "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");
        }
        else{
        buttonGroup->button(i)->setStyleSheet("QPushButton{border:1px outset lightgray; background:rgb(235,235,235);}"
                                              "QPushButton:hover{border-color:blue; background:rgb(228 , 240 , 250);}"
                                              "QPushButton:checked{background-color:rgb(228 , 240 , 250);}");}
    }


    //当九宫格里的按钮被选中时信号的处理
    connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(clicked_81(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//槽函数，用来传递被选中的按钮的numID
void MainWindow:: clicked_81(int btnID)
{
    this->num_clicked =btnID;
}


//填数按钮对应的槽函数
void MainWindow::on_d_1_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_1->text());
}

void MainWindow::on_d_8_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_8->text());
}

void MainWindow::on_d_7_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_7->text());
}

void MainWindow::on_d_4_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_4->text());
}

void MainWindow::on_d_5_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_5->text());
}

void MainWindow::on_d_3_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_3->text());
}

void MainWindow::on_d_6_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_6->text());
}

void MainWindow::on_d_2_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_2->text());
}

void MainWindow::on_d_9_clicked()
{
    if(this->num_clicked!=0)
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_9->text());
}


