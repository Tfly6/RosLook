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

//enum SubMode{

//};

class MyCommand : public QObject
{
    Q_OBJECT
public:
    explicit MyCommand(QObject *parent = nullptr);

    QProcess *process;

    void getRosEnv();
    void killCmd(QString cmd);
    void doKill(QStringList pidList);

    void writeCmd(QString cmd);


    static QString envPath;

    //int modeFlag;
    //int subMode;
    //QStringList content;
    //QStringList pidList;

signals:
    void Error(QString err);
    void readOut(int modeFlag,QStringList con);

private slots:
    void onError();


private:
    Config *myConfog;
};

#endif // MYCOMMAND_H
