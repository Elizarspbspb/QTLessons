#include "MyView.h"

MyView::MyView(MyController *m_controller)
{
    this->m_controller = m_controller;

    plblDisplay = new QLabel();
    plblDisplay->setFrameStyle(QFrame::Box | QFrame::Raised);  // установили стиль
    plblDisplay->setLineWidth(2);      // Толщина рамки
    plblDisplay->setMinimumSize(150, 50);

    ptxt = new QLineEdit();
    //ptxt->setStyleSheet("QLineEdit { background: rgb(0, 255, 255); selection-background-color: rgb(233, 99, 0); }");
    //QFont fnt ( "Consolas", 20, QFont::Normal);
    fnt = new QFont("Consolas", 20, QFont::Normal);
    ptxt->setFont(*fnt);

    ptopLayout = new QGridLayout;
    ptopLayout->addWidget(plblDisplay,0, 0, 1, 4);
    ptopLayout->addWidget(ptxt,1, 0, 1, 4);

    QChar aButtons[5][4] = {{ '1', '2', '3', '+'},
                            { '4', '5', '6', '-'},
                            { '7', '8', '9', '*'},
                            { '(', '0', ')', '/'},
                            {'.', '='}
                           };
    short s = 0;
    short size=4;
    for (int i = 0; i < 5; ++i)
    {
        if(i==4)
            size=2;
        for (int j =0; j < size; ++j)
            ptopLayout->addWidget(createButton(aButtons[i][j], s++), i + 2, j);
    }
    ptopLayout->addWidget(createButton("Clear", s),6, 2, 1, 2);
    setLayout(ptopLayout);
}

QPushButton* MyView::createButton(const QString& str, short s)
{
    qDebug() << "CONSTRUCTOR  createButton" << s;
    pcmd[s] = new QPushButton(str);
    pcmd[s]->setMinimumSize(40, 40);
    connect(pcmd[s], SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    return pcmd[s];

    /*pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    return pcmd;*/
}

void MyView::slotButtonClicked()
{
    str = ((QPushButton*)sender())->text();
    str = m_controller->ChangeData(str);
    ptxt->setText(str);
}

MyView::~MyView()
{
    //delete m_controller;
    delete ptxt;
    delete plblDisplay;
    delete fnt;
    for(int s=0; s<19; s++)
        delete pcmd[s];
    delete ptopLayout;
}
