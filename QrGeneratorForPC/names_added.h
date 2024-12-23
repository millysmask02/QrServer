#ifndef NAMES_ADDED_H
#define NAMES_ADDED_H

#include <QDialog>

namespace Ui {
class names_added;
}

class names_added : public QDialog
{
    Q_OBJECT

public:
    explicit names_added(QDialog *parent = nullptr);
    ~names_added();

private slots:
    void on_addedButton_clicked();

signals:
    void sendMes(QString name, QString series);

private:
    Ui::names_added *ui;
};

#endif // NAMES_ADDED_H
