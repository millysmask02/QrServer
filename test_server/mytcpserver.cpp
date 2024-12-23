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
    QByteArray formArr;
    QString head = "HTTP/1.1 200 Ok\n \
                   Content-Type: " + QString::number(formArr.size());
    QByteArray headFormArr = head.toUtf8();
    QByteArray slashNArr = QString("\n\n").toUtf8();

    if (rowsChecking(QString(arr)) == EnumTypeRequest::Form) {
        formArr = typeForms("form.html").toUtf8();
        mTcpSocket->write(headFormArr + slashNArr + formArr);
    }
    else if (rowsChecking(QString(arr)) == EnumTypeRequest::Approved) {
        formArr = typeForms("formGreat.html").toUtf8();
        mTcpSocket->write(headFormArr + slashNArr + formArr);
    }
    else {
        formArr = typeForms("formSad.html").toUtf8();
        mTcpSocket->write(headFormArr + slashNArr + formArr);
    }

    mTcpSocket->flush();
    mTcpSocket->close();
    mTcpSocket->deleteLater();

    qDebug() << searchNewValues(arr);
}

QString MyTcpServer::typeForms(const QString& fileName) {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString name = file.readAll();
    file.close();

    return name;
}

QString MyTcpServer::searchNewValues(const QString& request) {
    QRegExp pcName("(lt=)(.*)(&id)");
    QRegExp pcSeries("(id=)(.*)(\r)");
    QRegExp username("(/?username=)(.*)(&place)");
    QRegExp place("(place=)(.*)(&time)");
    QRegExp time("(time=)(.*)(HTTP)");
    QString s = "";
    int pos=0;
    pcName.indexIn(request, pos);
    pcSeries.indexIn(request, pos);
    username.indexIn(request, pos);
    place.indexIn(request, pos);
    time.indexIn(request, pos);
    s.append(pcName.cap(2) + ";");
    s.append(pcSeries.cap(2) + ";");
    s.append(username.cap(2) + ";");
    s.append(place.cap(2) + ";");
    s.append(time.cap(2) + ";");

    return s;
    // if (!s.isEmpty()) {
    //     QFile file("pc_names_n_series.csv");
    //     if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
    //         QTextStream stream(&file);
    //         //stream << nameLaptopText << ";" << serialLaptopText << ";" << Qt::endl;
    //     }
    //     file.close();
    // } else {
    //     qDebug() << "Error!";
    // }
    // return "huy";
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
