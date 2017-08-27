/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicelsr.h
 * Description: 激光器，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef LSR_H
#define LSR_H

#include <QObject>
#include "device.h"

class DeviceLSR : public Device
{
    Q_OBJECT
public:
    DeviceLSR(QObject* parent = 0);                     //构造函数
    ~DeviceLSR();                                       //析构函数
};

#endif // LSR_H
