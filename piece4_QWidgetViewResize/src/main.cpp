// main.cpp
#include <QApplication>
#include "zoomablewidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ZoomableWidget widget;
    widget.resize(400, 300);
    widget.setWindowTitle("Zoomable Widget");
    widget.show();

    return a.exec();
}
