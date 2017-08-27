/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicepcm.h
 * Description: PALM相机，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICEPCM_H
#define DEVICEPCM_H

#include <QObject>
#include "device.h"

class DevicePCM : public Device
{
public:
    DevicePCM();                                        //构造函数
    ~DevicePCM();                                       //析构函数
};

#endif // DEVICEPCM_H
