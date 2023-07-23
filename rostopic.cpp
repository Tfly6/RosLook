/*
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-07-22 21:50:11
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-07-23 21:27:32
 * @Description: rostopic 命令
 */
#include "rostopic.h"
#include <QDebug>

Rostopic::Rostopic(QObject *parent) : MyCommand(parent)
{
    modeFlag = MODENULL;
    echoFlag = false;

    connect(process,&QProcess::readyReadStandardOutput,this,&Rostopic::onReOut);
}

void Rostopic::onReOut()
{
    QString line = process->readAll();     // 读取命令输出的内容
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
    if(modeFlag == MODEECHO)
    {
        content << con;
        emit readOut(modeFlag,content);

    }
    if(modeFlag == MODEPUB)
    {
        content << con;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODEKILLCMD)
    {
        //qDebug() << "kill";
        doKill(con);
    }
}

void Rostopic::list()
{
    writeCmd("rostopic list\n");
    modeFlag = MODELIST;
    //qDebug()<<"rostopic list";
}

void Rostopic::info(QString topic)
{
    writeCmd("rostopic info "+topic+"\n");
    modeFlag = MODEINFO;
    //qDebug()<<"rostopic info";
}

void Rostopic::echo(QString topic,QString arg)
{
    writeCmd("rostopic echo "+arg+topic+"\n");
    modeFlag = MODEECHO;
    echoFlag = true;
    //qDebug()<<"rostopic echo";
}

void Rostopic::pub(QString topic ,QString type ,QString con ,QString arg)
{
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
   //    qDebug()<<con;

   // 判断con 是否为数字
    if(con.contains(QRegExp("[+-]?(0|([1-9]\\d*))(\\.\\d+)?")))
    {
       con = "\"'"+con+"'\"";
    }
    writeCmd("rostopic pub "+arg+" "+topic+" "+type+" "+con+"\n");
    modeFlag = MODEPUB;
    //qDebug()<<"rostopic pub";
}

void Rostopic::killEcho()
{
    killCmd("rostopic echo");
    modeFlag = MODEKILLCMD;
    echoFlag = false;
    //qDebug()<<"kill rostopic echo";
}
