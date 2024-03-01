import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0

Item {
    width: Screen.width
    height: Screen.height
    id:page1
    SpinBox {
        x:645
        y:10
        id:wait
        from: 2 ;   to: 10
        value: Ver.ERR_DELAY
        width: 150;   height: 35
        onValueChanged: {window.resetTime=value}
    }
    Text {
        id: name
        x:732;    y:17
        color: "black"
        font.family: "‌B Titr"
        text: {qsTr("تاخیر"); }
        // font.bold: true
        font.pixelSize: 12}
    //----------------------------------------------------------------------


    GridLayout {
        x:5;    y:50;
        id : grid;
        width: 140;    height: 120
        rows    : 3;     columns : 3
        property double colMulti : grid.width / grid.columns
        property double rowMulti : grid.height / grid.rows
        function prefWidth(item){ return colMulti * item.Layout.columnSpan }
        function prefHeight(item){return rowMulti * item.Layout.rowSpan    }

        Rectangle {
            gradient:
                Gradient {
                GradientStop {position: 0.0; color: "blue"}
                GradientStop {position: 1; color: "white"}}
            radius: 10
            Layout.rowSpan   : 1;        Layout.columnSpan: 3;
            Text {id: year; text: DateConvert.ERR_YEAR;  anchors.fill: parent;  font.pixelSize: 30; font.bold: true;  color: "black"; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter  }
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)  }
        Rectangle {
            radius: 10
            gradient:
                Gradient {
                GradientStop {position: 0.0; color: "blue"}
                GradientStop {position: 1; color: "white"}}
            Layout.rowSpan   : 1;       Layout.columnSpan: 1
            Text {id: day;   text: DateConvert.ERR_DAY; anchors.fill: parent.Center; font.pixelSize: 27; font.bold: true; color: "black"; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter }
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this) }

        Rectangle {
            radius: 10
            gradient:
                Gradient {
                GradientStop {position: 0.0; color: "blue"}
                GradientStop {position: 1; color: "white"}}
            Layout.rowSpan   : 1;       Layout.columnSpan: 2
            Text { id: month;   text: DateConvert.ERR_MONTH;
                 font.pixelSize: 22;  font.bold: true; color: "black"; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter}
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)      }


        Rectangle {
            radius: 10
            id : greenRect
            gradient:
                Gradient {
                GradientStop {position: 0.0; color: "blue"}
                GradientStop {position: 1; color: "white"}}
            Layout.rowSpan : 1;        Layout.columnSpan : 3
            Text { id: dayWeek;  text: DateConvert.ERR_DAYWEEK; color: "black";   font.pixelSize: 25; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter; horizontalAlignment: Text.AlignHCenter;   verticalAlignment: Text.AlignVCenter}
            Layout.preferredWidth  : grid.prefWidth(this)
            Layout.preferredHeight : grid.prefHeight(this)}



    }


    Rectangle {

        width: 300
        height: 300
        x:250
        y:100
        color: "transparent"
        MouseArea {
            anchors.fill: parent
            onClicked: Spi.TurnOnDisplay()
            // onDragChanged: Spi.SetPowerSaver(0);
            // onPressedChanged: Spi.SetPowerSaver(0);
            onPressed: Spi.TurnOnDisplay();
        }



    }




    //SpinBox {
    //   x:35
    //   y:160
    //  id:sleep
    //   from: 20
    //   to:100
    //  value: 60
    //  width: 110
    //  height: 35
    //  onValueChanged: {Spi.SetPowerSaver();}
    //}
    //Text {
    // id: name3
    // x:5;    y:165
    // color: "white"
    //   font.family: "‌B Titr"
    //   text: qsTr("مایشگر")
    // font.bold: true
    // font.pixelSize: 12

    //}


}
