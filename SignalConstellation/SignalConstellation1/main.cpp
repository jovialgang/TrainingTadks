#include <QApplication>
#include "PointModel.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PointModel model;
    MainWindow widget;
    widget.setModel(&model);
    widget.show();

    return app.exec();
}
