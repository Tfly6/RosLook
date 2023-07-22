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
