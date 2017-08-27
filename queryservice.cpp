#include "queryservice.h"
#include "commandmanager.h"
#include "command.h"
#include "communicationmanager.h"
#include "communication.h"
#include "actionask.h"
#include "devicecfg.h"
#include "deviceldr.h"
#include "deviceenv.h"
#include "devicepcm.h"
#include "devicepdt.h"

QueryService::QueryService(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(20000);
}

QueryService::~QueryService()
{

}

void QueryService::disable()
{
    timer->stop();
}

void QueryService::timeout()
{
    query();
}

void QueryService::query()
{
    CommunicationManager *communicationManager = CommunicationManager::getInstance();
    Communication *communication = communicationManager->getCommunication();
    if(communication == NULL)
    {
        return;
    }
    ActionASK *ask = new ActionASK();
    DeviceLDR *ldr = new DeviceLDR();
    DeviceENV *env = new DeviceENV();
    DeviceCFG *cfg = new DeviceCFG();
    DevicePCM *pcm = new DevicePCM();
    DevicePDT *pdt = new DevicePDT();
    ldr->setAction(ask);
    env->setAction(ask);
    cfg->setAction(ask);
    pcm->setAction(ask);
    pdt->setAction(ask);
    CommandManager *commandManager = CommandManager::getInstance();
    Command *commandLdr = commandManager->createCommand(ldr);
    Command *commandEnv = commandManager->createCommand(env);
    Command *commandCfg = commandManager->createCommand(cfg);
    Command *commandPcm = commandManager->createCommand(pcm);
    Command *commandPdt = commandManager->createCommand(pdt);
    communicationManager->getCommunication()->sendCommand(commandLdr->toString());
    communicationManager->getCommunication()->sendCommand(commandEnv->toString());
//    communicationManager->getCommunication()->sendCommand(commandCfg->toString());
    communicationManager->getCommunication()->sendCommand(commandPcm->toString());
    communicationManager->getCommunication()->sendCommand(commandPdt->toString());
}

