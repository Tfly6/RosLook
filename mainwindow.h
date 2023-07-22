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

    void windowInit();

    QString topicName;
    QString nodeName;

    QAction *closesAct;       // 菜单里推出界面的功能
    QLabel *stabar;
    bool closeFlag;


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
    //Rostopic *rostopic;
    //Rosnode *rosnode;

    Rostopic *topicCmd;
    Rostopic *echoCmd;
    Rostopic *pubCmd;

    Rosnode *nodeCmd;
    Rosnode *pingCmd;
    AutoDialog *autuDialog;   // pub 命令自定义界面
};
#endif // MAINWINDOW_H
