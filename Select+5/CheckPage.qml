import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.0
Item {


    id:checkPage
    visible: true
    focus: true
    width: 800
    height: 480
MouseArea{ anchors.fill: parent    }
    Rectangle{
        id:rect2
        anchors.fill: parent
        gradient:
            Gradient {
            GradientStop {position: 0.0; color: "black"}
            GradientStop {position: 1; color: "blue"}}

        Text {
            id: fingerSerial
            text: Ver.ERR_CHECKFINGER
            x:100
            y:100
            color: "White";  font.bold: true; font.pixelSize: 15;

        }

        Text {
            id: rfidSerial
            text: Ver.ERR_CHECKRFID
            x:100
            y:200
            color: "White";  font.bold: true; font.pixelSize: 15;
        }


        Text {
            id: printerSerial
            text: Ver.ERR_CHECKPRINTER
            x:100
            y:300
            color: "White";  font.bold: true; font.pixelSize: 15;
        }


        Button {
            text: "خروج"
            x:400;
            y:380;
            onClicked: { checkPage.visible=false  }

        }







    }
}
