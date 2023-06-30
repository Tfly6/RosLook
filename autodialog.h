/**
****************************************************************************************
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-06-16 00:18:58
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-06-21 22:16:22
****************************************************************************************
*/

#ifndef AUTODIALOG_H
#define AUTODIALOG_H

#include <QDialog>
#include <QHideEvent>

namespace Ui {
class AutoDialog;
}

class AutoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoDialog(QWidget *parent = nullptr);
    ~AutoDialog();

    QString topic;  // 话题名
    QString type;   // 话题消息的类型
    QString arg;    // 参数
    QString con;    // 要发布的消息


private slots:
    void closeEvent(QCloseEvent *e);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AutoDialog *ui;
};

#endif // AUTODIALOG_H
