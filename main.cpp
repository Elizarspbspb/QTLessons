#include <QApplication>
#include "MyController.h"
#include "MyView.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);  // объект всего приложения

    MyModel *model;
    model = new MyModel;

    MyController controller(model);

    MyView view(&controller);
    view.setWindowTitle("MyCalculator");
    view.resize(230, 200);
    view.show();

    return app.exec();
}
