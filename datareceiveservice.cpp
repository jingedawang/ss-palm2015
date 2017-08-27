#include "datareceiveservice.h"
#include "communicationmanager.h"
#include "communication.h"
#include <QDir>
#include <QDateTime>

DataReceiveService::DataReceiveService(QObject *parent) : QObject(parent)
{
    dirPath = "E:/LidarFiles/";
    fileHeaderCount = 0;
    slowCount = 0;
    fastCount = 0;

    fileHeader = new QByteArray();
    slowDataBytesList.append(new QByteArray());
    fastDataBytesList.append(new QByteArray());

    QDir dir(dirPath);
    if(!dir.exists())
    {
        dir.mkdir(dirPath);
    }
    QDir::setCurrent(dirPath);

    Communication *communication = CommunicationManager::getInstance()->getCommunication();
    connect(communication, SIGNAL(tcp1DataReceived(QByteArray)), this, SLOT(tcp1DataReceived(QByteArray)));
    connect(communication, SIGNAL(tcp2DataReceived(QByteArray)), this, SLOT(tcp2DataReceived(QByteArray)));
    connect(communication, SIGNAL(tcp3DataReceived(QByteArray)), this, SLOT(tcp3DataReceived(QByteArray)));

    connect(&timer, SIGNAL(timeout()), this, SLOT(writeToFile()));
    connect(this, SIGNAL(slowDataBytesFilled()), this, SLOT(writeSlowData()));
    connect(this, SIGNAL(fastDataBytesFilled()), this, SLOT(writeFastData()));
    timer.start(1000);
}

DataReceiveService::~DataReceiveService()
{

}

void DataReceiveService::tcp1DataReceived(QByteArray bytes)
{
    if(fileHeader->size() + bytes.size() >= fileHeaderSize)
    {
        if(fileHeader->size() >= fileHeaderSize)
        {
            return;
        }
        QByteArray leftBytes = bytes.left(fileHeaderSize - fileHeader->size());
        fileHeader->append(leftBytes);
        emit fileHeaderFilled();
    }
    else
    {
        fileHeader->append(bytes);
    }
}

void DataReceiveService::tcp2DataReceived(QByteArray bytes)
{
    QByteArray *slowBytes = slowDataBytesList.last();
    if(slowBytes->size() + bytes.size() >= slowDataSize)
    {
        QByteArray leftBytes = bytes.left(slowDataSize - slowBytes->size());
        slowBytes->append(leftBytes);
        emit slowDataBytesFilled();
        QByteArray *nextSlowBytes = new QByteArray();
        QByteArray rightBytes = bytes.right(bytes.size() - slowDataSize + slowBytes->size());
        nextSlowBytes->append(rightBytes);
        slowDataBytesList.append(nextSlowBytes);
    }
    else
    {
        slowBytes->append(bytes);
    }
}

void DataReceiveService::tcp3DataReceived(QByteArray bytes)
{
    QByteArray *fastBytes = fastDataBytesList.last();
    if(fastBytes->size() + bytes.size() >= fastDataSize)
    {
        QByteArray leftBytes = bytes.left(fastDataSize - fastBytes->size());
        fastBytes->append(leftBytes);
        emit fastDataBytesFilled();
        QByteArray *nextFastBytes = new QByteArray();
        QByteArray rightBytes = bytes.right(bytes.size() - fastDataSize + fastBytes->size());
        nextFastBytes->append(rightBytes);
        fastDataBytesList.append(nextFastBytes);
    }
    else
    {
        fastBytes->append(bytes);
    }
}

void DataReceiveService::writeToFile()
{
    mutex.lock();
    timer.stop();
    if(fileHeader->size() == fileHeaderSize)
    {
        if(fileList.size() > fileHeaderCount)
        {
            qDebug() << "------------------写文件头-------------------" << endl;
            QFile *file = fileList.at(fileHeaderCount);
            file->open(QIODevice::Append);
            QByteArray bytes = *fileHeader;
            file->seek(0);
            file->write(bytes);
            file->close();
            fileHeaderCount ++;
        }
    }
    timer.start(1000);
    mutex.unlock();
}

void DataReceiveService::writeSlowData()
{
    qDebug() << "------------------写慢数据文件-------------------" << endl;
    mutex.lock();
    if(fileList.size() <= slowCount)
    {
        QFile *file = new QFile(dirPath + "data-" + QDateTime::currentDateTime().toString("yyyyMMdd-HHmmss") + ".imp");
        file->open(QIODevice::Append);
        QByteArray bytes = *slowDataBytesList.first();
        file->seek(fileHeaderSize);
        file->write(bytes);
        file->close();
        fileList.append(file);
        slowCount ++;
        delete slowDataBytesList.first();
        slowDataBytesList.removeFirst();
    }
    else
    {
        QFile *file = fileList.at(slowCount);
        file->open(QIODevice::Append);
        QByteArray bytes = *slowDataBytesList.first();
        file->seek(fileHeaderSize);
        file->write(bytes);
        file->close();
        slowCount ++;
        delete slowDataBytesList.first();
        slowDataBytesList.removeFirst();
    }
    mutex.unlock();
}

void DataReceiveService::writeFastData()
{
    qDebug() << "------------------写快数据文件-------------------" << endl;
    mutex.lock();
    if(fileList.size() <= fastCount)
    {
//        QFile *file = new QFile(dirPath + "data-" + QDateTime::currentDateTime().toString("yyyyMMdd-HHmmss") + ".imp");
        QFile *file = new QFile();
        file->setFileName("data-" + QDateTime::currentDateTime().toString("yyyyMMdd-HHmmss") + ".imp");
        file->open(QIODevice::Append);
        QByteArray bytes = *fastDataBytesList.first();
        file->seek(fileHeaderSize + slowDataSize);
        file->write(bytes);
        file->close();
        fileList.append(file);
        fastCount ++;
        delete fastDataBytesList.first();
        fastDataBytesList.removeFirst();
    }
    else
    {
        QFile *file = fileList.at(fastCount);
        file->open(QIODevice::Append);
        QByteArray bytes = *fastDataBytesList.first();
        file->seek(fileHeaderSize + slowDataSize);
        file->write(bytes);
        file->close();
        fastCount ++;
        delete fastDataBytesList.first();
        fastDataBytesList.removeFirst();
    }
    mutex.unlock();
}

