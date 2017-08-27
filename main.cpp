/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: main.cpp
 * Description: ss-palm2015的入口函数，创建可供QML调用的UIAdapter
 * 对象和MessageReceiveService对象，加载QML的入口文件。进入应用程序
 * 消息循环。
 * Version: 1.0
 ************************************************************/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQuickView>
#include "uiadapter.h"
#include "queryservice.h"
#include "messagereceiveservice.h"
#include "datareceiveservice.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral("qrc:/images/images/ss-palm2015.png")));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("uiAdapter", new UIAdapter());
    engine.rootContext()->setContextProperty("messageReceiveService", new MessageReceiveService());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));




    return app.exec();
}
