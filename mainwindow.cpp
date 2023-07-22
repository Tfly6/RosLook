#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->windowInit();

    autuDialog = new AutoDialog(this);

    closeFlag = true;

    //rostopic = new Rostopic(this);
    //rosnode = new Rosnode(this);

    topicCmd = new Rostopic(this);
    echoCmd = new Rostopic(this);
    pubCmd = new Rostopic(this);

    nodeCmd = new Rosnode(this);
    pingCmd = new Rosnode(this);

    topicCmd->getRosEnv();

    void (Rostopic::*topic)(int modeFlag,QStringList con) = &Rostopic::readOut;
    void (Rostopic::*topicErr)(QString err) = &Rostopic::Error;

    connect(topicCmd,topic,this,&MainWindow::onTopicReOut);
    connect(topicCmd,topicErr,this,&MainWindow::onError);
    connect(echoCmd,topic,this,&MainWindow::onTopicReOut);
    connect(echoCmd,topicErr,this,&MainWindow::onError);
    connect(pubCmd,topic,this,&MainWindow::onTopicReOut);
    connect(pubCmd,topicErr,this,&MainWindow::onError);


    void (Rosnode::*node)(int modeFlag,QStringList con) = &Rosnode::readOut;
    void (Rosnode::*nodeErr)(QString err) = &Rosnode::Error;

    connect(nodeCmd,node,this,&MainWindow::onNodeReOut);
    connect(nodeCmd,nodeErr,this,&MainWindow::onError);
    connect(pingCmd,node,this,&MainWindow::onNodeReOut);
    connect(pingCmd,nodeErr,this,&MainWindow::onError);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::windowInit()
{
    this->setWindowIcon(QPixmap(":/res/app.png"));
    this->setWindowTitle("RosLook");

    closesAct = new QAction("退出",this);
    //设置打开文件动作的提示信息
    closesAct->setStatusTip("退出程序");
    //关联打开文件动作的信号和槽
    connect(closesAct,&QAction::triggered,this,&MainWindow::closeact);
    QMenu *menu = ui->menubar->addMenu("工具");
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

void MainWindow::closeEvent(QCloseEvent *event)
{
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

void MainWindow::closeact()
{
   this->close();
}

void MainWindow::onError(QString err)
{
    //qDebug()<<err;
    QMessageBox::critical(this,"错误",err.toUtf8());
}

void MainWindow::onTopicReOut(int modeFlag,QStringList con)
{
    // for (auto &element : con) {
    //     qDebug()<< element;
    // }
    //qDebug()<<rostopic->modeFlag;
    qDebug()<<modeFlag;
    if(modeFlag == MODELIST)
    {
        ui->list_topic->clear();
        ui->list_topic->addItems(con);
        //qDebug()<<1;
    }
    if(modeFlag == MODEINFO)
    {
        ui->list_info_topic->clear();
        ui->list_info_topic->addItems(con);
    }
    if(modeFlag == MODEECHO)
    {
        ui->list_echo->clear();
        ui->list_echo->addItems(con);
        //qDebug()<<2;
    }
    if(modeFlag == MODEPUB)
    {
        ui->list_pub->clear();
        ui->list_pub->addItems(con);
    }
}

void MainWindow::onNodeReOut(int modeFlag,QStringList con)
{
    if(modeFlag == MODELIST)
    {
        ui->list_node->clear();
        ui->list_node->addItems(con);
        //qDebug()<<45;
    }
    if(modeFlag == MODEINFO)
    {
        ui->list_info_node->clear();
        ui->list_info_node->addItems(con);
    }
    if(modeFlag == MODEPING)
    {
        ui->list_ping->clear();
        ui->list_ping->addItems(con);
        //qDebug()<<2;
    }
    if(modeFlag == MODEKILL)
    {
        ui->list_kill->clear();
        ui->list_kill->addItems(con);
    }
}

// rostopic
void MainWindow::on_Btn_flushed_1_clicked()
{
    topicCmd->list();
}

void MainWindow::on_list_topic_itemDoubleClicked(QListWidgetItem *item)
{
    topicName = item->text();
    ui->line_topic->setText(topicName);
    topicCmd->info(topicName);
}

void MainWindow::on_Btn_echo_clicked()
{
    if(!topicName.isEmpty())
    {
        bool echoFlag = echoCmd->echoFlag;

        echoFlag = !echoFlag;
        if(echoFlag)
        {
            echoCmd->echo(topicName);
            stabar->setText("echoCmd:开");
            ui->statusbar->addWidget(stabar);
            closeFlag = false;
        }
        else{
            echoCmd->killEcho();
            stabar->setText("echoCmd:关");
            ui->statusbar->addWidget(stabar);
            closeFlag = true;
        }
        echoCmd->echoFlag = echoFlag;
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
        topic = topicName;
    }
    //qDebug()<<"33";
    QString type = autuDialog->type;
    QString arg = autuDialog->arg;
    QString con = autuDialog->con;
    pubCmd->pub(topic,type,con,arg);
}

void MainWindow::on_Btn_auto_clicked()
{
    autuDialog->show();
}

// rosnode
void MainWindow::on_Btn_flushed_2_clicked()
{
    nodeCmd->list();
}

void MainWindow::on_list_node_itemDoubleClicked(QListWidgetItem *item)
{
    nodeName = item->text();
    ui->line_node->setText(nodeName);
    nodeCmd->info(nodeName);
}

void MainWindow::on_Btn_kill_clicked()
{
    int button = QMessageBox::question(this,"询问","确定杀掉此节点吗?",QMessageBox::Yes,QMessageBox::No);
    if(QMessageBox::Yes == button)
    {
        nodeCmd->kill(nodeName);//默认情况下接收关闭信号，关闭窗体
    }
}

void MainWindow::on_Btn_ping_clicked()
{
    pingCmd->ping(nodeName);
}

