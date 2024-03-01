import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Item {
id:searchlogs
visible: true
width: 800
height: 480

MouseArea{ anchors.fill: parent    }

RowLayout {
    id: rowLayout
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 5

    spacing: 10
       Text {text: qsTr("Search By Id");         color: "white" }
    TextField { id: idField   }
    Button {  text: qsTr("Search")

        // Make a new entry in the database
        onClicked: {      myModel.updateSearchLog(idField.text); tableView.model=myModel;   tableView.update();  }

    }

    Button {
        text: qsTr("EXIT")

        // Make a new entry in the database
        onClicked: searchlogs.visible=false
    }


}



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
        title: "DateTime"
    }




    // Setting lines in TableView to intercept mouse left click

}}

