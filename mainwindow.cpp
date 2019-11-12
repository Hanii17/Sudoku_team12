#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QObject>

#include<QString>
#include "SudoKu.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent,int x)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //用QButtonGroup类来管理九宫格的81个按钮属性
    buttonGroup = new QButtonGroup(this);



    baseTime.setHMS(0,0,0,0);



    //计时器信号与槽
    connect(&this->ptimer,&QTimer::timeout,
            [=]()
    {
        this->baseTime=this->baseTime.addSecs(1);
        QString str=this->baseTime.toString("mm:ss");
        this->ui->time_label->setText(str);

    });

    //启动计时器
     ptimer.start(1000);


    //难度等级
    this->gamelevel=x;



     s= new SudoKu(gamelevel); //记得释放内存

    //设置互斥属性
    buttonGroup->setExclusive(true);
    //利用findchild查找81个按钮，然后添加到Group里，与编号对应
    for (int i=1;i<=81;i++) {
        buttonGroup->addButton(findChild<QPushButton*>("btn_"+QString::number(i)),i);
    }


  //设置窗口的按钮基础格式
   this->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                       " border-top:1px outset black;border-bottom:1px outset black;background:rgb(236,236,236);}"
                       "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                       "QPushButton:checked{background-color:rgb(195, 222, 244);}");


    //擦除按钮的样式
    this->ui->clear_btn->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(230,230,230);}"
                                       "QPushButton:hover{border-color:green; background:transparent;}");



   //设置选择按钮的样式
    ui->d_1->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");
    ui->d_2->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");
    ui->d_3->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");
    ui->d_4->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");
    ui->d_5->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");
    ui->d_6->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");
    ui->d_7->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");
    ui->d_8->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");
    ui->d_9->setStyleSheet("QPushButton{border:2px outset lightgray; background:rgb(236,236,236);}"
                           "QPushButton:hover{border-color:lightgray; background:transparent;}");



   //设置九宫格样式
    for(int i=1;i<=81;i++)
    {

        if(s->vvnum[(i-1)/9][(i-1)%9]!=0)
        {
        buttonGroup->button(i)->setText(QString::number(s->vvnum[(i-1)/9][(i-1)%9]));
        buttonGroup->button(i)->setCheckable(false);
        }
        else buttonGroup->button(i)->setCheckable(true);

}

    //当九宫格里的按钮被选中时信号的处理
    connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(clicked_81(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->s;
}

//槽函数，用来传递被选中的按钮的numID
void MainWindow:: clicked_81(int btnID)
{
    this->num_clicked =btnID;
}


//填数按钮对应的槽函数
void MainWindow::on_d_1_clicked()
{
    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_1->text());
   if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,1))
       this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");
   else
    this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}
}

void MainWindow::on_d_8_clicked()
{
    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText("2");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,2))

        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");


    else
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}

}

void MainWindow::on_d_7_clicked()
{
    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText("3");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,3))
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");
    else
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}
}

void MainWindow::on_d_4_clicked()
{
    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText("4");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,4))
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");
    else
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}
}

void MainWindow::on_d_5_clicked()
{
    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_5->text());
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,5))
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");
    else
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}
}

void MainWindow::on_d_3_clicked()
{
    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText("6");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,6))
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");
    else
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}
}

void MainWindow::on_d_6_clicked()
{
    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText("7");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,7))
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");
    else
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}
}

void MainWindow::on_d_2_clicked()
{

    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText("8");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,8))
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");
   else
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}

}

void MainWindow::on_d_9_clicked()
{
    if(this->num_clicked!=0){
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_9->text());
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,9))
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:green");
    else
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");}
}





//擦除功能
void MainWindow::on_clear_btn_clicked()
{
    if(this->num_clicked!=0){
        this->buttonGroup->button(this->num_clicked)->setText("");

    }
}

void MainWindow::on_idea_btn_clicked()
{
    int a=this->s->idea_sudo();
    this->buttonGroup->button(a)->setText(QString::number(s->vvnum[(a-1)/9][(a-1)%9]));
    buttonGroup->button(a)->setCheckable(false);
    this->buttonGroup->button(a)->setStyleSheet("color:green");
}
