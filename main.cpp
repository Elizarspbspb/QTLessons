#include <QApplication>
#include <QtWidgets>

//#include "MyFunction.h"
#include "MyView.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);  // объект всего приложения

    //MyFunction function;
    MyView function;

    function.setWindowTitle("MyFunction");
    function.resize(230, 200);

    function.show();

    return app.exec();
}
