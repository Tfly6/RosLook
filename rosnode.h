/*
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-07-22 21:50:06
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-07-23 21:25:12
 * @Description: rosnode 命令
 */
#ifndef ROSNODE_H
#define ROSNODE_H

#include "mycommand.h"
#include <QObject>

class Rosnode : public MyCommand
{
    Q_OBJECT
public:
    explicit Rosnode(QObject *parent = nullptr);

    void list();
    void info(QString node);
    void ping(QString node);
    void kill(QString node);

    int modeFlag;           // 模式
    QStringList content;    // 命令执行输出的内容

private slots:
    void onReOut();

};

#endif // ROSNODE_H
