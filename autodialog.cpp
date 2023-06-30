/**
****************************************************************************************
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-06-16 00:18:58
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-06-21 21:07:46
 * @Description: pub 命令自定义窗口
****************************************************************************************
*/
#include "autodialog.h"
#include "ui_autodialog.h"
#include <QMessageBox>
#include <QDebug>

AutoDialog::AutoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutoDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("pubCom 自定义");
}

AutoDialog::~AutoDialog()
{
    delete ui;
}

void AutoDialog::closeEvent(QCloseEvent *e)
{
    int button = QMessageBox::question(this,"询问","确定关闭吗?",QMessageBox::Yes,QMessageBox::No);
    if(QMessageBox::Yes == button)
    {
        e->accept();//默认情况下接收关闭信号，关闭窗体
    }
    else
    {
        e->ignore();//忽略关闭信号，阻止窗体关闭
    }
}

void AutoDialog::on_pushButton_clicked()
{
    topic = ui->line_topic->text();
    type = ui->line_type->text();
    arg = ui->line_arg->text();
    con = ui->text_con->toPlainText();
//     qDebug()<<topic;
//     qDebug()<<type;
//     qDebug()<<arg;
//     qDebug()<<con;
}


void AutoDialog::on_pushButton_2_clicked()
{
    this->close();
}

