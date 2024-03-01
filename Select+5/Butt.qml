import QtQuick 2.0
import QtQuick.Window 2.0

Item {
    //id:reasybutton
    signal bclicked()
    property int bx:0
    property int by:0
    property int bwidth:Screen.width/4.44
    property int bheight:Screen.height/4.44
    property string btext:"button"
    property string bicon:"qrc:/zDownload.png"
    property string bcolorBorder1:"transparent"
    property string bcolorBorder2:"red"
    property string bcolorText1:"black"
    property string bcolorText2:"red"
    property color tcolor: "white"
    Rectangle {
        id:rect
        width:bwidth
        height:bheight
        x:bx
        y:by
        border.color: mid.pressed ? bcolorBorder2 : bcolorBorder1;
        border.width: mid.pressed ? 7 : 4 ;
        radius: 30
        color: "transparent"
        // gradient: Gradient {
        // GradientStop { position: 0.0; color: "#920341"}
        //  GradientStop { position: 1.0; color: "blue" }
        //}


        Image {
            //anchors.centerIn: parent.Center
            id: background
            width: Screen.width/11.4
            height: Screen.width/11.4
            // anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: bicon}

        Text {
            y:70
            id:t1
            color: mid.pressed ? bcolorText2 : bcolorText1;
            font.bold:true;
            font.pixelSize: 18;
            text: btext
            width: bwidth
            height: 40
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            //font.italic: true
            font.pointSize: 16
            font.family: "Titr"

            //anchors.verticalCenter: parent.bottom

        }

        MouseArea {
            id: mid

            anchors.fill: parent
            onClicked: {   bclicked();    }
        }
    }
}
