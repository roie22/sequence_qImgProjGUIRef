
#if  0
#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QtMouseMoveViewTranlated_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
#endif


#include <QApplication>
#include <QGraphicsScene>
#include "panview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(-500, -500, 1000, 1000);

    // 添加一些示例项目
    scene.addEllipse(-50, -50, 100, 100, QPen(Qt::black), QBrush(Qt::red));
    scene.addRect(100, 100, 200, 100, QPen(Qt::blue), QBrush(Qt::green));

    // 使用我们的自定义视图
    PanView view;
    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setDragMode(QGraphicsView::RubberBandDrag); // 可选：同时支持框选
    view.show();

    return app.exec();
}

