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

        spacing: 15


        Button {
            text: qsTr("EXIT")

            // Make a new entry in the database
            onClicked: showuser.visible=false
        }
    }

    Component.onCompleted: { myModel.updateModel2();    tableView.update(); }

    TableView {

        id: tableView
        anchors.top: rowLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5

        TableViewColumn {
            role: "id"
            title: "id"
            width: 50
        }
        TableViewColumn {
            role: "FullName"
            title: "FullName"

        }
        TableViewColumn {
            role: "CardNo"
            title: "CardNo"
            width: 150
        }
        TableViewColumn {
            role: "AccessType"
            title: "DateTime"
            width: 350
        }

        TableViewColumn {
            role: "FingerIdL"
            title: "Type"
            width: 100
        }


        model: myModel

        // Setting lines in TableView to intercept mouse left click

    }}

