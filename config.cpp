#include "config.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QJsonObject> // { }
//#include <QJsonArray> // [ ]
#include <QJsonDocument> // 解析Json
#include <QJsonValue> // int float double bool null { } [ ]
#include <QJsonParseError>

Config::Config(QObject *parent) : QObject(parent)
{
    init();
}

void Config::init()
{
    QFile file("config.json");
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
        return;
    }
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "can't open error!";
        return;
    }
    qDebug()<<"ok";
    QTextStream stream(&file);
    //stream.setCodec("UTF-8");		// 设置读取编码是UTF8
    QString str = stream.readAll();
    con = str;
    file.close();
}

QString Config::readConfig()
{
    QString ret;
    if(con.isEmpty())
    {
        qDebug()<<"文件内容为空";
        return ret;
    }

    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(con.toUtf8(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
        return ret;
    }

    QJsonObject rootObj = doc.object();

    QJsonValue nameValue = rootObj.value("path");
    bool ok = fileExists(nameValue.toString());
    if(!ok)
    {
        qDebug()<<"环境错误";
        return ret;
    }
    ret = nameValue.toString();
    qDebug() << "path = " << ret;
    return ret;
}

bool Config::fileExists(QString fileName)
{
    QFileInfo fi(fileName);
    return fi.isFile();
}
