import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
Item {
    id:settings
    visible: true
    focus: true
    width: Screen.width
    height:Screen.height

MouseArea{ anchors.fill: parent    }
    property  int vol: 50

    Rectangle {
        id:rect2
        anchors.fill: parent
        gradient:
            Gradient {
            GradientStop {position: 0.0; color: "black"}
            GradientStop {position: 1; color: "blue"}}
        //-------------------------------------------------------------------------

        //  GridLayout {

        SpinBox {
            id:volume
            from: 0
            to:100
            value:Ver.ERR_SOUND
            width: 120
            height: 60
            x:100; y:100
            onValueChanged: {Ver.VolumController(value)}
        }
        Text {
            id: name2
            color: "white"
            font.family: "‌B Titr"
            text: qsTr("حجم صدا")
            // font.bold: true
            x:300; y:100
            font.pixelSize: 18

        }

        //---------------------------------------------------------------------------------




        SpinBox {
            id: delay
            width: 120
            height: 60
            from:3
            to:20
            x:100; y:200
            value: Ver.ERR_DELAY

        }
        Text {
            id: tdisplay
            color: "white"
            font.family: "‌B Titr"
            text: qsTr("زمان تاخیر ")
            font.bold: true
            x:300; y:200
            font.pixelSize: 18

        }



        SpinBox {
            id: displayoff
            width: 120
            height: 60
            from:30
            to:90
            x:100; y:300
            value:Ver.ERR_DISPOFF
            onValueChanged: {  }
        }
        Text {
            id: tdisplayoff
            color: "white"
            font.family: "‌B Titr"
            text: qsTr("زمان استراحت نمایشگر")
            font.bold: true
            x:300; y:300
            font.pixelSize: 18

        }



    }// GridLayout

    Butt {
        id:exit
        bx:300
        by:320
        bcolorText1: "white";
        bcolorText2: "brown";
        bicon: "qrc:/zSave.png"
        btext: " ذخیره"
        onBclicked: {       Ver.Insert_Into_Setting(volume.value,delay.value,displayoff.value)   }}

    Butt {
        id:save
        bx:600
        by:320
        bcolorText1: "white";
        bcolorText2: "brown";
        bicon: "qrc:/zExit.png"
        btext: " خروج"
        onBclicked: {  settings.visible=false   }}


    //}
}



