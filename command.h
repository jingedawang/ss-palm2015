/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: command.h
 * Description: Command类的头文件。该类提供构造字符串命令的toString
 * 方法和解析字符串命令为Command对象的fromQString方法。
 * Version: 1.0
 ************************************************************/
#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include "device.h"

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = 0);              //构造函数
    ~Command();                                         //析构函数

    Device *getDevice() const;                          //返回device成员
    void setDevice(Device *value);                      //设置device成员
    QString toString();                                 //使用device成员构造命令字符串
    static Command *fromQString(QString str);           //把str字符串命令解析为Command对象

private:
    Device* device;                                     //Device类型的成员变量
};

#endif // COMMAND_H
