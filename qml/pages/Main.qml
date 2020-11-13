import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Servers")
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }

            MenuItem {
                text: qsTr("Add server")
                onClicked: pageStack.push(addEditDialog, {index: -1, name: "", mac: "", broadcast: "", port: 0})
            }
        }

        model: wolModel

        delegate: ListItem {
            id: listItem

            DetailItem {
                anchors.verticalCenter: parent.verticalCenter
                label: name
                value: mac
            }

            function remove() {
                remorseAction("Deleting", function() { wolModel.deleteServer(index) })
            }

            menu: Component {
                ContextMenu {
                    MenuItem {
                        text: qsTr("Edit")
                        onClicked: pageStack.push(addEditDialog, {index: index, name: name, mac: mac, broadcast: broadcast, port: port})
                    }
                    MenuItem {
                        text: qsTr("Delete")
                        onClicked: remove()
                    }
                }
            }

            onClicked: wolModel.wakeUpServer(index)
        }
        VerticalScrollDecorator {}
    }

    ServerEditDialog {
        id: addEditDialog

        onDone: {
            if (result == DialogResult.Accepted) {
                if (index === -1) {
                    wolModel.addServer(name, mac, broadcast, port)
                } else {
                    wolModel.editServer(index, name, mac, broadcast, port)
                }
            }
        }
    }
}
