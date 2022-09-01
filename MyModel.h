#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractItemModel>
#include <QStack>
#include <QString>
#include <QRegularExpression>
#include <QtDebug>
#include <string.h>

struct Formulate //Описание вводимых символов
{
    char priority;  // Приоритет операции
    double value;   // Значение
};

class MyModel : public QAbstractItemModel
{
private:
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

    QStringList m_data;
    //QString m_data;

public:
    MyModel(QObject *parent = nullptr);

    // количество строчек в модели данных
    virtual int columnCount(const QModelIndex &parent) const;

    // количесвто столбцов в модели
    virtual int rowCount(const QModelIndex &parent) const;

    // Вернет интерпретацию в зависимости от роли, роль декарации или ячейки данных
    virtual QVariant data(const QModelIndex &index, int role) const;

    // Вернет индекс элемента
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;

    // Вернет родителя элемента
    virtual QModelIndex parent(const QModelIndex &index) const;

    Formulate item;

    bool calculate(QStack <Formulate>& number, QStack <Formulate>& operation, Formulate& item);
    short getRang(char);
    void forming(double, char);

    ~MyModel();

    // функции для работы с моделью данных
public slots:
    //void slotButtonClicked();
    void slotButtonClicked(QString);
};

#endif // MYMODEL_H
