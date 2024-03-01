import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Item {
id:removeuser
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

    Text {text: qsTr("شماره شناسه برای حذف");         color: "white" }
    TextField { id: idremove }
    Text {id:message; text: qsTr("");         color: "Red" }
    Button {  text: qsTr("حذف")

    onClicked: {  dialogDelete.open()  }}
    Button {text: qsTr("خروج")
    onClicked: { removeuser.visible=false; }  }

    Button {text: qsTr("مرتب سازی بانام")
    onClicked: { myModel.updateModel4()}  }
    Button {text: qsTr("مرتب سازی با شناسه")
    onClicked: { myModel.updateModel3(); }  }
}

Component.onCompleted: tableView.update();

TableView {
    height: 50
    id: tableView
    anchors.top: rowLayout.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 5

    TableViewColumn {
        role: "id"
        title: "شناسه"
    }
    TableViewColumn {
        role: "FullName"
        title: "نام کامل"
    }
    TableViewColumn {
        role: "CardNo"
        title: "شماره کارت"
    }
    TableViewColumn {
        role: "AccessType"
        title: "سطح دسترسی"
    }

    model: myModel



}


MessageDialog {
    id: dialogDelete
    title: qsTr("حذف رکورد")
    text: qsTr("آیا درخواست جاری را تایید میکنید؟")
    icon: StandardIcon.Warning
    standardButtons: StandardButton.Ok | StandardButton.Cancel

    // If the answer ...
    onAccepted: {
        /* ... remove the line by id, which is taken from the data model
         * on the line number in the presentation
         * */
         message.text=Ver.Deleteone(idremove.text);     myModel.updateModel();  tableView.model=myModel;   tableView.update(); dialogDelete.close()

        //database.removeRecord(myModel.getId(tableView.currentRow))
        //myModel.updateModel();
    }
}
}


