/**
****************************************************************************************
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-06-16 00:18:58
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-06-21 21:04:42
 * @Description: 主程序入口
****************************************************************************************
*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
