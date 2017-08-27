#include "device.h"
#include "deviceenv.h"
#include "deviceldr.h"
#include "devicepcm.h"
#include "devicepdt.h"
#include "devicetsk.h"
#include "devicecmr.h"
#include "devicescn.h"
#include "devicestg.h"
#include "devicelsr.h"
#include "deviceucm.h"

void Device::setAction(Action *action)
{
    this->action = action;
}

Action *Device::getAction()
{
    return this->action;
}


QString Device::getDeviceName() const
{
    return deviceName;
}
Device::Device(QObject *parent) : QObject(parent), deviceName("Device")
{

}

Device::~Device()
{

}

QString Device::toString()
{
    return "<" + deviceName + "_" + action->toString() + ">";
}

Device *Device::fromQString(QString deviceName)
{
    if(deviceName == "ENV")
    {
        return new DeviceENV();
    }
    else if(deviceName == "LDR")
    {
        return new DeviceLDR();
    }
    else if(deviceName == "TSK")
    {
        return new DeviceTSK();
    }
    else if(deviceName == "CMR")
    {
        return new DeviceCMR();
    }
    else if(deviceName == "SCN")
    {
        return new DeviceSCN();
    }
    else if(deviceName == "STG")
    {
        return new DeviceSTG();
    }
    else if(deviceName == "LSR")
    {
        return new DeviceLSR();
    }
    else if(deviceName == "UCM")
    {
        return new DeviceUCM();
    }
    else if(deviceName == "PCM")
    {
        return new DevicePCM();
    }
    else if(deviceName == "PDT")
    {
        return new DevicePDT();
    }
    else
        return new Device();
}
