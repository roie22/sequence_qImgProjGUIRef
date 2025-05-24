#include <QWidget>
#include <QWheelEvent>
#include <QPainter>
#include <QMouseEvent>

class ZoomableWidget : public QWidget {
    Q_OBJECT
public:
    explicit ZoomableWidget(QWidget *parent = nullptr)
        : QWidget(parent), m_scale(1.0), m_offset(0, 0) {
        setMouseTracking(true);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 应用变换：先平移后缩放
        painter.translate(m_offset);
        painter.scale(m_scale, m_scale);

        // 绘制示例内容（一个矩形和文字）
        painter.fillRect(QRect(50, 50, 100, 100), Qt::blue);
        painter.setPen(Qt::white);
        painter.drawText(QRect(50, 50, 100, 100), Qt::AlignCenter, "Zoomable");
    }

    void wheelEvent(QWheelEvent *event) override {
        // 获取鼠标位置（视口坐标）
        QPointF mousePos = event->pos();

        // 计算缩放前的目标点（世界坐标）
        QPointF targetBeforeScale = (mousePos - m_offset) / m_scale;

        // 调整缩放比例（限制范围）
        float scaleFactor = event->angleDelta().y() > 0 ? 1.1 : 0.9;
        m_scale *= scaleFactor;
        m_scale = qMax(0.1f, qMin(m_scale, 10.0f)); // 限制缩放范围[0.1, 10]

        // 计算缩放后的偏移量，保持目标点位置不变
        QPointF targetAfterScale = (mousePos - m_offset) / m_scale;
        m_offset += (targetAfterScale - targetBeforeScale) * m_scale;

        update();
    }

    // 可选：添加平移功能（见下文扩展）
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_lastPos = event->pos();
            m_isDragging = true;
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (m_isDragging) {
            QPointF delta = event->pos() - m_lastPos;
            m_offset += delta;
            m_lastPos = event->pos();
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_isDragging = false;
        }
    }

private:
    float m_scale;          // 当前缩放比例
    QPointF m_offset;        // 平移偏移量
    QPointF m_lastPos;       // 鼠标上次位置（用于平移）
    bool m_isDragging = false;
};
