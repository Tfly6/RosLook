/*
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-07-22 22:02:40
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-07-23 21:23:07
 * @Description: 
 */
#include "mycommand.h"
#include <QThread>
#include <QDebug>
#include "signal.h"

QString MyCommand::envPath = "";

MyCommand::MyCommand(QObject *parent) : QObject(parent)
{
    myConfog = new Config(this);
    process = new QProcess(this);

    // 设置执行的程序
    process->setProgram("bash");


    connect(process,&QProcess::started,[=](){
        qDebug() << "start ok!";
    });

//    void (QProcess::*fin)(int exitCode, QProcess::ExitStatus exitStatus) = &QProcess::finished;
//    void (QProcess::*error)(QProcess::ProcessError error) = &QProcess::errorOccurred;
    void (MyCommand::*errorReOut)() = &MyCommand::onError;

    // connect(process,fin,[=](int exitCode, QProcess::ExitStatus exitStatus){
    //     qDebug() << "finished: "<< exitCode <<","<< exitStatus;
    // });
//    connect(process,error,[=](QProcess::ProcessError error){
//        qDebug() << "error: "<< error;
//    });

    connect(process,&QProcess::readyReadStandardError,this,errorReOut);

}

void MyCommand::onError()
{
    QString error = process->readAllStandardError();
    //error.chop(2);
    //qDebug()<<error;
    if(envPath.isEmpty())
    {
        emit Error("环境错误，请检查配置文件");
    }
    else
    {
        emit Error(error);
    }
}

void MyCommand::getRosEnv()
{
    envPath = myConfog->readConfig();
    if(envPath.isEmpty())
    {
        qDebug()<<"env error";
        return;
    }
    envPath = "source "+envPath+" && ";
    //qDebug()<<"env = "<<envPath;
}

void MyCommand::writeCmd(QString cmd)
{
    // 判断程序运行状态
    if(process->state() == QProcess::Running)
    {
        process->close();            // 关闭程序
        QThread::msleep(100);        // 延时
    }
    process->start();                // 开始执行程序
    process->waitForStarted();       // 等待开始
    cmd = envPath+cmd;
    process->write(cmd.toUtf8());    // 执行命令
}

void MyCommand::killCmd(QString cmd)
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }
    process->start();
    process->waitForStarted();
    process->write("ps -ef | grep '"+cmd.toUtf8()+"' | grep -v grep | awk '{print $2}'\n");
}

void MyCommand::doKill(QStringList pidList)
{
    for(auto &pid:pidList)
    {
        //qDebug()<<pid;
        kill(pid.toInt(),SIGINT);    // 杀死进程
    }
    qDebug()<<"kill cmd ok!";
}
