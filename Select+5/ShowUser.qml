import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
Item {
    id:showuser
    visible: true
    width: Screen.width
    height:Screen.height
MouseArea{ anchors.fill: parent    }
    RowLayout {
        id: rowLayout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5


        spacing: 10


        Button {
            text: qsTr("خروج")


            onClicked: showuser.visible=false }
        Button {text: qsTr("مرتب سازی بانام")
            onClicked: { myModel.updateModel4()}  }
        Button {text: qsTr("مرتب سازی با شناسه")
            onClicked: { myModel.updateModel3(); }  }
    }

    Component.onCompleted: tableView.update();

    TableView {

        id: tableView
        anchors.top: rowLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        height: 50

        TableViewColumn {

            role: "id"
            title: "id"
        }
        TableViewColumn {
            role: "FullName"
            title: "FullName"
        }
        TableViewColumn {
            role: "CardNo"
            title: "CardNo"
        }
        TableViewColumn {
            role: "AccessType"
            title: "AccessType"
        }



        model: myModel

        // Setting lines in TableView to intercept mouse left click

    }



}


