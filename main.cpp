#include <QApplication>
#include <QtWidgets>

#include "MyController.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);  // объект всего приложения

    MyController function;

    return app.exec();
}
