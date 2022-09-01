#include "MyModel.h"

MyModel::MyModel(QObject *parent) : QAbstractItemModel{parent}
{

}

int MyModel::columnCount(const QModelIndex &) const
{
    return 1;
}

int MyModel::rowCount(const QModelIndex &) const
{
    return m_data.size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        return m_data.at(index.row());  // Индекс содержит и колонны и строчки и родителя
    }
    return QVariant();
}

QModelIndex MyModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column, (void*)&m_data[row]);
    //return createIndex(row, column, (void*)&m_data);
}

// Функция для получения родителя
QModelIndex MyModel::parent(const QModelIndex &) const
{
    return QModelIndex();
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

MyModel::~MyModel()
{
    number.clear();
    operation.clear();
    view_display.clear();
    stand_display.clear();
}

bool MyModel::calculate(QStack<Formulate>& Number_Stack, QStack<Formulate>& Operation_Stack, Formulate& item)
{
    double a, b, c;
    a = Number_Stack.top().value;     //Берется верхнее число из стека с числами
    Number_Stack.pop();                                             //Удаляется верхнее число из стека с числами
    switch (Operation_Stack.top().priority) {     //Проверяется тип верхней операции из стека с операциями
    case '+':                                               //Если тип верхней операции из стека с операциями сложение
        b = Number_Stack.top().value;
        Number_Stack.pop();
        c = a + b;
        forming(c, 0);
        Number_Stack.push(item); //Результат операции кладется обратно в стек с числами
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

void MyModel::slotButtonClicked(QString str)
{
    //m_data.append(view_display);
    //view_display.append(view_display);

    //emit layoutChanged();
    //plblDisplay->setText(view_display);

    //QString str = ((QPushButton*)sender())->text();
    if (str == "Clear")
    {
        //plblDisplay->setText("0");
        //ptxt->setText("0");

        m_data.append("0");
        //view_display.append("0");

        emit layoutChanged();

        number.clear();
        operation.clear();
        view_display = "";
        stand_display = "";
        flag_top = 0;
        flag_operation = 0;
        flag_start = 0;
        flag_open = 0;
        flag_drob=0;
        flag_negative=0;
        count_parenthesis = 0;
        emit layoutChanged();
        return;
    }
    if (str.contains(QRegularExpression("[0-9]")))
    {
        flag_start = 1;
        flag_open = 0;
        flag_operation = 0;

        stand_display += str;
        view_display += str;
        //ptxt->setText(stand_display);

        m_data.append(stand_display);
        //view_display.append(stand_display);

        emit layoutChanged();

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
        emit layoutChanged();
    }
    else if (str == "." && flag_start==1 && flag_drob==0 && flag_operation==0) {
        stand_display += str;
        //ptxt->setText(stand_display);

        m_data.append(stand_display);
        //view_display.append(stand_display);

        emit layoutChanged();

        flag_drob = 1;
        emit layoutChanged();
    }
    else if((str=="-" && flag_start==0 && flag_negative==0) || (str=="-" && flag_open==1 && flag_negative==0))
    {
        stand_display += str;
        //ptxt->setText(stand_display);

        m_data.append(stand_display);
        //view_display.append(stand_display);

        emit layoutChanged();

        flag_negative = 1;
        flag_open = 0;
        emit layoutChanged();
    }
    else if(str.contains(QRegularExpression("[\\+\\-\\*\\/]")) && flag_start==1 && flag_operation==0 && flag_open==0)
    {
        flag_operation = 1;
        flag_top = 0;
        flag_drob = 0;
        flag_negative=0;

        stand_display += str;
        //ptxt->setText(stand_display);

        m_data.append(stand_display);
        //view_display.append(stand_display);

        emit layoutChanged();

        view_display.clear();
        view_display = str;

        forming(-1, view_display[0].toLatin1());
        if (operation.size() == 0) { //Если стек с операциями пуст
            operation.push(item); //Операция кладется в стек с операциями
            view_display.clear();
            emit layoutChanged();
            return;
        }
        if (operation.size() != 0 && getRang(item.priority) > getRang(operation.top().priority)) { //Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
            operation.push(item); //Операция кладется в стек с операциями
            view_display.clear();
            emit layoutChanged();
            return;
        }
        if (operation.size() != 0 && getRang(item.priority) <= getRang(operation.top().priority))
        {
            if (calculate(number, operation, item) == false) //Если функция вернет "false", то прекращаем работу
            {
                view_display.clear();
                emit layoutChanged();
                return;
            }
            forming(-1, view_display[0].toLatin1());
            operation.push(item); //Операция кладется в стек с операциями
            view_display.clear();
            emit layoutChanged();
            return;
        }
        view_display.clear();
        emit layoutChanged();
    }
    else if((str=="(" && flag_start==0 && flag_negative == 0) || (str=="(" && flag_start==1 && flag_operation==1 && flag_negative == 0))
    {
        count_parenthesis++;
        flag_top = 0;
        flag_open = 1;
        flag_drob = 0;
        flag_negative=0;

        stand_display += str;
        //ptxt->setText(stand_display);

        m_data.append(stand_display);
        //view_display.append(stand_display);

        emit layoutChanged();

        view_display.clear();
        view_display = str;

        forming(-1, view_display[0].toLatin1());
        operation.push(item);       //Операция кладется в стек с операциями
        view_display.clear();
        emit layoutChanged();
        return;
    }
    else if(str==")" && flag_start==1 && flag_operation == 0 && count_parenthesis>0)
    {
        flag_top = 0;
        flag_drob = 0;
        flag_negative=0;
        count_parenthesis--;

        stand_display += str;
        //ptxt->setText(stand_display);

        m_data.append(stand_display);
        //view_display.append(stand_display);

        emit layoutChanged();

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
        emit layoutChanged();
        return;
    }
    else if(str == "=" && flag_start==1 && flag_operation == 0 && count_parenthesis==0)
    {
        qDebug() << "Equal";

        flag_drob=0;
        stand_display += str;
        //ptxt->setText(stand_display);

        m_data.append(stand_display);
        //view_display.append(stand_display);

        emit layoutChanged();

        view_display.clear();
        view_display = str;

        while (operation.size() != 0)  //Вызываем функцию до тех пор, пока в стеке с операциями не будет 0 элементов
        {
            if (calculate(number, operation, item) == false) //Если функция вернет "false", то прекращаем работу
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

        //ptxt->setText(stand_display+view_display);
        //plblDisplay->setText(view_display);

        //m_data.append(view_display);
        m_data.append(stand_display+view_display);
        //view_display.append(view_display);

        emit layoutChanged();

        view_display.clear();
        stand_display.clear();

        number.clear();
        operation.clear();
        view_display = "";
        stand_display = "";
        flag_top = 0;
        flag_operation = 0;
        flag_start = 0;
        flag_open = 0;
        flag_drob=0;
        flag_negative=0;
        count_parenthesis = 0;
        emit layoutChanged();
    }
}
