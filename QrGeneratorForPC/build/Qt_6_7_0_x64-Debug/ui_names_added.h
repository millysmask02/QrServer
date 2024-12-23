/********************************************************************************
** Form generated from reading UI file 'names_added.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAMES_ADDED_H
#define UI_NAMES_ADDED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_names_added
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *nameLaptop;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *serialLaptop;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addedButton;

    void setupUi(QWidget *names_added)
    {
        if (names_added->objectName().isEmpty())
            names_added->setObjectName("names_added");
        names_added->resize(648, 444);
        verticalLayout = new QVBoxLayout(names_added);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(names_added);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        nameLaptop = new QLineEdit(names_added);
        nameLaptop->setObjectName("nameLaptop");

        horizontalLayout->addWidget(nameLaptop);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(names_added);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        serialLaptop = new QLineEdit(names_added);
        serialLaptop->setObjectName("serialLaptop");

        horizontalLayout_2->addWidget(serialLaptop);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addedButton = new QPushButton(names_added);
        addedButton->setObjectName("addedButton");
        addedButton->setFont(font);

        horizontalLayout_3->addWidget(addedButton);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(names_added);

        QMetaObject::connectSlotsByName(names_added);
    } // setupUi

    void retranslateUi(QWidget *names_added)
    {
        names_added->setWindowTitle(QCoreApplication::translate("names_added", "Form", nullptr));
        label->setText(QCoreApplication::translate("names_added", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\275\320\276\321\203\321\202\320\260:", nullptr));
        label_2->setText(QCoreApplication::translate("names_added", "\320\241\320\265\321\200\320\270\320\271\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200 \320\275\320\276\321\203\321\202\320\260:", nullptr));
        addedButton->setText(QCoreApplication::translate("names_added", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class names_added: public Ui_names_added {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAMES_ADDED_H
