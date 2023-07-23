/*
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-07-22 21:50:37
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-07-23 21:12:35
 * @Description: 主界面
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QLabel>
#include "autodialog.h"
#include "rostopic.h"
#include "rosnode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void windowInit();        // 界面初始化

    QString topicName;        // 话题名
    QString nodeName;         // 节点名

    QAction *closesAct;       // 菜单里退出界面的功能
    QLabel *stabar;           // 状态栏显示的消息
    bool closeFlag;           // 界面关闭标志


private slots:

    void onTopicReOut(int modeFlag,QStringList con);
    void onNodeReOut(int modeFlag,QStringList con);
    void onError(QString err);

    void closeact();
    void closeEvent(QCloseEvent *event);


    void on_Btn_flushed_1_clicked();

    void on_list_topic_itemDoubleClicked(QListWidgetItem *item);

    void on_Btn_pub_clicked();

    void on_Btn_echo_clicked();

    void on_Btn_auto_clicked();

    void on_Btn_flushed_2_clicked();

    void on_list_node_itemDoubleClicked(QListWidgetItem *item);

    void on_Btn_kill_clicked();

    void on_Btn_ping_clicked();

private:
    Ui::MainWindow *ui;
    
    Rostopic *topicCmd;
    Rostopic *echoCmd;
    Rostopic *pubCmd;

    Rosnode *nodeCmd;
    Rosnode *pingCmd;
    AutoDialog *autuDialog;   // pub 命令自定义界面
};
#endif // MAINWINDOW_H
