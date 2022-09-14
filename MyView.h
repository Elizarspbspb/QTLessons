#ifndef MYVIEW_H
#define MYVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QtDebug>
#include <string.h>

#include "MyController.h"

class QLineEdit;
class QLabel;
class QPushButton;
class QGridLayout;
class MyView : public QWidget
{
    Q_OBJECT
private:
    QLabel* plblDisplay;
    QLineEdit* ptxt;
    QGridLayout* ptopLayout;
    QFont* fnt;
    //QPushButton* pcmd;
    QPushButton* pcmd[19];
    MyController *m_controller;

    QString str;

public:
    MyView(MyController *MyController);
    QPushButton* createButton(const QString& str, short);
    ~MyView();

public slots:
    void slotButtonClicked();

signals:
    void signalModel(QString);
};

#endif // MYVIEW_H
