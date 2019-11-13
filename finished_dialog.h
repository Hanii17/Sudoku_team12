#ifndef FINISHED_DIALOG_H
#define FINISHED_DIALOG_H

#include <QDialog>
#include<QApplication>
#include<QString>
namespace Ui {
class finished_Dialog;
}

class finished_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit finished_Dialog(QWidget *parent = nullptr,QString mesg1="");
    ~finished_Dialog();



private slots:
    void on_OK_btn_clicked();

private:
    Ui::finished_Dialog *ui;
    QString mesg;
};

#endif // FINISHED_DIALOG_H
