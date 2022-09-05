#include "MyView.h"

MyView::MyView(QWidget* pwgt) : QWidget(pwgt)
{
    plblDisplay = new QLabel();
    plblDisplay->setFrameStyle(QFrame::Box | QFrame::Raised);  // установили стиль
    plblDisplay->setLineWidth(2);      // Толщина рамки
    plblDisplay->setMinimumSize(150, 50);

    ptxt = new QLineEdit();
    //ptxt->setStyleSheet("QLineEdit { background: rgb(0, 255, 255); selection-background-color: rgb(233, 99, 0); }");
    QFont fnt ( "Consolas", 20, QFont::Normal);
    ptxt->setFont(fnt);

    QChar aButtons[5][4] = {{ '1', '2', '3', '+'},
                            { '4', '5', '6', '-'},
                            { '7', '8', '9', '*'},
                            { '(', '0', ')', '/'},
                            {'.', '='}
                           };

    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(plblDisplay,0, 0, 1, 4);
    ptopLayout->addWidget(ptxt,1, 0, 1, 4);

    short s=4;
    for (int i = 0; i < 5; ++i)
    {
        for (int j =0; j < s; ++j)
            ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
    }
    ptopLayout->addWidget(createButton("Clear"),6, 2, 1, 2);
    qDebug() << "CONSTRUCTOR";
    setLayout(ptopLayout);
}

QPushButton* MyView::createButton(const QString& str)
{
    pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;
}

void MyView::slotButtonClicked()
{
    str = ((QPushButton*)sender())->text();
    emit signalView(str);
}

void MyView::slotButtonClicked_result(QString str)
{
    if(str == "Clear")
        ptxt->clear();
    else
        ptxt->setText(str);
}

MyView::~MyView()
{
    delete ptxt;
    delete plblDisplay;
    delete plbResult;
    delete pcmd;
    view_display.clear();
    stand_display.clear();
    str.clear();
}
