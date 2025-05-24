#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class PannableWidget : public QWidget {
    Q_OBJECT
public:
    explicit PannableWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setMouseTracking(true); // 启用鼠标跟踪
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        
        // 应用平移变换
        painter.translate(m_offset);
        
        // 绘制内容（示例：一个矩形）
        painter.fillRect(50, 50, 100, 100, Qt::blue);
        painter.drawText(60, 100, "Drag me with mouse");
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_lastPos = event->pos(); // 记录起始位置
            m_isDragging = true;
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (m_isDragging) {
            // 计算偏移量
            QPoint delta = event->pos() - m_lastPos;
            m_offset += delta;
            m_lastPos = event->pos();
            
            update(); // 触发重绘
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_isDragging = false;
        }
    }

private:
    QPoint m_offset;     // 累计平移偏移量
    QPoint m_lastPos;    // 鼠标上次位置
    bool m_isDragging = false;
};