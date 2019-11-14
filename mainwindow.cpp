#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QObject>
#include<QString>
#include "SudoKu.h"
#include<QDebug>
#include<QMessageBox>
#include"SudoKu.h"
#include"finished_dialog.h"
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

    //初始化错误次数
     this->wrong_times=0;


     s= new SudoKu(gamelevel); //记得释放内存

     //判断提示个数
     this->idea_time=idea_times(gamelevel);



   //设置等级文字
     this->ui->label->setText("等级:"+this->level_info(gamelevel));


     //设置错误次数
     this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));

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
                                       "QPushButton:hover{border-color:rgb(39,216,39); background:transparent;}");

  //提示按钮的样式
    this->ui->idea_btn->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(230,230,230);}"
                                       "QPushButton:hover{border-color:rgb(39,216,39); background:transparent;}");

    //返回按钮样式
    this->ui->pushButton->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(230,230,230);}"
                                       "QPushButton:hover{border-color:rgb(39,216,39); background:transparent;}");

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


    //设置九宫格深浅
   l=this->s->change_color();
for(int p=0;p<36;p++)
{
    this->buttonGroup->button(l[p])->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                        " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);}"
                        "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                        "QPushButton:checked{background-color:rgb(195, 222, 244);}");
}


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

//填入1
void MainWindow::on_d_1_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_1->text());
   if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,1))
       {
       this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
       this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=1;
       for(int j=0;j<36;j++)
       {
           if(this->num_clicked==l[j])
               this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                   " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                   "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                   "QPushButton:checked{background-color:rgb(195, 222, 244);}");

       }
       }
   else
       {
    this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
       this->wrong_times++;
       this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
       for(int j=0;j<36;j++)
       {
           if(this->num_clicked==l[j])
               this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                   " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                   "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                   "QPushButton:checked{background-color:rgb(195, 222, 244);}");

       }
       }

   //判断是否完成
   correct_times=0;
   for(int j=0;j<9;j++){
       for(int k=0;k<9;k++)
       {
           if(this->s->vvnum[j][k]==this->s->result[j][k])
            this->correct_times+=1;

       }}
   if(correct_times==81){

       this->ptimer.stop();


       //创建结算界面提示消息

       dil=new finished_Dialog(nullptr,this->final());
       this->dil->show();
   }


    }
}


//填入2
void MainWindow::on_d_8_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText("2");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,2))
       {
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=2;
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }


    else
        {
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }

    //判断是否完成
    correct_times=0;
    for(int j=0;j<9;j++){
        for(int k=0;k<9;k++)
        {
            if(this->s->vvnum[j][k]==this->s->result[j][k])
             this->correct_times+=1;

        }}
    if(correct_times==81){

        this->ptimer.stop();

        //创建结算界面提示消息
        dil=new finished_Dialog(nullptr,this->final());
        this->dil->show();
    }
    }

}

//填入3
void MainWindow::on_d_7_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText("3");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,3))
        {
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=3;
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }
    else
        {
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }
    //判断是否完成
    correct_times=0;
    for(int j=0;j<9;j++){
        for(int k=0;k<9;k++)
        {
            if(this->s->vvnum[j][k]==this->s->result[j][k])
             this->correct_times+=1;

        }}
    if(correct_times==81){

        this->ptimer.stop();

        //创建结算界面提示消息
        dil=new finished_Dialog(nullptr,this->final());
        this->dil->show();
    }


    }
}


//填入4
void MainWindow::on_d_4_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText("4");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,4))
        {
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=4;
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }
    else
        {
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }

    //判断是否完成
    correct_times=0;
    for(int j=0;j<9;j++){
        for(int k=0;k<9;k++)
        {
            if(this->s->vvnum[j][k]==this->s->result[j][k])
             this->correct_times+=1;
        }}
    if(correct_times==81){

        this->ptimer.stop();


        //创建结算界面提示消息
        dil=new finished_Dialog(nullptr,this->final());
        this->dil->show();
    }
    }
}

//填入5
void MainWindow::on_d_5_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_5->text());
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,5)){
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=5;
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }
    else
        {
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }
    //判断是否完成
    correct_times=0;
    for(int j=0;j<9;j++){
        for(int k=0;k<9;k++)
        {
            if(this->s->vvnum[j][k]==this->s->result[j][k])
             this->correct_times+=1;

        }}
    if(correct_times==81){


        this->ptimer.stop();


        //创建结算界面提示消息
        dil=new finished_Dialog(nullptr,this->final());
        this->dil->show();
    }

    }
}

//填入6
void MainWindow::on_d_3_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText("6");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,6))
        {
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=6;
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }
    else{
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }

    //判断是否完成
    correct_times=0;
    for(int j=0;j<9;j++){
        for(int k=0;k<9;k++)
        {
            if(this->s->vvnum[j][k]==this->s->result[j][k])
             this->correct_times+=1;
        }}
    if(correct_times==81){

        this->ptimer.stop();


        //创建结算界面提示消息
        dil=new finished_Dialog(nullptr,this->final());
        this->dil->show();
    }


    }
}

//填入7
void MainWindow::on_d_6_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText("7");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,7))
        {
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=7;
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }
    else{
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }

    //判断是否完成
    correct_times=0;
    for(int j=0;j<9;j++){
        for(int k=0;k<9;k++)
        {
            if(this->s->vvnum[j][k]==this->s->result[j][k])
             this->correct_times+=1;

        }}
    if(correct_times==81){

        this->ptimer.stop();


        //创建结算界面提示消息
        dil=new finished_Dialog(nullptr,this->final());
        this->dil->show();
    }


    }
}

//填入8
void MainWindow::on_d_2_clicked()
{

    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText("8");
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,8))
        {
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=8;
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }
   else
        {
     this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
        }

    //判断是否完成
    correct_times=0;
    for(int j=0;j<9;j++){
        for(int k=0;k<9;k++)
        {
            if(this->s->vvnum[j][k]==this->s->result[j][k])
             this->correct_times+=1;
        }}
    if(correct_times==81){

        this->ptimer.stop();


        //创建结算界面提示消息
        dil=new finished_Dialog(nullptr,this->final());
        this->dil->show();
    }

    }

}

//填入9
void MainWindow::on_d_9_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
    this->buttonGroup->button(this->num_clicked)->setText(this->ui->d_9->text());
    if (this->s->judge_sudo((this->num_clicked-1)/9,(this->num_clicked-1)%9,9))
    {
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:rgb(39,216,39)");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=9;
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }

    }
    else{
        this->buttonGroup->button(this->num_clicked)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(this->num_clicked==l[j])
                this->buttonGroup->button(this->num_clicked)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }
    }

    //判断是否完成
    correct_times=0;
    for(int j=0;j<9;j++){
        for(int k=0;k<9;k++)
        {
            if(this->s->vvnum[j][k]==this->s->result[j][k])
             this->correct_times+=1;
        }}
    if(correct_times==81){

        this->ptimer.stop();


        //创建结算界面提示消息
        dil=new finished_Dialog(nullptr,this->final());
        this->dil->show();
    }



    }
}




//擦除功能
void MainWindow::on_clear_btn_clicked()
{
    if(this->num_clicked!=0&&this->buttonGroup->button(num_clicked)->isCheckable()){
        this->buttonGroup->button(this->num_clicked)->setText("");
        this->s->vvnum[(this->num_clicked-1)/9][(this->num_clicked-1)%9]=0;
      this->buttonGroup->button(this->num_clicked)->setCheckable(true);
    }
}

//提示功能
void MainWindow::on_idea_btn_clicked()
{
    int a=this->s->idea_sudo();
    if (this->s->judge_sudo((a-1)/9,(a-1)%9,s->vvnum[(a-1)/9][(a-1)%9])){
    this->buttonGroup->button(a)->setText(QString::number(s->vvnum[(a-1)/9][(a-1)%9]));
    buttonGroup->button(a)->setCheckable(false);
    this->buttonGroup->button(a)->setStyleSheet("color:rgb(39,216,39)");
    for(int j=0;j<36;j++)
    {
        if(a==l[j])
            this->buttonGroup->button(a)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:rgb(39,216,39);}"
                                "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                "QPushButton:checked{background-color:rgb(195, 222, 244);}");

    }
    }

    else
    {
        this->buttonGroup->button(a)->setText(QString::number(s->vvnum[(a-1)/9][(a-1)%9]));
        buttonGroup->button(a)->setCheckable(true);
        this->buttonGroup->button(a)->setStyleSheet("color:red");
        this->wrong_times++;
        this->ui->label_2->setText("错误次数："+QString::number(this->wrong_times));//错误次数+1
        for(int j=0;j<36;j++)
        {
            if(a==l[j])
                this->buttonGroup->button(a)->setStyleSheet("QPushButton{border-right:1px outset black;border-left:1px outset black;"
                                    " border-top:1px outset black;border-bottom:1px outset black;background:rgb(187,187,187);color:red;}"
                                    "QPushButton:hover{border-color:blue; background:rgb(195, 222, 244);}"
                                    "QPushButton:checked{background-color:rgb(195, 222, 244);}");

        }

    }

    idea_time--;
    if(idea_time<=0)
        this->ui->idea_btn->setEnabled(false);
}


//发送返回start界面的信号
void MainWindow::on_pushButton_clicked()
{
    emit return_start();
}



// 获取可提示次数
int MainWindow::idea_times(int le)
{
    switch (le) {
    case 1:return 70;
    case 2:return 5;
    case 3:return 7;
    case 4:return 10;
    default:return 5;

    }
}

//获取结算信息
QString MainWindow::final()
{
    return(this->ui->time_label->text()+"\n"+this->ui->label_2->text());
}


//获取等级信息
QString MainWindow::level_info(int level1)
{
    switch (level1) {
    case 1:return "简单";
     case 2:return "中等";
    case 3:return "困难";
     case 4:return "专家";
    default: return "中等";
    }
}
