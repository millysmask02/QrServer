#include "mytcpserver.h"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

#include <QString>
#include <QRegExp>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 8000)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
    // qDebug() << searchNewValues("GET lt=asus&id=ksk0192&username=masha&place=room10&time=day HTTP");
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
    QStringList values = searchValues(arr);

    QByteArray formArr;
    QString head = "HTTP/1.1 200 Ok\n \
                   Content-Type: " + QString::number(formArr.size());
    QByteArray headFormArr = head.toUtf8();
    QByteArray slashNArr = QString("\n\n").toUtf8();

    if (rowsChecking(QString(arr)) == EnumTypeRequest::Form) {
        QString form = typeForms("form.html");
        form = form.arg(values[0]).arg(values[1]);
        formArr = form.toUtf8();
    }
    else if (rowsChecking(QString(arr)) == EnumTypeRequest::Approved) {
        formArr = typeForms("formGreat.html").toUtf8();
        saveToFile(values[0], values[1], values[2], values[3], values[4]);
    }
    else {
        formArr = typeForms("formSad.html").toUtf8();
    }

    mTcpSocket->write(headFormArr + slashNArr + formArr);

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

QStringList MyTcpServer::searchValues(const QString&request) {
    QStringList info;
    QString value;
    int id = request.indexOf("HTTP");
    int i = 0;
    int start;
    while(i < id) {

        start = request.indexOf("=", i) + 1;

        if (start > id || start == -1) break;

        int end = request.indexOf("&", start);

        if (end > id || end == -1) break;

        i = end;

        value = request.mid(start, end - start);
        info.append(value);

        qDebug() << i << start << end << value << id;
    }
    value = request.mid(start, id - start - 1);
    info.append(value);

    return info;
}

void MyTcpServer::saveToFile(const QString& value, const QString& value2, const QString& value3, const QString& value4, const QString& value5) {
    if (!value.isEmpty() && !value2.isEmpty() && !value3.isEmpty() && !value4.isEmpty() && !value5.isEmpty()) {
        QFile file("moving_laptop.csv");
        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream stream(&file);
            stream << value << ";" << value2 << ";" << value3 << ";" << value4 << ";" << value5 << Qt::endl;
        }
        file.close();
    } else {
        qDebug() << "Error!";
    }
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
