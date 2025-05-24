// main.cpp
#include <QApplication>
#include "pannablewidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    PannableWidget widget;
    widget.resize(400, 300);
    widget.show();
    
    return a.exec();
}