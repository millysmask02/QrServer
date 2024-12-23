#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "names_added.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generation_clicked();

    void on_switchForm_clicked();

    void receiveMes(QString name, QString series);

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> map;
    names_added na;
};
#endif // MAINWINDOW_H
