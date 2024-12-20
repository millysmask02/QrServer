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
    enum class EnumTypeRequest {
        Form,
        Approved,
        Error,
    };
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    QString typeForms(const QString& fileName);
    EnumTypeRequest rowsChecking(QString row);
};

#endif // MYTCPSERVER_H
