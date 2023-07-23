/*
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-07-22 21:50:05
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-07-23 21:26:24
 * @Description: rosnode 命令
 */
#include "rosnode.h"
#include <QDebug>

Rosnode::Rosnode(QObject *parent) : MyCommand(parent)
{
    modeFlag = MODENULL;

    connect(process,&QProcess::readyReadStandardOutput,this,&Rosnode::onReOut);
}

void Rosnode::onReOut()
{
    QString line = process->readAll();    // 读取命令输出的内容
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

void Rosnode::list()
{
    writeCmd("rosnode list\n");
    modeFlag = MODELIST;
    //qDebug()<<"rosnode list";
}

void Rosnode::info(QString node)
{
    writeCmd("rosnode info "+node+"\n");
    modeFlag = MODEINFO;
    //qDebug()<<"rosnode info";
}

void Rosnode::ping(QString node)
{
    writeCmd("rosnode ping -c 5 "+node+"\n");
    modeFlag = MODEPING;
    //qDebug()<<"rosnode ping";
}

void Rosnode::kill(QString node)
{
    writeCmd("rosnode kill "+node+"\n");
    modeFlag = MODEKILL;
    //qDebug()<<"rosnode kill";
}
