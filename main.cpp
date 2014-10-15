#include <QApplication>
#include "Window.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window * w = new Window();
    w->show();

    return app.exec();
}
