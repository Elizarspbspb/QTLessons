#include <QApplication>
#include <QtWidgets>

#include "MyFunction.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);  // объект всего приложения

    MyFunction function;

    function.setWindowTitle("MyFunction");
    function.resize(230, 200);

    function.show();

    return app.exec();
}
