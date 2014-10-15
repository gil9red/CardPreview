#include <QApplication>
#include "Window.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window * w = new Window();
    w->resize(900, 500);
    w->show();

    return app.exec();
}
