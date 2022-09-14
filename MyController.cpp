#include "MyController.h"

MyController::MyController()
{
    qDebug() << "CONSTRUCTOR MyController";
}

MyController::MyController(MyModel *m_model)
{
    qDebug() << "CONSTRUCTOR MyController with parameters";
    this->m_model = m_model;
}

QString MyController::ChangeData(QString str)
{
    QString str2;
    str2 = m_model->slotButtonClicked(str);
    return str2;
}

MyController::~MyController()
{
    delete m_model;
}
