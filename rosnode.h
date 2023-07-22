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

    int modeFlag;
    QStringList content;

private slots:
    void onReOut();

};

#endif // ROSNODE_H
