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

//#include <QListView>
//#include <QTableView>

class QPushButton;
class QLineEdit;
class QLabel;
class MyView : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* ptxt;
    QLabel* plblDisplay;
    QLabel* plbResult;
    QPushButton* pcmd;

    QString stand_display;
    QString view_display;
    QString str;

public:
    MyView(QWidget* pwgt = 0);
    QPushButton* createButton(const QString& str);
    ~MyView();

public slots:
    void slotButtonClicked();
    void slotButtonClicked_result(QString);

signals:
    void signalView(QString);
};

#endif // MYVIEW_H
