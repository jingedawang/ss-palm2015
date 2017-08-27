/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: MyToast.qml
 * Description: 用于实现类似Android中的Toast效果。
 * Version: 1.0
 ************************************************************/
import QtQuick 2.0

Item{
    id: rectFrame
    width: 100
    height:50
    property bool isShow: false //是否是示toast
    property alias text: toast.text//显示的文字
    property int interval: 1000//显示时间，ms
    property int fontSize: 30//文字大小
    signal sigToastDisappear();//该toast消失后触发此消息

    function showToast(text)//显示toast函数
    {
        rectFrame.text = text;
        count = 1;
        rectFrame.isShow = true;
        toastTimer.restart();
    }
    property int count: 1
    Timer
    {
        id:toastTimer
        interval : 1000
        onTriggered:
        {
            switch(count)
            {
            case 1://透明度从0到1时触发，持续时间为1000ms
                toastTimer.interval = rectFrame.interval
                count = count+1;
                toastTimer.restart();
                break;
            case 2://一直显示interval毫秒时触发，即将开始消失
                toastTimer.interval = 1000
                count = count+1;
                rectFrame.isShow = false;
                toastTimer.restart();
                break;
            case 3://透明度从1到0时触发，持续时间为1000ms
                count = 1;
                toastTimer.interval = 1000
                rectFrame.sigToastDisappear();
                break;
            }
        }
    }


    //背景色
    Rectangle
    {
        id:toastbkg
        anchors.centerIn: toast;
        width: toast.width + 10;
        height: toast.height + 10;
        color: "black";
        opacity: rectFrame.isShow ? 1 : 0
        Behavior on opacity {
            NumberAnimation { duration: 1000 }
        }
    }


    //显示文字
    Text
    {
        id:toast
        x:0
        y:0
        color: "white"
        anchors.centerIn: parent;
        text:"sssssss";
        opacity: rectFrame.isShow ? 1 : 0
        Behavior on opacity {
            NumberAnimation { duration: 1000 }
        }
    }
}
