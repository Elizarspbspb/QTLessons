#include "MyController.h"

MyController::MyController(QWidget* pwgt) : QWidget(pwgt)
{
    m_view = new MyView;
    m_view->setWindowTitle("MyFunction");
    m_view->resize(230, 200);
    m_view->show();

    m_model = new MyModel;

    connect(m_view, &MyView::signalView, m_model, &MyModel::slotButtonClicked);
    connect(m_model, &MyModel::signalModel, m_view, &MyView::slotButtonClicked_result);
}

MyController::~MyController()
{
    delete m_view;
    delete m_model;
}
