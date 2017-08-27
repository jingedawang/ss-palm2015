#include "messagereceiveservice.h"
#include "commandmanager.h"
#include "command.h"
#include "communicationmanager.h"
#include "communication.h"

MessageReceiveService::MessageReceiveService(QObject *parent) : QObject(parent)
{

}

MessageReceiveService::~MessageReceiveService()
{

}

void MessageReceiveService::enable()
{
    Communication *communication = CommunicationManager::getInstance()->getCommunication();
    connect(communication, SIGNAL(dataReceived(QString)), this, SLOT(messageReceived(QString)));
}

void MessageReceiveService::disable()
{
    Communication *communication = CommunicationManager::getInstance()->getCommunication();
    disconnect(communication, SIGNAL(dataReceived(QString)), this, SLOT(messageReceived(QString)));
}

void MessageReceiveService::messageReceived(QString message)
{
    QList<Command *> *list = CommandManager::getInstance()->parseCommand(message);
    for(int i=0; i<list->length(); i++)
    {
        Command *command = list->at(i);
        //环境参数
        if(command->getDevice()->getDeviceName() == "ENV")
        {
            connect(command->getDevice()->getAction(), SIGNAL(gpsTypeChanged(int)), this, SIGNAL(envGpsTypeChanged(int)));
        }
        else if(command->getDevice()->getDeviceName() == "PDT")
        {
            connect(command->getDevice()->getAction(), SIGNAL(gpsTypeChanged(int)), this, SIGNAL(pdtGpsTypeChanged(int)));
        }
        connect(command->getDevice()->getAction(), SIGNAL(gpsxChanged(float)), this, SIGNAL(envGpsxChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(gpsyChanged(float)), this, SIGNAL(envGpsyChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(gpszChanged(float)), this, SIGNAL(envGpszChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(utcChanged(unsigned long)), this, SIGNAL(envUtcChanged(unsigned long)));
        if(command->getDevice()->getDeviceName() == "ENV")
        {
            connect(command->getDevice()->getAction(), SIGNAL(sutcChanged(unsigned long)), this, SIGNAL(envSutcChanged(unsigned long)));
        }
        else if(command->getDevice()->getDeviceName() == "PDT")
        {
            connect(command->getDevice()->getAction(), SIGNAL(sutcChanged(unsigned long)), this, SIGNAL(pdtSutcChanged(unsigned long)));
        }
        connect(command->getDevice()->getAction(), SIGNAL(incxChanged(float)), this, SIGNAL(envIncxChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(incyChanged(float)), this, SIGNAL(envIncyChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(tempAChanged(float)), this, SIGNAL(envTempAChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(tempBChanged(float)), this, SIGNAL(envTempBChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(hemiAChanged(float)), this, SIGNAL(envHemiAChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(hemiBChanged(float)), this, SIGNAL(envHemiBChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(altitudeChanged(short)), this, SIGNAL(envAltitudeChanged(short)));
        connect(command->getDevice()->getAction(), SIGNAL(airspeedChanged(unsigned short)), this, SIGNAL(envAirspeedChanged(unsigned short)));
        //设备状态报告
        connect(command->getDevice()->getAction(), SIGNAL(rangMinChanged(float)), this, SIGNAL(ldrRangMinChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(rangMaxChanged(float)), this, SIGNAL(ldrRangMaxChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(refMinChanged(float)), this, SIGNAL(ldrRefMinChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(refMaxChanged(float)), this, SIGNAL(ldrRefMaxChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(dataSpeedChanged(float)), this, SIGNAL(ldrDataSpeedChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(dataTotalChanged(float)), this, SIGNAL(ldrDataTotalChanged(float)));
        connect(command->getDevice()->getAction(), SIGNAL(impSizeChanged(float)), this, SIGNAL(ldrImpSizeChanged(float)));
        //PALM相机反馈
        connect(command->getDevice()->getAction(), SIGNAL(f1Changed(unsigned int)), this, SIGNAL(pcmF1Changed(uint)));
        connect(command->getDevice()->getAction(), SIGNAL(f2Changed(unsigned int)), this, SIGNAL(pcmF2Changed(uint)));
        connect(command->getDevice()->getAction(), SIGNAL(f3Changed(unsigned int)), this, SIGNAL(pcmF3Changed(uint)));
        connect(command->getDevice()->getAction(), SIGNAL(f4Changed(unsigned int)), this, SIGNAL(pcmF4Changed(uint)));
        connect(command->getDevice()->getAction(), SIGNAL(f5Changed(unsigned int)), this, SIGNAL(pcmF5Changed(uint)));
        connect(command->getDevice()->getAction(), SIGNAL(f6Changed(unsigned int)), this, SIGNAL(pcmF6Changed(uint)));
        connect(command->getDevice()->getAction(), SIGNAL(tcChanged(unsigned int)), this, SIGNAL(pcmTcChanged(uint)));
        //PALM数据传输
        connect(command->getDevice()->getAction(), SIGNAL(dmiCountChanged(unsigned long)), this, SIGNAL(pdtDmiCountChanged(ulong)));
        connect(command->getDevice()->getAction(), SIGNAL(sateChanged(unsigned short)), this, SIGNAL(pdtSateChanged(unsigned short)));
        connect(command->getDevice()->getAction(), SIGNAL(ppsChanged(bool)), this, SIGNAL(pdtPpsChanged(bool)));
        connect(command->getDevice()->getAction(), SIGNAL(imuChanged(bool)), this, SIGNAL(pdtImuChanged(bool)));
        connect(command->getDevice()->getAction(), SIGNAL(gpsDataChanged(bool)), this, SIGNAL(pdtGpsDataChanged(bool)));
        //故障状态查询（适用于所有设备）
        if (command->getDevice()->getDeviceName() == "TSK")
        {
            connect(command->getDevice()->getAction(), SIGNAL(stateChanged(QString)), this, SIGNAL(tskStateChanged(QString)));
        }
        else if(command->getDevice()->getDeviceName() == "CMR")
        {
            connect(command->getDevice()->getAction(), SIGNAL(stateChanged(QString)), this, SIGNAL(cmrStateChanged(QString)));
        }
        else if(command->getDevice()->getDeviceName() == "STG")
        {
            connect(command->getDevice()->getAction(), SIGNAL(stateChanged(QString)), this, SIGNAL(stgStateChanged(QString)));
        }
        else if(command->getDevice()->getDeviceName() == "SCN")
        {
            connect(command->getDevice()->getAction(), SIGNAL(stateChanged(QString)), this, SIGNAL(scnStateChanged(QString)));
        }
        else if(command->getDevice()->getDeviceName() == "LSR")
        {
            connect(command->getDevice()->getAction(), SIGNAL(stateChanged(QString)), this, SIGNAL(lsrStateChanged(QString)));
        }
        else if(command->getDevice()->getDeviceName() == "UCM")
        {
            connect(command->getDevice()->getAction(), SIGNAL(stateChanged(QString)), this, SIGNAL(ucmStateChanged(QString)));
        }
        else if(command->getDevice()->getDeviceName() == "PCM")
        {
            connect(command->getDevice()->getAction(), SIGNAL(stateChanged(QString)), this, SIGNAL(pcmStateChanged(QString)));
        }
        else if(command->getDevice()->getDeviceName() == "PDT")
        {
            connect(command->getDevice()->getAction(), SIGNAL(stateChanged(QString)), this, SIGNAL(pdtStateChanged(QString)));
        }
        command->getDevice()->getAction()->notify();
    }
}

