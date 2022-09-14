#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "MyModel.h"

class MyController
{
private:
    MyModel *m_model;
public:
    MyController();
    MyController(MyModel *);
    QString ChangeData(QString);
    ~MyController();
};

#endif // MYCONTROLLER_H
