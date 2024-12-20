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

private:
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    int rowsChecking(QString row);
};

class Enums : public QObject {
public:
    enum class EnumTypeRequest: int {
        Form,
        Approved,
        Error,
    };
    Q_ENUM(EnumTypeRequest)
    Q_OBJECT
    Enums() = delete;
};

#endif // MYTCPSERVER_H
