#include "MyModel.h"

MyModel::MyModel()
{
    qDebug() << "CONSTRUCTOR MyModel";
    flag_top=0;
    action = 0;
    flag_start=0;
    flag_operation=0;
    flag_open = 0;
    flag_drob=0;
    flag_minus=0;
    flag_negative = 0;
    flag_in_parenthesis = 0;
    count_parenthesis = 0;
}

//Функция возвращает приоритет операции - "1" для сложения и вычитания, "2" для умножения и деления
short MyModel::getRang(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}

void MyModel::forming(double value, char pr)
{
    item.priority = pr;
    item.value = value;
}

bool MyModel::calculate(QStack<Formulate>& Number_Stack, QStack<Formulate>& Operation_Stack, Formulate& item)
{
    double a, b, c;
    a = Number_Stack.top().value;                   //Берется верхнее число из стека с числами
    Number_Stack.pop();                             //Удаляется верхнее число из стека с числами
    switch (Operation_Stack.top().priority) {       //Проверяется тип верхней операции из стека с операциями
    case '+':                                       //Если тип верхней операции из стека с операциями сложение
        b = Number_Stack.top().value;
        Number_Stack.pop();
        c = a + b;
        forming(c, 0);
        Number_Stack.push(item);    //Результат операции кладется обратно в стек с числами
        Operation_Stack.pop();
        qDebug() << "result  = " << c;
        break;
    case '-':
        b = Number_Stack.top().value;
        Number_Stack.pop();
        c = b - a;
        forming(c, 0);
        Number_Stack.push(item);
        Operation_Stack.pop();
        qDebug() << "result  = " << c;
        break;
    case '*':
        b = Number_Stack.top().value;
        Number_Stack.pop();
        c = a * b;
        forming(c, 0);
        Number_Stack.push(item);
        Operation_Stack.pop();
        qDebug() << "result  = " << c;
        break;
    case '/':
        b = Number_Stack.top().value;
        if (a == 0) {
            return false;
        }
        else {
            Number_Stack.pop();
            c = (b / a);
            forming(c, 0);
            Number_Stack.push(item);
            Operation_Stack.pop();
            qDebug() << "result  = " << c;
            break;
        }
        default:
            return false;
            break;
        }
    return true;
}

QString MyModel::slotButtonClicked(QString str)
{
    if (str == "Clear")
    {
        number.clear();
        operation.clear();
        view_display.clear();
        stand_display.clear();
        flag_top = 0;
        flag_operation = 0;
        flag_start = 0;
        flag_open = 0;
        flag_drob=0;
        flag_negative=0;
        count_parenthesis = 0;
        return str;
    }
    if (str.contains(QRegularExpression("[0-9]")))
    {
        flag_start = 1;
        flag_open = 0;
        flag_operation = 0;
        stand_display += str;
        view_display += str;

        if(flag_top==1)
            number.pop();   //Число удаляется из стека
        if(flag_drob==0 && flag_negative==0)
            forming(view_display.toDouble(), getRang(view_display[0].toLatin1()));
        else if(flag_drob==1 && flag_negative==0)
            forming(view_display.toDouble()/10, getRang(view_display[0].toLatin1()));
        else if(flag_drob==0 && flag_negative==1)
            forming(0-view_display.toDouble(), getRang(view_display[0].toLatin1()));
        else if(flag_drob==1 && flag_negative==1)
            forming(0-view_display.toDouble()/10, getRang(view_display[0].toLatin1()));
        number.push(item);  //Число кладется в стек с числами
        flag_top=1;
        return stand_display;
    }
    else if (str == "." && flag_start==1 && flag_drob==0 && flag_operation==0)
    {
        stand_display += str;
        flag_drob = 1;
        return stand_display;
    }
    else if((str=="-" && flag_start==0 && flag_negative==0) || (str=="-" && flag_open==1 && flag_negative==0))
    {
        stand_display += str;
        flag_negative = 1;
        flag_open = 0;
        return stand_display;
    }
    else if(str.contains(QRegularExpression("[\\+\\-\\*\\/]")) && flag_start==1 && flag_operation==0 && flag_open==0)
    {
        flag_operation = 1;
        flag_top = 0;
        flag_drob = 0;
        flag_negative=0;

        stand_display += str;
        view_display.clear();
        view_display = str;

        forming(-1, view_display[0].toLatin1());
        if (operation.size() == 0) {    //Если стек с операциями пуст
            operation.push(item);       //Операция кладется в стек с операциями
            view_display.clear();
            return stand_display;
        }
        if (operation.size() != 0 && getRang(item.priority) > getRang(operation.top().priority)) { //Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
            operation.push(item);   //Операция кладется в стек с операциями
            view_display.clear();
            return stand_display;
        }
        if (operation.size() != 0 && getRang(item.priority) <= getRang(operation.top().priority))
        {
            if (calculate(number, operation, item) == false) //Если функция вернет "false", то прекращаем работу
            {
                view_display.clear();
                return stand_display;
            }
            forming(-1, view_display[0].toLatin1());
            operation.push(item);   //Операция кладется в стек с операциями
            view_display.clear();
            return stand_display;
        }
        view_display.clear();
        return stand_display;
    }
    else if((str=="(" && flag_start==0 && flag_negative == 0) || (str=="(" && flag_start==1 && flag_operation==1 && flag_negative == 0))
    {
        count_parenthesis++;
        flag_top = 0;
        flag_open = 1;
        flag_drob = 0;
        flag_negative=0;

        stand_display += str;
        view_display.clear();
        view_display = str;

        forming(-1, view_display[0].toLatin1());
        operation.push(item);       //Операция кладется в стек с операциями
        view_display.clear();
        return stand_display;
    }
    else if(str==")" && flag_start==1 && flag_operation == 0 && count_parenthesis>0)
    {
        flag_top = 0;
        flag_drob = 0;
        flag_negative=0;
        count_parenthesis--;
        stand_display += str;

        while (operation.top().priority != '(')  //Вызываем матем. функцию до тех пор, пока в стеке с операциями не будет 0 элементов
        {
            if (calculate(number, operation, item) == false){ //Если функция вернет "false", то прекращаем работу
                stand_display = "ERROR_1";
                break;
            }
            else
                continue; //Если все хорошо
        }
        operation.pop();
        return stand_display;
    }
    else if(str == "=" && flag_start==1 && flag_operation == 0 && count_parenthesis==0)
    {
        flag_drob=0;
        stand_display += str;
        view_display.clear();
        view_display = str;

        while (operation.size() != 0)  //Вызываем функцию до тех пор, пока в стеке с операциями не будет 0 элементов
        {
            if (calculate(number, operation, item) == false) //Если функция вернет false, то прекращаем работу
            {
                stand_display = "ERROR_2";
                break;
            }
            else
                continue; //Если все хорошо
        }

        view_display.clear();
        std::string t_str = std::to_string(number.top().value);
        view_display = QString::fromLocal8Bit(t_str.c_str());
        return (stand_display+view_display);
    }
    return stand_display;
}

MyModel::~MyModel()
{
    number.clear();
    operation.clear();
    view_display.clear();
    stand_display.clear();
}
