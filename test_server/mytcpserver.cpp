#include "mytcpserver.h"
#include <QDebug>
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

    QString form = "<!DOCTYPE html>\
<html lang=\"ru\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Регистрация</title>\
                   <style>\
                   body {\
    display: flex;\
        justify-content: center;\
        align-items: center;\
        min-height: 100vh;\
        margin: 0;\
        background-color: #f0f0f0;\
    }\
    .form-container {\
        text-align: center;\
        padding: 30px;\
        border: 2px solid #ccc;\
        border-radius: 12px;\
        background-color: white;\
        box-shadow: 0 4px 8px rgba(0,0,0,0.1);\
    }\
    .form-row {\
        margin-bottom: 20px;\
        display: flex;\
        align-items: center;\
        justify-content: center;\
    }\
    label {\
    display: inline-block;\
    width: 150px;\
        text-align: center;\
        font-weight: bold;\
        margin-right: 5px;\
        font-size: 1.2em;\
    }\
    input[type=\"text\"] {\
    padding: 12px;\
    border: 1.5px solid #ccc;\
    border-radius: 6px;\
    box-sizing: border-box;\
    margin-right: 10%;\
    width: 350px;\
    font-size: 1.2em;\
    font-family: system-ui;\
    }\
    button {\
    padding: 15px 30px;\
        background-color: #4CAF50;\
    color: white;\
    border: none;\
        border-radius: 6px;\
    cursor: pointer;\
        margin-top: 20px;\
        font-size: 1.2em;\
    transition: background-color 0.3s;\
    }\
button:hover {\
          background-color: #45a049;\
}\
</style>\
</head>\
<body>\
    <div class=\"form-container\">\
        <div class=\"form-row\">\
            <label for=\"username\">Имя:</label>\
            <input type=\"text\" id=\"username\" name=\"username\">\
        </div>\
        <div class=\"form-row\">\
            <label for=\"place\">Место:</label>\
            <input type=\"text\" id=\"place\" name=\"place\">\
        </div>\
        <div class=\"form-row\">\
            <label for=\"text\">Время:</label>\
            <input type=\"text\" id=\"text\" name=\"text\">\
        </div>\
        <button>Отправить</button>\
    </div>\
</body>\
</html>";

QString formGreat = "<!DOCTYPE html>\
                        <html lang=\"ru\">\
          <head>\
          <meta charset=\"UTF-8\">\
          <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
          <title>Запрос принят</title>\
          <style>\
          body {\
    display: flex;\
        justify-content: center;\
        align-items: center;\
        min-height: 100vh;\
    margin: 0;\
        background-color: #f0f0f0;\
    }\
    .message-container {\
        text-align: center;\
    padding: 40px;\
        background-color: white;\
        border-radius: 10px;\
        box-shadow: 0 4px 8px rgba(0,0,0,0.1);\
    border: 2px solid #4CAF50;\
    }\
    h1 {\
    color: #4CAF50;\
        font-size: 2em;\
        margin-bottom: 20px;\
        text-shadow: 1px 1px 2px rgba(0,0,0,0.1);\
    }\
    p {\
    color: #555;\
        font-size: 1.2em;\
        line-height: 1.6;\
        text-shadow: 1px 1px 2px rgba(0,0,0,0.05);\
    }\
    </style>\
        </head>\
        <body>\
        <div class=\"message-container\">\
        <h1>Ваш запрос принят, данные получены!</h1>\
                                    <p>Спасибо за ваш запрос. Мы получили ваши данные и обрабатываем их. Скоро с вами свяжутся.</p>\
                                    </div>\
                                    </body>\
         </html>";

QString formSad = "<!DOCTYPE html>\
                  <html lang=\"ru\">\
      <head>\
      <meta charset=\"UTF-8\">\
      <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
      <title>Кот</title>\
      <style>\
      body {\
display: flex;\
    justify-content: center;\
    align-items: center;\
    min-height: 100vh;\
margin: 0;\
    background-color: #f0f0f0;\
}\
.cat-container {\
    text-align: center;\
    border-radius: 15px;\
    background-color: white;\
padding: 20px;\
    box-shadow: 0 4px 8px rgba(0,0,0,0.1);\
}\
img {\
    max-width: 500px;\
height: auto;\
    border-radius: 10px;\
display: block;\
margin: 0 auto;\
    box-shadow: 2px 2px 10px rgba(0,0,0,0.2);\
}\
</style>\
    </head>\
    <body>\
    <div class=\"cat-container\">\
    <img src=\'Images\\cat.jpg\' alt=\"Грустный кот\">\
    </div>\
    </body>\
                  </html>";

    QByteArray formArr = form.toUtf8();
    QByteArray formGreatArr = formGreat.toUtf8();
    QByteArray formSadArr = formSad.toUtf8();
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

EnumTypeRequest MyTcpServer::rowsChecking(QString row) {
    if (row.startsWith("GET") && (row.contains("HTTP") && row.contains("lt=") && row.contains("id="))) {
        if (row.contains("username") && row.contains("place") && row.contains("time")) {
            return EnumTypeRequest::Approved;
        }
        return EnumTypeRequest::Form;
    }
    return EnumTypeRequest::Error;
}
