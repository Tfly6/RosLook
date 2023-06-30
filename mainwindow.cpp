/**
****************************************************************************************
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-06-16 00:18:58
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-06-21 20:35:56
 * @Description: 主窗口
****************************************************************************************
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QMenu>
#include "stdio.h"
#include "signal.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->windowInit();

    closeFlag = true;   // 允许关闭界面
    echoFlag = false;   // echo 命令未开启

    myCmd = new MyCommand(this);
    echoCmd = new MyCommand(this);
    pubCmd = new MyCommand(this);

    autuDialog = new AutoDialog(this);

    myCmd->getRosEnv();

    // 函数指针
    void (MyCommand::*cmd)(int modeFlag,QStringList con) = &MyCommand::readOut;
    void (MyCommand::*cmdErr)(QString err) = &MyCommand::Error;
    void (MyCommand::*echo)(int modeFlag,QStringList con) = &MyCommand::readOut;
    void (MyCommand::*echoErr)(QString err) = &MyCommand::Error;
    void (MyCommand::*pub)(int modeFlag,QStringList con) = &MyCommand::readOut;
    void (MyCommand::*pubErr)(QString err) = &MyCommand::Error;

    connect(myCmd,cmd,this,&MainWindow::onReOut);
    connect(myCmd,cmdErr,this,&MainWindow::onError);
    connect(echoCmd,echo,this,&MainWindow::onReOut);
    connect(echoCmd,echoErr,this,&MainWindow::onError);
    connect(pubCmd,pub,this,&MainWindow::onReOut);
    connect(pubCmd,pubErr,this,&MainWindow::onError);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::windowInit()
{
    this->setWindowIcon(QPixmap(":/res/app.png"));
    this->setWindowTitle("RosLook");

    clearAct = new QAction("清除",this);
    closesAct = new QAction("退出",this);
    //设置打开文件动作的提示信息
    clearAct->setStatusTip("清除 echoCmd 进程");
    closesAct->setStatusTip("退出程序");
    //关联打开文件动作的信号和槽
    connect(clearAct, &QAction::triggered, this, &MainWindow::clearEcho);
    connect(closesAct,&QAction::triggered,this,&MainWindow::closeact);
    QMenu *menu = ui->menubar->addMenu("工具");
    menu->addAction(clearAct);
    menu->addAction(closesAct);

    stabar = new QLabel(this);
    QLabel *permanent=new QLabel(this);
    permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
    permanent->setText("Version: v0.1");
    ui->statusbar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    // 状态栏添加永久信息
    ui->statusbar->addPermanentWidget(permanent);
    stabar->setText("echoCmd:关");
    // 状态栏添加正常信息
    ui->statusbar->addWidget(stabar);
}

void MainWindow::clearEcho()
{
    echoCmd->killEchoCmd();
    closeFlag = true;
    stabar->setText("echoCmd:关");
    ui->statusbar->addWidget(stabar);
    echoFlag = false;
}

void MainWindow::closeact()
{
   this->close();
}

void MainWindow::onError(QString err)
{
    //qDebug()<<err;
    QMessageBox::critical(this,"错误",err.toUtf8());
}

void MainWindow::onReOut(int modeFlag,QStringList con)
{
    // for (auto &element : con) {
    //     qDebug()<< element;
    // }
    
    if(modeFlag == MODELIST)
    {
        ui->list_topic->clear();
        ui->list_topic->addItems(con);
    }
    if(modeFlag == MODEINFO)
    {
        ui->list_info->clear();
        ui->list_info->addItems(con);
    }
    if(modeFlag == MODESUB)
    {
        ui->list_sub->clear();
        ui->list_sub->addItems(con);
    }
    if(modeFlag == MODEPUB)
    {
        ui->list_pub->clear();
        ui->list_pub->addItems(con);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
//    QThread::msleep(50);  // 50ms
    if(closeFlag)
    {
        qDebug("end...");
        event->accept();
    }
    else{
        event->ignore();
        QMessageBox::warning(this,"警告","请先清除 echoCmd");
    }

}

void MainWindow::on_Btn_flushed_clicked()
{
    myCmd->listCmd();
}

void MainWindow::on_list_topic_itemDoubleClicked(QListWidgetItem *item)
{
    target = item->text();
    ui->line_topic->setText(target);
    myCmd->infoCmd(target);
}

void MainWindow::on_Btn_sub_clicked()
{

    if(!target.isEmpty())
    {
        echoFlag = !echoFlag;
        if(echoFlag)
        {
            echoCmd->echoCmd(target);
            stabar->setText("echoCmd:开");
            ui->statusbar->addWidget(stabar);
            closeFlag = false;
        }
        else{
            echoCmd->killEchoCmd();
            stabar->setText("echoCmd:关");
            ui->statusbar->addWidget(stabar);
            closeFlag = true;
        }
    }
    else{
       QMessageBox::warning(this,"警告","请先选择topic");
    }
}

void MainWindow::on_Btn_pub_clicked()
{
    QString topic = autuDialog->topic;
    if(topic.isEmpty())
    {
        topic = target;
    }

    QString type = autuDialog->type;
    QString arg = autuDialog->arg;
    QString con = autuDialog->con;
    pubCmd->pubCmd(topic,type,con,arg);
}

void MainWindow::on_Btn_auto_clicked()
{
    autuDialog->show();
}

