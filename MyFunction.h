#pragma once
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QStack>
#include <QString>
#include <QRegularExpression>
#include <QtDebug>
#include <string.h>

#ifndef MYFUNCTION_H
#define MYFUNCTION_H

struct Formulate //Описание вводимых символов
{
    char priority;  // Приоритет операции
    double value;   // Значение
};

class QPushButton;
class QLineEdit;

class MyFunction : public QWidget {
    Q_OBJECT
    private:
        QLineEdit* ptxt;
        QLabel* plblDisplay;
        QLabel* plbResult;
        QStack<Formulate> number;
        QStack<Formulate> operation;
        QString view_display;
        QString stand_display;

        bool flag_top=0;
        bool action = 0;
        bool flag_start=0;
        bool flag_operation=0;
        bool flag_open = 0;
        bool flag_drob=0;
        bool flag_minus=0;
        bool flag_negative = 0;
        bool flag_in_parenthesis = 0;
        int count_parenthesis = 0;

    public:
        Formulate item;
        bool calculate(QStack <Formulate>& number, QStack <Formulate>& operation, Formulate& item);
        MyFunction(QWidget* pwgt = 0);
        QPushButton* createButton(const QString& str);
        short getRang(char);
        void forming(double, char);
        QString to_qstring(double);
        ~MyFunction();

    public slots:
        void slotButtonClicked();
};

#endif // MYFUNCTION_H
