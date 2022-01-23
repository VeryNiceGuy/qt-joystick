
#include "joystickPoint.h"
#include <QGuiApplication>
#include <QtQuick/QQuickView>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<JoystickPoint>("JoystickComponent", 1, 0, "JoystickPoint");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return app.exec();
}
