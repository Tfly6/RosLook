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
    QString line = process->readAll();
    if(line.isEmpty())
    {
        qDebug() <<"error: " ;
    }
    QStringList con = line.split("\n",QString::SkipEmptyParts);
//     for (auto &element : con) {
//         qDebug()<< element;
//     }

    if(modeFlag == MODELIST)
    {
        content = con;
        qDebug()<<32;
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
        qDebug()<<44;
        emit readOut(modeFlag,content);

    }
    if(modeFlag == MODEPUB)
    {
        content << con;
        emit readOut(modeFlag,content);
    }
    if(modeFlag == MODEKILLCMD)
    {
        qDebug() << "kill";
        doKill(con);
    }
}

void Rostopic::list()
{
    writeCmd("rostopic list\n");
    modeFlag = MODELIST;
    //myCmd->subMode = MODELIST;
}

void Rostopic::info(QString topic)
{
    writeCmd("rostopic info "+topic+"\n");
    modeFlag = MODEINFO;
    //myCmd->subMode = MODEINFO;
}

void Rostopic::echo(QString topic,QString arg)
{
    writeCmd("rostopic echo "+arg+topic+"\n");
    modeFlag = MODEECHO;
    //echoCmd->subMode = MODEECHO;
    echoFlag = true;
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
   //    qDebug()<<con <<" " <<typeid(con).name();

   // 判断con 是否为数字
    if(con.contains(QRegExp("[+-]?(0|([1-9]\\d*))(\\.\\d+)?")))
    {
       con = "\"'"+con+"'\"";
    }
    qDebug()<<"99";
    writeCmd("rostopic pub "+arg+" "+topic+" "+type+" "+con+"\n");
    modeFlag = MODEPUB;
    //pubCmd->subMode = MODEPUB;
}

void Rostopic::killEcho()
{
    killCmd("rostopic echo");
    modeFlag = MODEKILLCMD;
    echoFlag = false;
}
