#ifndef WOLMODEL_H
#define WOLMODEL_H

#include <QAbstractListModel>
#include <QSettings>

class WOLModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        MacRole,
        BroadcastRole,
        PortRole
    };

    struct Server {
        QString name;
        QString mac;
        QString broadcast;
        uint port;
    };

    explicit WOLModel(QAbstractListModel *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = NameRole) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void addServer(QString name, QString mac, QString broadcast, uint port);
    Q_INVOKABLE void editServer(int index, QString name, QString mac, QString broadcast, uint port);
    Q_INVOKABLE void wakeUpServer(int index);
    Q_INVOKABLE void deleteServer(int index);

signals:

public slots:

private:
    QSettings* _settings;
    QVector<Server> _servers;

    void saveServers();
};

#endif // WOLMODEL_H
