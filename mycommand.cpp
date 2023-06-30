/**
****************************************************************************************
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-06-16 00:18:58
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-06-21 20:57:12
 * @Description: 使用QProcess自定义命令
****************************************************************************************
*/

#include "mycommand.h"
#include <QThread>
#include <QDebug>
#include "signal.h"

QString MyCommand::envPath = "";

MyCommand::MyCommand(QObject *parent) : QObject(parent)
{
    modeFlag = MODENULL;

    process = new QProcess(this);
    process->setProgram("bash");


    connect(process,&QProcess::started,[=](){
        qDebug() << "start ok!";
    });

    
//    void (QProcess::*fin)(int exitCode, QProcess::ExitStatus exitStatus) = &QProcess::finished;
//    void (QProcess::*error)(QProcess::ProcessError error) = &QProcess::errorOccurred;
    void (MyCommand::*errorReOut)() = &MyCommand::onError;

//    connect(process,fin,[=](int exitCode, QProcess::ExitStatus exitStatus){
//        qDebug() << "finished: "<< exitCode <<","<< exitStatus;
//    });
//    connect(process,error,[=](QProcess::ProcessError error){
//        qDebug() << "error: "<< error;
//    });
    connect(process,&QProcess::readyReadStandardOutput,this,&MyCommand::onReOut);
    connect(process,&QProcess::readyReadStandardError,this,errorReOut);

}

void MyCommand::onError()
{
    QString error = process->readAllStandardError();
    //error.chop(2);
    //qDebug()<<error;
    emit Error(error);
}

void MyCommand::onReOut()
{
    QString line = process->readAll();
    if(line.isEmpty())
    {
        qDebug() <<"error: " ;
    }
    QStringList list = line.split("\n",QString::SkipEmptyParts);
    if(modeFlag == MODEENV)
    {
        envPath = QString("source /opt/ros/%1/setup.bash && ").arg(list[0]);
        //qDebug()<< envPath;
    }
    if(modeFlag == MODELIST)
    {
        //qDebug()<<"MODELIST";
        content = list;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODEINFO)
    {
        //qDebug()<<"MODEINFO";
        content = list;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODESUB)
    {
        //qDebug()<<"MODESUB";
        content << list;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODEPUB)
    {
        //qDebug()<<"MODEPUB";
        content << list;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODEKILLSUB)
    {
        pidList = list;
        for(auto pid:pidList)
        {
            //qDebug()<<pid;
            kill(pid.toInt(),SIGINT);
        }
    }
    if(modeFlag == MODEOTHER)
    {
        //qDebug()<<"MODEOTHER";
        content << list;
        emit readOut(modeFlag,content);
    }
}

void MyCommand::getRosEnv()
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }
    process->start();
    process->waitForStarted();
    process->write("ls /opt/ros\n");

    modeFlag = MODEENV;
}

void MyCommand::listCmd()
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }
    process->start();
    process->waitForStarted();
    QString cmd = envPath+"rostopic list\n";
    process->write(cmd.toUtf8());
    modeFlag = MODELIST;
    // rostopic list
}

void MyCommand::infoCmd(QString topic)
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }
    process->start();
    process->waitForStarted();
    QString cmd = envPath+"rostopic info "+topic+"\n";
    process->write(cmd.toUtf8());
    modeFlag = MODEINFO;
    // rostopic info topic_name
}

void MyCommand::echoCmd(QString topic,QString arg)
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }
    process->start();
    process->waitForStarted();
    QString cmd = envPath+"rostopic echo "+arg+topic+"\n";
    process->write(cmd.toUtf8());
    modeFlag = MODESUB;
    // rostopic echo arg topic_name
}

void MyCommand::pubCmd(QString topic, QString type, QString con, QString arg)
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }

//    if(topic.isEmpty())
//    {
//        topic = "/chatter";
//    }
    if(type.isEmpty())
    {
        type = "std_msgs/String";
    }
    if(con.isEmpty())
    {
        con = "hello";
    }
    if(arg.isEmpty())
    {
        arg = "-1";
    }
    content = QStringList()<<"pub data: "+con;

//    qDebug()<<topic;
//    qDebug()<<type;
//    qDebug()<<arg;
//    qDebug()<<con <<" " <<typeid(con).name();

    // 判断con 是否为数字
    if(con.contains(QRegExp("[+-]?(0|([1-9]\\d*))(\\.\\d+)?")))
    {
        con = "\"'"+con+"'\"";
    }
    process->start();
    process->waitForStarted();

    QString cmd = envPath+"rostopic pub "+arg+" "+topic+" "+type+" "+con+"\n";
    //qDebug()<<cmd;
    //content = QStringList()<<"pub data: "+con;
    process->write(cmd.toUtf8());
    modeFlag = MODEPUB;
    //rostopic pub -1 topic_name topic_type “con”
}

void MyCommand::otherCmd(QString cmd)
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }
    process->start();
    process->waitForStarted();
    process->write(cmd.toUtf8());
    modeFlag = MODEOTHER;
}

void MyCommand::killEchoCmd()
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }
    process->start();
    process->waitForStarted();
    process->write("ps -ef | grep 'rostopic echo' | grep -v grep | awk '{print $2}'\n");
    modeFlag = MODEKILLSUB;
}
