/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: devicepst.h
 * Description: PALM转台，继承自Device类。只在构造函数中修改
 * 了继承自Device类的deviceName成员。
 * Version: 1.0
 ************************************************************/
#ifndef DEVICEPST_H
#define DEVICEPST_H

#include <QObject>
#include "device.h"

class DevicePST : public Device
{
public:
    DevicePST();                                        //构造函数
    ~DevicePST();                                       //析构函数
};

#endif // DEVICEPST_H
