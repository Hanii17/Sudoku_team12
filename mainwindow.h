#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QButtonGroup>
#include "SudoKu.h"
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr,int x=1);
    ~MainWindow();




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



    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup *buttonGroup;
    int num_clicked=0;
    SudoKu *s;
    int gamelevel;

};
#endif // MAINWINDOW_H
