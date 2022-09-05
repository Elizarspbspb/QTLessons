#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include <QWidget>
#include "MyView.h"
#include "MyModel.h"

class MyController : public QWidget
{
    Q_OBJECT
private:
    MyView *m_view;
    MyModel *m_model;
public:
    MyController(QWidget* pwgt = 0);
    ~MyController();
};

#endif // MYCONTROLLER_H
