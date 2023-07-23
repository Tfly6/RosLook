/*
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-07-22 21:50:12
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-07-23 21:27:41
 * @Description: rostopic 命令
 */
#ifndef ROSTOPIC_H
#define ROSTOPIC_H

#include "mycommand.h"
#include <QObject>

class Rostopic : public MyCommand
{
    Q_OBJECT
public:
    explicit Rostopic(QObject *parent = nullptr);

    void list();
    void info(QString topic);
    void echo(QString topic,QString arg = "-c ");
    void pub(QString topic ,QString type ,QString con ,
             QString arg);

    void killEcho();

    bool echoFlag;            // echo  命令的标志
    int modeFlag;             // 模式
    QStringList content;      // 命令执行输出的内容

private slots:
    void onReOut();

};

#endif // ROSTOPIC_H
