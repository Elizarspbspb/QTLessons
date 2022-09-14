#ifndef MYMODEL_H
#define MYMODEL_H

#include <QStack>
#include <QString>
#include <QRegularExpression>
#include <QtDebug>

struct Formulate //Описание вводимых символов
{
    char priority;  // Приоритет операции
    double value;   // Значение
};

class MyModel
{
private:
    QStack<Formulate> number;
    QStack<Formulate> operation;

    bool flag_top;
    bool action;
    bool flag_start;
    bool flag_operation;
    bool flag_open;
    bool flag_drob;
    bool flag_minus;
    bool flag_negative;
    bool flag_in_parenthesis;
    int count_parenthesis;

    QString stand_display;
    QString view_display;

    Formulate item;

public:

    MyModel();

    bool calculate(QStack <Formulate>& number, QStack <Formulate>& operation, Formulate& item);  // Вычисления
    short getRang(char);            // Получить приоритет операции
    void forming(double, char);     // Сформировать элемент
    QString slotButtonClicked(QString);

    ~MyModel();
};

#endif // MYMODEL_H
