#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QButtonGroup>
#include "SudoKu.h"
#include <QApplication>
#include<QTime>
#include<QTimer>
#include<QMessageBox>
#include"finished_dialog.h"
#include<QString>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr,int x=1);
    ~MainWindow();
   //获取提示次数
   int idea_times(int le);

   //获取结束信息
   QString final();

   //获取等级信息
   QString level_info(int level1);

    //自定义返回信号
signals:
    void return_start();
private slots:

    void on_d_1_clicked();
    void clicked_81(int btnID);
    void on_d_8_clicked();

    void on_d_7_clicked();

    void on_d_4_clicked();

    void on_d_5_clicked();

    void on_d_3_clicked();

    void on_d_6_clicked();

    void on_d_2_clicked();

    void on_d_9_clicked();


    void on_clear_btn_clicked();

    void on_idea_btn_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup *buttonGroup;
    int num_clicked=0;//被点击按钮的编号
    SudoKu *s;//数独指针
    int gamelevel;//游戏难度
    QTimer ptimer;//计时器
    QTime baseTime;//开始时的时间
   int correct_times;//比较正确的次数
   finished_Dialog *dil;//结束时的消息窗口
   int idea_time;//提示次数
   int wrong_times;//错误次数
  int *l;//指针指向变色九宫格
};
#endif // MAINWINDOW_H
