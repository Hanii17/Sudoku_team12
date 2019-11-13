#ifndef START_H
#define START_H

#include <QWidget>
#include"mainwindow.h" //游戏窗口
namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();

private slots:
    void on_start_btn_clicked();

    void on_rule_btn_clicked();
   void backtostart();
private:
    Ui::start *ui;
  MainWindow *a;

};

#endif // START_H
