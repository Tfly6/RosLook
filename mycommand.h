/*
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-07-22 22:02:43
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-07-23 21:19:06
 * @Description: 
 */
#ifndef MYCOMMAND_H
#define MYCOMMAND_H

#include <QObject>
#include <QProcess>
#include "config.h"


enum Mode{
    MODENULL,
    MODELIST,
    MODEINFO,
    MODEKILLCMD,
    MODEPUB,
    MODEECHO,
    MODEPING,
    MODEKILL,
    //MODEOTHER,
};

class MyCommand : public QObject
{
    Q_OBJECT
public:
    explicit MyCommand(QObject *parent = nullptr);

    QProcess *process;

    void getRosEnv();                    // 读取配置文件
    void killCmd(QString cmd);           // 关闭命令进程
    void doKill(QStringList pidList);    // 执行关闭

    void writeCmd(QString cmd);          // 写入命令


    static QString envPath;              // ros环境路径

signals:
    void Error(QString err);
    void readOut(int modeFlag,QStringList con);

private slots:
    void onError();


private:
    Config *myConfog;                     // 解析配置文件
};

#endif // MYCOMMAND_H
