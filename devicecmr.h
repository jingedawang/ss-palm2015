/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicecmr.h
 * Description: 外置相机，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICECMR_H
#define DEVICECMR_H

#include <QObject>
#include "device.h"

class DeviceCMR : public Device
{
public:
    DeviceCMR();                                        //构造函数
    ~DeviceCMR();                                       //析构函数
};

#endif // DEVICECMR_H
