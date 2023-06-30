/**
****************************************************************************************
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-06-16 00:18:58
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-06-21 22:16:36
****************************************************************************************
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QProcess>
#include <QAction>
#include <QLabel>
#include <QVector>

#include "mycommand.h"
#include "autodialog.h"

#define CMD_RESULT_BUF_SIZE 1024

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int getCmd(QByteArray cmd,QString &result);
    void windowInit();


private slots:
    void clearEcho();
    void closeact();

    void onReOut(int modeFlag,QStringList con);
    void onError(QString err);
    void closeEvent(QCloseEvent *event);

    void on_Btn_flushed_clicked();

    void on_list_topic_itemDoubleClicked(QListWidgetItem *item);

    void on_Btn_sub_clicked();

    void on_Btn_pub_clicked();

    void on_Btn_auto_clicked();

private:
    Ui::MainWindow *ui;

    QString target;           // 选中的话题
    bool closeFlag;           // 界面关闭的标志值
    bool echoFlag;            // echo命令关闭的标志值

    QAction *clearAct;        // 菜单里清除echo功能
    QAction *closesAct;       // 菜单里推出界面的功能
    QLabel *stabar;           // 状态显示

    MyCommand *myCmd;         // 一般命令
    MyCommand *echoCmd;       // echo 命令
    MyCommand *pubCmd;        // pub 命令

    AutoDialog *autuDialog;   // pub 命令自定义界面

};
#endif // MAINWINDOW_H
