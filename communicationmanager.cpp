#include "communicationmanager.h"

CommunicationManager::CommunicationManager(QObject *parent) : QObject(parent)
{
    remoteMode = false;
}

CommunicationManager::~CommunicationManager()
{

}

//初始化静态变量，否则出错
CommunicationManager *CommunicationManager::manager = NULL;

CommunicationManager *CommunicationManager::getInstance()
{
    if(manager == NULL)
    {
        manager = new CommunicationManager();
    }
    return manager;
}

Communication *CommunicationManager::createCommunication(QString IP)
{
    //从已有列表中查找
    foreach(Communication *communication , remoteMode ? remoteCommunicationList : communicationList)
    {
        if(communication->getLidarIP() == IP)
        {
            return communication;
        }
    }
    //找不到，创建新的Communication实例
    Communication *newInstance = remoteMode ? new Communication(IP, true) : new Communication(IP);
    //将新实例加入列表
    (remoteMode ? remoteCommunicationList : communicationList).append(newInstance);
    return newInstance;
}

Communication *CommunicationManager::getCommunication()
{
    return (remoteMode ? remoteCommunicationList : communicationList).last();
}

void CommunicationManager::enterRemoteMode()
{
    remoteMode = true;
    qDebug() << "进入远程模式" << endl;
}

void CommunicationManager::quitRemoteMode()
{
    remoteMode = false;
}

void CommunicationManager::deleteCommunication()
{
    (remoteMode ? remoteCommunicationList : communicationList).removeLast();
}

