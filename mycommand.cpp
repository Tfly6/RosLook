#include "mycommand.h"
#include <QThread>
#include <QDebug>
#include "signal.h"

QString MyCommand::envPath = "";

MyCommand::MyCommand(QObject *parent) : QObject(parent)
{
    //modeFlag = MODENULL;

    myConfog = new Config(this);
    process = new QProcess(this);
    process->setProgram("bash");


    connect(process,&QProcess::started,[=](){
        qDebug() << "start ok!";
    });

    void (QProcess::*fin)(int exitCode, QProcess::ExitStatus exitStatus) = &QProcess::finished;
//    void (QProcess::*error)(QProcess::ProcessError error) = &QProcess::errorOccurred;
    void (MyCommand::*errorReOut)() = &MyCommand::onError;

    connect(process,fin,[=](int exitCode, QProcess::ExitStatus exitStatus){
        qDebug() << "finished: "<< exitCode <<","<< exitStatus;
    });
//    connect(process,error,[=](QProcess::ProcessError error){
//        qDebug() << "error: "<< error;
//    });
//    connect(process,&QProcess::readyReadStandardOutput,this,&MyCommand::onReOut);
    connect(process,&QProcess::readyReadStandardError,this,errorReOut);

}

//void MyCommand::onReOut()
//{
//    QString line = process->readAll();
//    if(line.isEmpty())
//    {
//        qDebug() <<"error: " ;
//    }
//    QStringList list = line.split("\n",QString::SkipEmptyParts);
//    if(modeFlag == MODEKILLCMD)
//    {
//        pidList = list;
//        for(auto &pid:pidList)
//        {
//            //qDebug()<<pid;
//            kill(pid.toInt(),SIGINT);
//        }
//        qDebug()<<"kill cmd ok!";
//    }
//    if(modeFlag == MODEOTHER)
//    {
//        //qDebug()<<"MODEOTHER";
//        //content = list;
//        emit readOut(subMode,list);
//    }
//}

void MyCommand::onError()
{
    QString error = process->readAllStandardError();
    //error.chop(2);
    qDebug()<<error;
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
    qDebug()<<"env = "<<envPath;
}

void MyCommand::writeCmd(QString cmd)
{
    if(process->state() == QProcess::Running)
    {
        process->close();
        QThread::msleep(100);
    }
    process->start();
    process->waitForStarted();
    cmd = envPath+cmd;
    process->write(cmd.toUtf8());
    //modeFlag = MODEOTHER;
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
    qDebug()<<"7867";
    //modeFlag = MODEKILLCMD;
}

void MyCommand::doKill(QStringList pidList)
{
    for(auto &pid:pidList)
    {
        //qDebug()<<pid;
        kill(pid.toInt(),SIGINT);
    }
    qDebug()<<"kill cmd ok!";
}
