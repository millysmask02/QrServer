#include "mytcpserver.h"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

#include <QString>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 8000)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
}

void MyTcpServer::slotServerRead()
{
    mTcpSocket = (QTcpSocket*)this->sender();
    QByteArray arr = mTcpSocket->readAll();
    qDebug() << arr.toStdString();

    QByteArray formArr = typeForms("form.html").toUtf8();
    QByteArray formGreatArr = typeForms("formGreat.html").toUtf8();
    QByteArray formSadArr = typeForms("formSad.html").toUtf8();
    QString head = "HTTP/1.1 200 Ok\n \
                   Content-Type: " + QString::number(formArr.size());
    QByteArray headFormArr = head.toUtf8();
    QByteArray slashNArr = QString("\n\n").toUtf8();

    if (rowsChecking(QString(arr)) == EnumTypeRequest::Form) {
        mTcpSocket->write(headFormArr + slashNArr + formArr);
    }
    else if (rowsChecking(QString(arr)) == EnumTypeRequest::Approved) {
        mTcpSocket->write(headFormArr + slashNArr + formGreatArr);
    }
    else {
        mTcpSocket->write(headFormArr + slashNArr + formSadArr);
    }

    mTcpSocket->flush();
    mTcpSocket->close();
    mTcpSocket->deleteLater();
}

QString MyTcpServer::typeForms(const QString& fileName) {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString name = file.readAll();
    file.close();

    return name;
}

MyTcpServer::EnumTypeRequest MyTcpServer::rowsChecking(QString row) {
    if (row.startsWith("GET") && (row.contains("HTTP") && row.contains("lt=") && row.contains("id="))) {
        if (row.contains("username") && row.contains("place") && row.contains("time")) {
            return EnumTypeRequest::Approved;
        }
        return EnumTypeRequest::Form;
    }
    return EnumTypeRequest::Error;
}
