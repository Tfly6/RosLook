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

    bool echoFlag;
    int modeFlag;
    QStringList content;

private slots:
    void onReOut();

};

#endif // ROSTOPIC_H
