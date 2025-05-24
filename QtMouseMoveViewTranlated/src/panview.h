
#if 0
#ifndef PANVIEW_H
#define PANVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsView>

class PanView : public QGraphicsView
{
    Q_OBJECT

public:
    PanView(QWidget *parent = nullptr) : QGraphicsView(parent), m_panning(false)
    {
        setRenderHint(QPainter::Antialiasing);
        setDragMode(QGraphicsView::RubberBandDrag);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    }

protected:
    void wheelEvent(QWheelEvent *event) override
    {
        //
        const double scaleFactor = 1.15;
        if(event->angleDelta().y() > 0) {
            scale(scaleFactor, scaleFactor);
        } else {
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton &&
            (event->modifiers() & Qt::ShiftModifier)) {
            m_panning = true;
            m_panStartPos = event->pos();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (m_panning) {
            QPointF delta = mapToScene(event->pos()) - mapToScene(m_panStartPos);
            m_panStartPos = event->pos();
            centerOn(mapToScene(viewport()->rect().center()) - delta);
            event->accept();
            return;
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton && m_panning) {
            m_panning = false;
            setCursor(Qt::ArrowCursor);
            event->accept();
            return;
        }
        QGraphicsView::mouseReleaseEvent(event);
    }

private:
    bool m_panning;
    QPoint m_panStartPos;
};

#endif // PANVIEW_H
#endif


#include <QGraphicsView>
#include <QMouseEvent>
#include <QScrollBar>
#include <QApplication>

class PanView : public QGraphicsView
{
    Q_OBJECT

public:
//    PanView(QWidget *parent = nullptr)
//        : QGraphicsView(parent),
//          m_pan(false),
//          m_panStartX(0),
//          m_panStartY(0)
//    {
//        setDragMode(QGraphicsView::NoDrag); // 禁用默认拖动模式
//        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//        setRenderHint(QPainter::Antialiasing);
//    }

    //! 增加平滑化
    PanView(QWidget *parent = nullptr)
        : QGraphicsView(parent),
          m_pan(false),
          m_panStartX(0),
          m_panStartY(0)
    {
        setDragMode(QGraphicsView::NoDrag);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setRenderHint(QPainter::Antialiasing);

        setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);
    }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton || event->button() == Qt::MiddleButton) {
            // 开始拖动
            m_pan = true;
            m_panStartX = event->x();
            m_panStartY = event->y();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (m_pan) {
            // 计算移动距离
            int dx = event->x() - m_panStartX;
            int dy = event->y() - m_panStartY;

            // 移动滚动条
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - dx);
            verticalScrollBar()->setValue(verticalScrollBar()->value() - dy);

            // 更新起始位置
            m_panStartX = event->x();
            m_panStartY = event->y();
            event->accept();
            return;
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton  && m_pan) {
            // 结束拖动
            m_pan = false;
            setCursor(Qt::ArrowCursor);
            event->accept();
            return;
        }
        QGraphicsView::mouseReleaseEvent(event);
    }

    void wheelEvent(QWheelEvent *event) override
    {
        // 缩放因子
        const double scaleFactor = 1.1;

        if(event->angleDelta().y() > 0) {
            // 放大
            scale(scaleFactor, scaleFactor);
        } else {
            // 缩小
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }

//    void mousePressEvent(QMouseEvent *event) override
//    {
//        if (event->button() == Qt::LeftButton || event->button() == Qt::MiddleButton) {
//            m_pan = true;
//            m_panStartX = event->x();
//            m_panStartY = event->y();
//            setCursor(Qt::ClosedHandCursor);
//            event->accept();
//            return;
//        }
//        QGraphicsView::mousePressEvent(event);
//    }

private:
    bool m_pan;
    int m_panStartX;
    int m_panStartY;
};

