import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property int index
    property string name
    property string mac
    property string broadcast
    property int port

    Column {
        width: parent.width
        spacing: Theme.paddingLarge

        DialogHeader { }

        TextField {
            id: nameField
            width: parent.width
            placeholderText: "Name"
            hideLabelOnEmptyField: false
            text: name
            label: "Name"
        }

        TextField {
            id: macField
            width: parent.width
            placeholderText: "Mac address"
            hideLabelOnEmptyField: false
            validator: RegExpValidator { regExp: /^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$/ }
            text: mac
            label: "Mac address"
        }

        TextField {
            id: broadcastField
            width: parent.width
            placeholderText: "Broadcast address"
            text: broadcast !== "" ? broadcast : "255.255.255.255"
            validator: RegExpValidator { regExp: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/ }
            label: "Broadcast address"
        }

        TextField {
            id: portField
            width: parent.width
            placeholderText: "Port"
            text: port !== 0 ? port : "60000"
            label: "Port"
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            name = nameField.text
            mac = macField.text
            broadcast = broadcastField.text
            port = portField.text
        }
    }
}
