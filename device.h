/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: device.h
 * Description: 所有设备的基类，它的每一个派生类代表激光雷达的一个外
 * 设。该类提供toString方法生成命令字符串，以及fromQString方法根据
 * 设备名构造Device类的实例。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include "action.h"

class Device : public QObject
{
    Q_OBJECT
public:
    Device(QObject *parent = 0);                        //构造函数
    ~Device();                                          //析构函数

    void setAction(Action *action);                     //为该Device设置Action
    Action *getAction();                                //获取action成员
    QString toString();                                 //生成命令字符串
    static Device *fromQString(QString deviceName);     //[静态]使用设备名构造Device类型的实例
    QString getDeviceName() const;                      //获取设备名

protected:
    Action *action;                                     //Action类型的对象
    QString deviceName;                                 //设备名
};

#endif // DEVICE_H
