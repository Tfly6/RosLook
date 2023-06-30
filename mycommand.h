/**
****************************************************************************************
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-06-16 00:18:58
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-06-21 22:16:47
****************************************************************************************
*/
#ifndef MYCOMMAND_H
#define MYCOMMAND_H

#include <QObject>
#include <QProcess>
#include <QVector>

enum Mode{
    MODENULL,
    MODEENV,
    MODELIST,
    MODEINFO,
    MODEPUB,
    MODESUB,
    MODEKILLSUB,
    MODEOTHER,
};

class MyCommand : public QObject
{
    Q_OBJECT
public:
    explicit MyCommand(QObject *parent = nullptr);

    void getRosEnv();
    void listCmd();
    void infoCmd(QString topic);
    void echoCmd(QString topic ,QString arg = "-c ");
    void pubCmd(QString topic ,QString type ,QString con ,
                QString arg );

    void otherCmd(QString cmd);
    void killEchoCmd();


    static QString envPath;
    
    int modeFlag;
    QStringList content;
    QStringList pidList;

signals:
    void Error(QString err);
    void readOut(int modeFlag,QStringList con);

private slots:
    void onReOut();
    void onError();

private:
    
    QProcess *process;   // 启动bash
    
};

#endif // MYCOMMAND_H
