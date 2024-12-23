#include "names_added.h"
#include "ui_names_added.h"
#include <QString>
#include <QFile>
#include <QTextStream>

names_added::names_added(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::names_added)
{
    ui->setupUi(this);
}

names_added::~names_added()
{
    delete ui;
}

void names_added::on_addedButton_clicked()
{
    QString nameLaptopText = ui->nameLaptop->text();
    QString serialLaptopText = ui->serialLaptop->text();
    if (!nameLaptopText.isEmpty() && !serialLaptopText.isEmpty()) {
        QFile file("pc_names_n_series.csv");
        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream stream(&file);
            stream << nameLaptopText << ";" << serialLaptopText << ";" << Qt::endl;
        }
        file.close();
    } else {
        qDebug() << "Error!";
        return;
    }
    ui->nameLaptop->clear();
    ui->serialLaptop->clear();
    emit sendMes(nameLaptopText, serialLaptopText);
}
