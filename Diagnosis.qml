/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: Diagnosis.qml
 * Description: “故障诊断”界面。
 * Version: 1.0
 ************************************************************/
import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

Rectangle {
    property real dpi: Screen.pixelDensity.toFixed(2);
    property string fontFamilyWeiruanyahei: "微软雅黑";
    property string fontFamilyYouyuan: "幼圆";
    property string lightgreen: "#80c342";

    Rectangle {
        id: rectHeader;
        width: parent.width;
        anchors.top: parent.top;
        anchors.bottom: column.top;
        color: lightgreen;


        Rectangle {
            id: rectLeft;
            anchors.left: parent.left;
            height: parent.height;
            width: 0;
            color: lightgreen;
            Rectangle {
                id: rectLine;
                width: parent.height;
                x: -parent.height / 2 - height / 2;
                y: parent.height / 2 - height / 2;
                height: 10 * dpi;
                gradient: Gradient {
                    GradientStop { position: 0.0; color: lightgreen;}
                    GradientStop { position: 0.5; color: "white";}
                    GradientStop { position: 1.0; color: lightgreen;}
                }
                rotation: 90;
            }
            NumberAnimation {
                id: animationLine;
                target: rectLine;
                property: "x";
                loops: Animation.Infinite;
                from: -parent.height / 2;
                to: rectHeader.width;
                duration: 1000;
            }
        }
        Rectangle {
            id: rectRight;
            anchors.right: parent.right;
            height: parent.height;
            width: 0;
            color: "green";
        }
        Rectangle {
            id: rectStart;
            width: 50 * dpi;
            height: 20 * dpi;
            anchors.right: parent.right;
            anchors.rightMargin: 20 * dpi;
            anchors.verticalCenter: parent.verticalCenter;
            border.color: "white";
            border.width: 1 * dpi;
            color: mouseArea.containsMouse ? "white" : lightgreen;
            radius: 10 * dpi;
            MouseArea {
                id: mouseArea;
                hoverEnabled: true;
                anchors.fill: parent;
                state: "ready";
                states: [
                    State {
                        name: "ready";
                        PropertyChanges {
                            target: txtHeader;
                            text: "开始故障诊断";
                        }
                        StateChangeScript {
                            script: {
                                timer.stop();
                                timer.count = 0;
                                animationLine.stop();
                            }
                        }
                    },
                    State {
                        name: "restart";
                        PropertyChanges {
                            target: txtHeader;
                            text: "重新开始诊断";
                        }
                        StateChangeScript {
                            script: {
                                timer.stop();
                                timer.count = 0;
                                animationLine.stop();
                                animationLeft.stop();
                                animationRight.stop();
                            }
                        }
                    },
                    State {
                        name: "running";
                        PropertyChanges {
                            target: txtHeader;
                            text: "停止故障诊断";
                        }
                        StateChangeScript {
                            script: {
                                reset();
                                timer.start();
                                uiAdapter.askTsk();
                                animationLeft.start();
                                animationRight.start();
                            }
                        }
                    }
                ]

                onClicked: {
                    if(mouseArea.state == "ready")
                    {
                        mouseArea.state = "running";
                    }
                    else if(mouseArea.state == "running")
                    {
                        mouseArea.state = "restart";
                    }
                    else if(mouseArea.state == "restart")
                    {
                        mouseArea.state = "running";
                    }
                }
            }
            NumberAnimation {
                id: animationLeft;
                target: rectLeft;
                property: "width";
                to: parent.width;
                duration: 8000;
                onStarted: {
                    animationLine.start();
                }
            }
            NumberAnimation {
                id: animationRight;
                target: rectRight;
                property: "width";
                from: parent.width;
                to: 0;
                duration: 8000;
            }
            Text {
                id: txtHeader;
                anchors.centerIn: parent;
                text: "开始故障诊断";
                font.family: fontFamilyWeiruanyahei;
            }
        }
    }
    Column {
        id: column;
        anchors.bottom: parent.bottom;
        width: parent.width;
        height: 120 * dpi;
        Rectangle {
            width: parent.width;
            height: 1;
            color: "lightgray";
        }
        Rectangle {
            id:rectTsk;
            width: parent.width;
            height: 14 * dpi;
            Text {
                anchors.centerIn: parent;
                text: "数据采集作业";
                font.family: fontFamilyYouyuan;
            }
        }
        Rectangle {
            width: parent.width;
            height: 1;
            color: "lightgray";
        }
        Rectangle {
            id:rectCmr;
            width: parent.width;
            height: 14 * dpi;
            Text {
                anchors.centerIn: parent;
                text: "外置相机";
                font.family: fontFamilyYouyuan;
            }
        }
        Rectangle {
            width: parent.width;
            height: 1;
            color: "lightgray";
        }
        Rectangle {
            id:rectStg;
            width: parent.width;
            height: 14 * dpi;
            Text {
                anchors.centerIn: parent;
                text: "转台电机";
                font.family: fontFamilyYouyuan;
            }
        }
        Rectangle {
            width: parent.width;
            height: 1;
            color: "lightgray";
        }
        Rectangle {
            id:rectScn;
            width: parent.width;
            height: 14 * dpi;
            Text {
                anchors.centerIn: parent;
                text: "扫描电机";
                font.family: fontFamilyYouyuan;
            }
        }
        Rectangle {
            width: parent.width;
            height: 1;
            color: "lightgray";
        }
        Rectangle {
            id:rectLsr;
            width: parent.width;
            height: 14 * dpi;
            Text {
                anchors.centerIn: parent;
                text: "激光器";
                font.family: fontFamilyYouyuan;
            }
        }
        Rectangle {
            width: parent.width;
            height: 1;
            color: "lightgray";
        }
        Rectangle {
            id:rectUcm;
            width: parent.width;
            height: 14 * dpi;
            Text {
                anchors.centerIn: parent;
                text: "USB相机";
                font.family: fontFamilyYouyuan;
            }
        }
        Rectangle {
            width: parent.width;
            height: 1;
            color: "lightgray";
        }
        Rectangle {
            id:rectPcm;
            width: parent.width;
            height: 14 * dpi;
            Text {
                anchors.centerIn: parent;
                text: "palm相机";
                font.family: fontFamilyYouyuan;
            }
        }
        Rectangle {
            width: parent.width;
            height: 1;
            color: "lightgray";
        }
        Rectangle {
            id:rectPdt;
            width: parent.width;
            height: 14 * dpi;
            Text {
                anchors.centerIn: parent;
                text: "palm数据传输";
                font.family: fontFamilyYouyuan;
            }
        }
    }
    ColorAnimation {
        id: colorToDarkred;
        to: "darkred";
        property: "color";
        duration: 600;
    }
    ColorAnimation {
        id: colorToLightGreen;
        to: lightgreen;
        property: "color";
        duration: 600;
    }
    Timer {
        id: timer;
        property int count: 0;
        interval: 1000;
        repeat: true;
        onTriggered: {
            switch(count)
            {
            case 0:
                if(tskState)
                {
                    colorToLightGreen.target = rectTsk;
                    colorToLightGreen.start();
                }
                else
                {
                    colorToDarkred.target = rectTsk;
                    colorToDarkred.start();
                }
                uiAdapter.askCmr();
                count ++;
                break;
            case 1:
                if(cmrState)
                {
                    colorToLightGreen.target = rectCmr;
                    colorToLightGreen.start();
                }
                else
                {
                    colorToDarkred.target = rectCmr;
                    colorToDarkred.start();
                }
                uiAdapter.askStg();
                count ++;
                break;
            case 2:
                if(stgState)
                {
                    colorToLightGreen.target = rectStg;
                    colorToLightGreen.start();
                }
                else
                {
                    colorToDarkred.target = rectStg;
                    colorToDarkred.start();
                }
                uiAdapter.askScn();
                count ++;
                break;
            case 3:
                if(scnState)
                {
                    colorToLightGreen.target = rectScn;
                    colorToLightGreen.start();
                }
                else
                {
                    colorToDarkred.target = rectScn;
                    colorToDarkred.start();
                }
                uiAdapter.askLsr();
                count ++;
                break;
            case 4:
                if(lsrState)
                {
                    colorToLightGreen.target = rectLsr;
                    colorToLightGreen.start();
                }
                else
                {
                    colorToDarkred.target = rectLsr;
                    colorToDarkred.start();
                }
                uiAdapter.askUcm();
                count ++;
                break;
            case 5:
                if(ucmState)
                {
                    colorToLightGreen.target = rectUcm;
                    colorToLightGreen.start();
                }
                else
                {
                    colorToDarkred.target = rectUcm;
                    colorToDarkred.start();
                }
                uiAdapter.askPcm();
                count ++;
                break;
            case 6:
                if(pcmState)
                {
                    colorToLightGreen.target = rectPcm;
                    colorToLightGreen.start();
                }
                else
                {
                    colorToDarkred.target = rectPcm;
                    colorToDarkred.start();
                }
                uiAdapter.askPdt();
                count ++;
                break;
            case 7:
                if(pdtState)
                {
                    colorToLightGreen.target = rectPdt;
                    colorToLightGreen.start();
                }
                else
                {
                    colorToDarkred.target = rectPdt;
                    colorToDarkred.start();
                }
                count ++;
                mouseArea.state = "ready";
            }
        }
    }

    property bool tskState: false;
    property bool cmrState: false;
    property bool stgState: false;
    property bool scnState: false;
    property bool lsrState: false;
    property bool ucmState: false;
    property bool pcmState: false;
    property bool pdtState: false;

    Connections {
        target: messageReceiveService;

        onTskStateChanged: {
            if(state == "ready" || state == "working")
                tskState = true;
        }
        onCmrStateChanged: {
            if(state == "ready" || state == "working")
                cmrState = true;
        }
        onStgStateChanged: {
            if(state == "ready" || state == "working")
                stgState = true;
        }
        onScnStateChanged: {
            if(state == "ready" || state == "working")
                scnState = true;
        }
        onLsrStateChanged: {
            if(state == "ready" || state == "working")
                lsrState = true;
        }
        onUcmStateChanged: {
            if(state == "ready" || state == "working")
                ucmState = true;
        }
        onPcmStateChanged: {
            if(state == "ready" || state == "working")
                pcmState = true;
        }
        onPdtStateChanged: {
            if(state == "ready" || state == "working")
                pdtState = true;
        }
    }
    function reset()
    {
        tskState = false;
        cmrState = false;
        stgState = false;
        scnState = false;
        lsrState = false;
        ucmState = false;
        pcmState = false;
        pdtState = false;
        rectTsk.color = "white";
        rectCmr.color = "white";
        rectStg.color = "white";
        rectScn.color = "white";
        rectLsr.color = "white";
        rectUcm.color = "white";
        rectPcm.color = "white";
        rectPdt.color = "white";
    }
}
