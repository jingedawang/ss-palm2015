/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: deviceldr.h
 * Description: 设备状态，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICELDR_H
#define DEVICELDR_H

#include <QObject>
#include "device.h"

class DeviceLDR : public Device
{
    Q_OBJECT
public:
    DeviceLDR();                                        //构造函数
    ~DeviceLDR();                                       //构造函数
};

#endif // DEVICELDR_H
