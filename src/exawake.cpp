#include <QtQuick>
#include <sailfishapp.h>
#include "wolmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();
    WOLModel wolModel;

    view->engine()->rootContext()->setContextProperty("wolModel", &wolModel);

    // Show the application
    view->setSource(SailfishApp::pathTo("qml/exawake.qml"));
    view->show();

    return app->exec();
}
