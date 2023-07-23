/*
 * @Author: Tfly6 2085488186@qq.com
 * @Date: 2023-07-22 21:57:16
 * @LastEditors: Tfly6 2085488186@qq.com
 * @LastEditTime: 2023-07-23 21:06:55
 * @Description: 解析配置文件
 */
#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);

    QString readConfig();

signals:

private:
    QString con;
    void init();
    bool fileExists(QString fileName);
};

#endif // CONFIG_H
