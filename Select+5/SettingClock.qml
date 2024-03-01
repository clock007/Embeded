import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0

Item {
id:settingclock
visible: true
focus: true
width: Screen.width
height:Screen.height
MouseArea{ anchors.fill: parent    }
Rectangle{
    id:rect2
     anchors.fill: parent
     gradient:
     Gradient {
         GradientStop {position: 0.0; color: "black"}
         GradientStop {position: 1; color: "blue"}}

    GridLayout {

       id : grid;
       width: 500
       height: 350
       rowSpacing: 30;
       columnSpacing: 30

        rows    : 3;     columns : 6
        property double colMulti : grid.width / grid.columns
        property double rowMulti : grid.height / grid.rows
        function prefWidth(item){ return colMulti * item.Layout.columnSpan }
        function prefHeight(item){return rowMulti * item.Layout.rowSpan    }

        ComboBox {
            id:hour
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            model: [ "0","1","2","3","4","5","6","7","8","9","10","11","12", "13","14","15","16","17","18","19","20","21","22","23"]  }

        Rectangle {
            color: "transparent"
            id : hourbox
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            Text { id: hourtext;  text:"ساعت"; color: "white"; anchors.fill: parent;  font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter}
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)}

        ComboBox {
            id:minute
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            model: [ "0","1","2","3","4","5","6","7","8","9","10","11","12", "13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36", "37","38","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49", "50","51","52","53","54","55","56","57","58","59"];  }

        Rectangle {
            color: "transparent"
            id : minutebox
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            Text { id: minutetext;  text:"دقیقه"; color: "white"; anchors.fill: parent;  font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter}
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)}
        ComboBox {
            id:secound
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            model: [ "0","1","2","3","4","5","6","7","8","9","10","11","12", "13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36", "37","38","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49", "50","51","52","53","54","55","56","57","58","59"]  }

        Rectangle {
            color: "transparent"
            id : secoundbox
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            Text { id: secoundtext;  text:"ثانیه"; color: "white"; anchors.fill: parent;  font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter}
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)}
        //--------------------------- Row  1 ----------------------------


        ComboBox {
            id:year
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            model: [ "2018","2019","2020","2021","2022","2023","2024","2025","2026","2027" ]  }


        Rectangle {
            color: "transparent"
            id : yearbox
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            Text { id: yeartext;  text:"سال"; color: "white"; anchors.fill: parent;  font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter}
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)}

        ComboBox {
            id:month
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            model: [ "1","2","3","4","5","6","7","8","9","10","11","12" ]  }

        Rectangle {
            color: "transparent"
            id : monthbox
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            Text { id: monthtext;  text:"ماه"; color: "white"; anchors.fill: parent;  font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter}
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)}

        ComboBox {
            id:day
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            model: [ "1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31" ]  }

        Rectangle {
            color: "transparent"
            id : daybox
            Layout.rowSpan : 1;        Layout.columnSpan : 1
            Text { id: daytext;  text:"روز"; color: "white"; anchors.fill: parent;  font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter}
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)}



        //-----------------------------------------------------
        //-----------------------------------------------------

        Button {
            id:exit
            Layout.rowSpan   : 1
            Layout.columnSpan: 3
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)
            text: "خروج"
            onClicked: { settingclock.visible=false; Page2.visible=true  }
        }
        Button {
            id:save
            Layout.rowSpan   : 1
            Layout.columnSpan: 3
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)
            text: "ذخیره"
            onClicked: {  Spi.SetClock(year.currentText,month.currentText,day.currentText,hour.currentText,minute.currentText,secound.currentText); tShamsi.start();  DateConvert.Shamsi();   }
        }

        Timer {
             id:tShamsi
             interval: 3000
             running: false
             repeat: false
             onTriggered:{ DateConvert.Shamsi() }}


  //      Butt {
       //     id:bdatabase
        //    Layout.rowSpan   : 1
        //    Layout.columnSpan: 3

        //    bicon: "qrc:/zSave.png"
          //  btext: "ذخیره"
          //  onBclicked: {       }}


     //  Butt {
     //   id:bformat
      //  Layout.rowSpan   : 1
      //  Layout.columnSpan: 3
      //  bicon: "qrc:/zExit.png"
      //  btext: "خروج"
      //  onBclicked: {
      //  }}



    } //GridLayout

  }  //Rectangle

} //Item
