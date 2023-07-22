#include "rosnode.h"
#include <QDebug>

Rosnode::Rosnode(QObject *parent) : MyCommand(parent)
{
    modeFlag = MODENULL;

    connect(process,&QProcess::readyReadStandardOutput,this,&Rosnode::onReOut);
}

void Rosnode::onReOut()
{
    QString line = process->readAll();
    if(line.isEmpty())
    {
        qDebug() <<"error: " ;
    }
    QStringList con = line.split("\n",QString::SkipEmptyParts);

    if(modeFlag == MODELIST)
    {
        content = con;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODEINFO)
    {
        content = con;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODEPING)
    {
        content = con;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODEKILL)
    {
        content = con;
        emit readOut(modeFlag,content);
    }
}

//void Rosnode::onError(QString err)
//{
//    emit Error(err);
//}

void Rosnode::list()
{
    writeCmd("rosnode list\n");
    modeFlag = MODELIST;
    //myCmd->subMode = modeFlag;
}

void Rosnode::info(QString node)
{
    writeCmd("rosnode info "+node+"\n");
    modeFlag = MODEINFO;
    //myCmd->subMode = modeFlag;
}

void Rosnode::ping(QString node)
{
    writeCmd("rosnode ping -c 5 "+node+"\n");
    modeFlag = MODEPING;
    //pingCmd->subMode = modeFlag;
}

void Rosnode::kill(QString node)
{
    writeCmd("rosnode kill "+node+"\n");
    modeFlag = MODEKILL;
    //myCmd->subMode = modeFlag;
}
