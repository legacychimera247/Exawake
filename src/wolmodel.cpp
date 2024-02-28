#include "wolmodel.h"
#include "wol.cpp/wol.cpp"

WOLModel::WOLModel(QAbstractListModel *parent) : QAbstractListModel(parent)
{
    _settings = new QSettings("verdanditeam", "exawake");

    int size = _settings->beginReadArray("servers");
    for (int i = 0; i < size; ++i) {
        _settings->setArrayIndex(i);
        Server server;
        server.name = _settings->value("name").toString();
        server.mac = _settings->value("mac").toString();
        server.broadcast = _settings->value("broadcast").toString();
        server.port = _settings->value("port").toUInt();
        _servers.append(server);
    }
    _settings->endArray();
}

int WOLModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _servers.length();
}

QVariant WOLModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount()) return QVariant();

    auto server = _servers[index.row()];
    switch (role) {
    case Roles::NameRole:
        return server.name;
    case Roles::MacRole:
        return server.mac;
    case Roles::BroadcastRole:
        return server.broadcast;
    case Roles::PortRole:
        return server.port;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> WOLModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[MacRole] = "mac";
    roles[BroadcastRole] = "broadcast";
    roles[PortRole] = "port";
    return roles;
}

void WOLModel::addServer(QString name, QString mac, QString broadcast, uint port)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    Server server;
    server.name = name;
    server.mac = mac;
    server.broadcast = broadcast;
    server.port = port;
    _servers.append(server);
    endInsertRows();

    saveServers();
}

void WOLModel::editServer(int index, QString name, QString mac, QString broadcast, uint port)
{
    if (index < 0 || index >= rowCount()) return;

    auto &server = _servers[index];
    server.name = name;
    server.mac = mac;
    server.broadcast = broadcast;
    server.port = port;
    saveServers();

    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

void WOLModel::wakeUpServer(int index)
{
    if (index < 0 || index >= rowCount()) return;

    auto server = _servers[index];

    send_wol(server.mac.toStdString(), server.port, inet_addr(server.broadcast.toUtf8()));
}

void WOLModel::deleteServer(int index)
{
    if (index < 0 || index >= rowCount()) return;

    beginRemoveRows(QModelIndex(), index, index);
    _servers.remove(index);
    saveServers();
    endRemoveRows();
}

void WOLModel::saveServers()
{
    _settings->beginWriteArray("servers", _servers.size());
    int index = 0;
    for(const Server &server: _servers) {
        _settings->setArrayIndex(index);
        _settings->setValue("name", server.name);
        _settings->setValue("mac", server.mac);
        _settings->setValue("broadcast", server.broadcast);
        _settings->setValue("port", server.port);
        index++;
    }
    _settings->endArray();
}

