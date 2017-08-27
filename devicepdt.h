/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicepdt.h
 * Description: PALM数据传输，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICEPDT_H
#define DEVICEPDT_H

#include <QObject>
#include "device.h"

class DevicePDT : public Device
{
public:
    DevicePDT();                                        //构造函数
    ~DevicePDT();                                       //析构函数
};

#endif // DEVICEPDT_H
