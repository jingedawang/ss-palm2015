/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicetsk.h
 * Description: 数据采集作业，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICETSK_H
#define DEVICETSK_H

#include <QObject>
#include "device.h"

class DeviceTSK : public Device
{
public:
    DeviceTSK();                                        //构造函数
    ~DeviceTSK();                                       //析构函数
};

#endif // DEVICETSK_H
