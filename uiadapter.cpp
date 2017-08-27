#include "uiadapter.h"
#include "command.h"
#include "actionrun.h"
#include "actionbrk.h"
#include "actionstp.h"
#include "actionask.h"
#include "devicecmr.h"
#include "devicelsr.h"
#include "devicescn.h"
#include "devicestg.h"
#include "devicetsk.h"
#include "deviceucm.h"
#include "devicedmi.h"
#include "devicepst.h"
#include "devicepcm.h"
#include "devicepdt.h"
#include "devicecfg.h"
#include "remoteservice.h"
#include <QUdpSocket>


UIAdapter::UIAdapter(QObject *parent) : QObject(parent)
{
//    lidarIP = QString("192.168.0.188");     //实际情况
    lidarIP = QString("127.0.0.1");         //仿真
    communicationManager = CommunicationManager::getInstance();
    commandManager = CommandManager::getInstance();
}
UIAdapter::~UIAdapter()
{

}

void UIAdapter::identify(QString name)
{
    QUdpSocket socket;
    socket.writeDatagram(name.toLocal8Bit(), QHostAddress("127.0.0.1"), 77777);
}
void UIAdapter::connectDevice(bool remoteMode)
{
    if(remoteMode)
    {
        CommunicationManager::getInstance()->enterRemoteMode();
        //此处转发给本程序的另一个线程RemoteService
        CommunicationManager::getInstance()->createCommunication("127.0.0.1");  //此处IP不需改变
        RemoteService *remoteService = RemoteService::getInstance();
        connect(remoteService, SIGNAL(connectToServerFailed()), this, SIGNAL(connectToServerFailed()));
        connect(remoteService, SIGNAL(connectToServerSucceed()), this, SIGNAL(connectToServerSucceed()));
        remoteService->startService();
        queryService = new QueryService();
    }
    else
    {
        CommunicationManager::getInstance()->createCommunication(lidarIP);
        queryService = new QueryService();
        dataReceiveService = new DataReceiveService();
    }
}

void UIAdapter::disconnectDevice(bool remoteMode)
{
    Communication *communication = CommunicationManager::getInstance()->getCommunication();
    delete communication;
    CommunicationManager::getInstance()->deleteCommunication();
    RemoteService *remoteService = RemoteService::getInstance();
    remoteService->stopService();
    queryService->disable();
    queryService->deleteLater();
    queryService = NULL;
    if(remoteMode)
        CommunicationManager::getInstance()->quitRemoteMode();
    else
    {
        dataReceiveService->deleteLater();
        dataReceiveService = NULL;
    }
}

void UIAdapter::setGPSConnected(bool value)
{
    Action *action;
    if(value){
        ActionRUN *run = new ActionRUN();
        run->setStrgps();
        action = run;
    }
    else
    {
        ActionSTP *stp = new ActionSTP();
        stp->setStpgps();
        action = stp;
    }
    DevicePDT *pdt = new DevicePDT();
    pdt->setAction(action);
    Command *command = commandManager->createCommand(pdt);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::setIMUConnected(bool value)
{
    Action *action;
    if(value){
        ActionRUN *run = new ActionRUN();
        run->setStrimu();
        action = run;
    }
    else
    {
        ActionSTP *stp = new ActionSTP();
        stp->setStpimu();
        action = stp;
    }
    DevicePDT *pdt = new DevicePDT();
    pdt->setAction(action);
    Command *command = commandManager->createCommand(pdt);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::setLaser(int frequency, int percent, bool isSimulate)
{
    ActionRUN *run = new ActionRUN();
    run->setFreq(frequency);
    run->setPower(percent);
    if(isSimulate)
    {
        run->setM();
    }
    DeviceLSR *lsr = new DeviceLSR();
    lsr->setAction(run);
    Command *command = commandManager->createCommand(lsr);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::askLsr()
{
    ActionASK *ask = new ActionASK();
    DeviceLSR *lsr = new DeviceLSR();
    lsr->setAction(ask);
    Command *command = commandManager->createCommand(lsr);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::setScanner(float speed)
{
    ActionRUN *run = new ActionRUN();
    run->setFreq(speed);
    DeviceSCN *scanner = new DeviceSCN();
    scanner->setAction(run);
    Command *command = commandManager->createCommand(scanner);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::askScn()
{
    ActionASK *ask = new ActionASK();
    DeviceSCN *scn = new DeviceSCN();
    scn->setAction(ask);
    Command *command = commandManager->createCommand(scn);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::setStage(int speed, int mode, int roitStart, int roitEnd)
{
    ActionRUN *run = new ActionRUN();
    run->setFreq(speed);
    run->setM(mode);
    run->setRoit(roitStart, roitEnd);
    DeviceSTG *stage = new DeviceSTG();
    stage->setAction(run);
    Command *command = commandManager->createCommand(stage);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::askStg()
{
    ActionASK *ask = new ActionASK();
    DeviceSTG *stg = new DeviceSTG();
    stg->setAction(ask);
    Command *command = commandManager->createCommand(stg);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::setTsk(int min, int max, int echoMode, bool mp, bool netflow, int roisStart, int roisEnd, int roitStart, int roitEnd)
{
    ActionRUN *run = new ActionRUN();
    run->setMin(min);
    run->setMax(max);
    run->setEcho(echoMode);
    if(mp)
    {
        run->setM();
    }
    if(netflow)
    {
        run->setNetFlow();
    }
    run->setRois(roisStart, roisEnd);
    run->setRoit(roitStart, roitEnd);
    DeviceTSK *tsk = new DeviceTSK();
    tsk->setAction(run);
    Command *command = commandManager->createCommand(tsk);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::setCmr(int freq, int cmrMode, int roitStart, int roitEnd)
{
    ActionRUN *run = new ActionRUN();
    run->setFreq(freq);
    run->setM(cmrMode);
    run->setRoit(roitStart, roitEnd);
    DeviceCMR *cmr = new DeviceCMR();
    cmr->setAction(run);
    Command *command = commandManager->createCommand(cmr);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::askCmr()
{
    ActionASK *ask = new ActionASK();
    DeviceCMR *cmr = new DeviceCMR();
    cmr->setAction(ask);
    Command *command = commandManager->createCommand(cmr);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::setUcm(bool mode, int roitStart, int roitEnd, bool cmra, bool cmrb, int freq)
{
    ActionRUN *run = new ActionRUN();
    if(mode)
    {
        run->setM();
    }
    run->setRoit(roitStart, roitEnd);
    if(cmra)
    {
        run->setCmra();
    }
    if(cmrb)
    {
        run->setCmrb();
    }
    run->setFreq(freq);
    DeviceUCM *ucm = new DeviceUCM();
    ucm->setAction(run);
    Command *command = commandManager->createCommand(ucm);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::askUcm()
{
    ActionASK *ask = new ActionASK();
    DeviceUCM *ucm = new DeviceUCM();
    ucm->setAction(ask);
    Command *command = commandManager->createCommand(ucm);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::setDmi(unsigned int code, float circ)
{
    ActionRUN *run = new ActionRUN();
    run->setCode(code);
    run->setCirc(circ);
    DeviceDMI *dmi = new DeviceDMI();
    dmi->setAction(run);
    Command *command = commandManager->createCommand(dmi);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::tskBreak()
{
    ActionBRK *brk = new ActionBRK();
    DeviceTSK *tsk = new DeviceTSK();
    tsk->setAction(brk);
    Command *command = commandManager->createCommand(tsk);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::tskContinue()
{
    ActionRUN *run = new ActionRUN();
    DeviceTSK *tsk = new DeviceTSK();
    tsk->setAction(run);
    Command *command = commandManager->createCommand(tsk);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::askTsk()
{
    ActionASK *ask = new ActionASK();
    DeviceTSK *tsk = new DeviceTSK();
    tsk->setAction(ask);
    Command *command = commandManager->createCommand(tsk);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::stop()
{
    ActionSTP *stp = new ActionSTP();
    DeviceLSR *lsr = new DeviceLSR();
    DeviceSCN *scn = new DeviceSCN();
    DeviceSTG *stg = new DeviceSTG();
    DeviceTSK *tsk = new DeviceTSK();
    DeviceCMR *cmr = new DeviceCMR();
//    DeviceUCM *ucm = new DeviceUCM();
    lsr->setAction(stp);
    scn->setAction(stp);
    stg->setAction(stp);
    tsk->setAction(stp);
    cmr->setAction(stp);
//    ucm->setAction(stp);
    Communication *communication = communicationManager->getCommunication();
    communication->sendCommand(commandManager->createCommand(tsk)->toString());
    communication->sendCommand(commandManager->createCommand(lsr)->toString());
    communication->sendCommand(commandManager->createCommand(cmr)->toString());
    communication->sendCommand(commandManager->createCommand(stg)->toString());
    communication->sendCommand(commandManager->createCommand(scn)->toString());
    //    communication->sendCommand(commandManager->createCommand(ucm)->toString());
}

void UIAdapter::stopScn()
{
    ActionSTP *stp = new ActionSTP();
    DeviceSCN *scn = new DeviceSCN();
    scn->setAction(stp);
    communicationManager->getCommunication()->sendCommand(commandManager->createCommand(scn)->toString());
}

void UIAdapter::stopStg()
{
    ActionSTP *stp = new ActionSTP();
    DeviceSTG *stg = new DeviceSTG();
    stg->setAction(stp);
    communicationManager->getCommunication()->sendCommand(commandManager->createCommand(stg)->toString());
}

void UIAdapter::stopUcm()
{
    ActionSTP *stp = new ActionSTP();
    DeviceUCM *ucm = new DeviceUCM();
    ucm->setAction(stp);
    communicationManager->getCommunication()->sendCommand(commandManager->createCommand(ucm)->toString());
}

void UIAdapter::stopCmr()
{
    ActionSTP *stp = new ActionSTP();
    DeviceCMR *cmr = new DeviceCMR();
    cmr->setAction(stp);
    communicationManager->getCommunication()->sendCommand(commandManager->createCommand(cmr)->toString());
}

void UIAdapter::stopPst()
{
    ActionSTP *stp = new ActionSTP();
    DevicePST *pst = new DevicePST();
    pst->setAction(stp);
    Command *command = commandManager->createCommand(pst);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::setPst(float freq, bool m, int res, bool direction)
{
    ActionRUN *run = new ActionRUN();
    run->setFreq(freq);
    if(m)
    {
       run->setM();
    }
    run->setRes(res);
    if(direction)
    {
        run->setAnti();
    }
    DevicePST *pst = new DevicePST();
    pst->setAction(run);
    Command *command = commandManager->createCommand(pst);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::askPst()
{
    ActionASK *ask = new ActionASK();
    DevicePST *pst = new DevicePST();
    pst->setAction(ask);
    Command *command = commandManager->createCommand(pst);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}
void UIAdapter::stopPcm()
{
    ActionSTP *stp = new ActionSTP();
    DevicePCM *pcm = new DevicePCM();
    pcm->setAction(stp);
    Command *command = commandManager->createCommand(pcm);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::askPdt()
{
    ActionASK *ask = new ActionASK();
    DevicePDT *pdt = new DevicePDT();
    pdt->setAction(ask);
    Command *command = commandManager->createCommand(pdt);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::askCfg()
{
    ActionASK *ask = new ActionASK();
    DeviceCFG *cfg = new DeviceCFG();
    cfg->setAction(ask);
    Command *command = commandManager->createCommand(cfg);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::enterRemoteMode()
{

}

void UIAdapter::quitRemoteMode()
{
    CommunicationManager::getInstance()->quitRemoteMode();
    RemoteService *remoteService = RemoteService::getInstance();
    remoteService->stopService();
}
void UIAdapter::setPcm(int freq, int mode)
{
    ActionRUN *run = new ActionRUN();
    run->setFreq(freq);
    run->setM(mode);
    DevicePCM *pcm = new DevicePCM();
    pcm->setAction(run);
    Command *command = commandManager->createCommand(pcm);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

void UIAdapter::askPcm()
{
    ActionASK *ask = new ActionASK();
    DevicePCM *pcm = new DevicePCM();
    pcm->setAction(ask);
    Command *command = commandManager->createCommand(pcm);
    communicationManager->getCommunication()->sendCommand(command->toString());
    qDebug() << command->toString() << endl;
}

