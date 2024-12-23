#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "names_added.h"
#include <QImage>
#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <generate.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Generate gen;
    QFile file("pc_names_n_series.csv");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        auto spisok = stream.readLine().split(";");
        map[spisok[0]] = spisok[1];
    }
    file.close();
    QStringList keys = map.keys();
    ui->selectLaptop->addItems(keys);
    connect(&na, &names_added::sendMes, this, &MainWindow::receiveMes);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveMes(QString name, QString series) {
    map[name] = series;
    ui->selectLaptop->addItem(name);
}

void MainWindow::on_generation_clicked()
{
    QString pc_name = ui->selectLaptop->currentText();
    QString pc_series = map[ui->selectLaptop->currentText()];
    Generate QR;
    QR.setPCnameSeries(pc_name, pc_series);
    qDebug() << QR.generateQR();
}

void MainWindow::on_switchForm_clicked()
{
    na.exec();
}
