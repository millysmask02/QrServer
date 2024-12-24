#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);

public slots:
    void slotNewConnection();
    void slotServerRead();
    void saveToFile(const QStringList& values);

private:
    enum class EnumTypeRequest {
        Form,
        Approved,
        Error,
    };
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    bool isFailed = true;
    QString typeForms(const QString& fileName);
    QStringList searchValues(const QString&request);
    EnumTypeRequest rowsChecking(QString row);
};

#endif // MYTCPSERVER_H
