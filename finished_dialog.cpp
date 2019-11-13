#include "finished_dialog.h"
#include "ui_finished_dialog.h"

finished_Dialog::finished_Dialog(QWidget *parent,QString mesg1) :
    QDialog(parent),
    ui(new Ui::finished_Dialog)
{
    ui->setupUi(this);
    this->ui->finish_message->setText("恭喜你完成游戏！\n耗时："+mesg1);
}

finished_Dialog::~finished_Dialog()
{
    delete ui;

}

void finished_Dialog::on_OK_btn_clicked()
{

    this->close();
}
