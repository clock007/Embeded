import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Item {

visible: true
width: 800
height: 480



Rectangle {
    id:rect2
     anchors.fill: parent
     gradient:
     Gradient {
         GradientStop {position: 0.0; color: "black"}
         GradientStop {position: 1; color: "red"}}


     SpinBox {
         x:300
         y:80
         id:wait
         from: 4
         to: 10
         value: 5
         width: 110
        height: 35
        onValueChanged: {  }
     }
     Text {
        id: name
         x:630;    y:80
         color: "white"
         font.family: "‌B Titr"
         text: qsTr("تاخیر در به روز رسانی")
        // font.bold: true
         font.pixelSize: 18

     }



     SpinBox {
         x:300
         y:130
         id:volume
         from: 0
         to:100
         value: 50
         width: 110
         height: 35
        onValueChanged: {Ver.VolumController(value)}
     }
     Text {
        id: name2
         x:630;    y:105
         color: "white"
         font.family: "‌B Titr"
         text: qsTr("حجم صدا")
        // font.bold: true
         font.pixelSize: 18

     }



     SpinBox {
        x:300
        y:180
       id:sleep
        from: 20
        to:100
       value: 60
         width: 110
         height: 35
        onValueChanged: {Spi.SetPowerSaver(name3.text.toString());}
     }
     Text {
      id: name3
      x:630;    y:185
      color: "white"
      font.family: "‌B Titr"
      text: qsTr("زمان استراحت نمایشگر")
      font.bold: true
     font.pixelSize: 18

    }

     Butt {
     id:exit
     bx:300
     by:300
     btext: " خروج"
     onBclicked: {  settings.visible=false   }}


}}


