#include "Arrow.h"

Arrow::Arrow() : m_highlighted(false) {


}

void Arrow::setStartPointIndex(int index) {
    m_startPointIndex = index;
}

int Arrow::getStartPointIndex() const {
    return m_startPointIndex;
}

void Arrow::setEndPointIndex(int index) {
    m_endPointIndex = index;
}

int Arrow::getEndPointIndex() const {
    return m_endPointIndex;
}


void Arrow::setHighlighted(bool highlighted) {
    m_highlighted = highlighted;
}

bool Arrow::isHighlighted() const {
    return m_highlighted;
}


void Arrow::draw(QPainter& painter, const QVector<Point>& points) const {
    if (m_startPointIndex >= points.size() || m_endPointIndex >= points.size()) {
        return;
    }

    const Point& start = points[m_startPointIndex];
    const Point& end = points[m_endPointIndex];

    // Голова стрелки
    QPointF arrowHeadPoints[3];
    double angle = atan2(end.y - start.y, end.x - start.x) - PI;
    arrowHeadPoints[0] = QPointF(end.x + 10 * cos(angle + PI / 6), end.y + 10 * sin(angle + PI / 6));
    arrowHeadPoints[1] = QPointF(end.x, end.y);
    arrowHeadPoints[2] = QPointF(end.x + 10 * cos(angle - PI / 6), end.y + 10 * sin(angle - PI / 6));

    if (getStartPointIndex() != getEndPointIndex() && isHighlighted()) {
        // Рисуем выделенную стрелку
        painter.setPen(Qt::red);
        painter.drawLine(start.x, start.y, end.x, end.y);
        painter.setBrush(Qt::red);
        painter.drawPolygon(arrowHeadPoints, 3);
    } else if (getStartPointIndex() == getEndPointIndex()) {
        // Рисуем петлю, если стрелка выходит и приходит в одну и ту же точку
        qreal loopRadius = 30;
        QPointF loopCenter(start.x, start.y - loopRadius);
        if (isHighlighted()) {
            painter.setPen(Qt::red);
            painter.setBrush(Qt::red);
            int spanAngle = 16 * 360;  // Полный окружностной диапазон
            painter.drawArc(loopCenter.x() - loopRadius, loopCenter.y() - loopRadius, loopRadius * 2, loopRadius * 2, 0, spanAngle);
        } else {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::black);
            int spanAngle = 16 * 360;
            painter.drawArc(loopCenter.x() - loopRadius, loopCenter.y() - loopRadius, loopRadius * 2, loopRadius * 2, 0, spanAngle);
        }
        painter.drawPolygon(arrowHeadPoints, 3);
    }else {
        painter.setPen(Qt::black);
        painter.drawLine(start.x, start.y, end.x, end.y);
        painter.setBrush(Qt::black);
        painter.drawPolygon(arrowHeadPoints, 3);
    }
}

bool Arrow::contains(const QPointF& point, const QVector<Point>& points, double scale) const {
    if (m_startPointIndex >= points.size() || m_endPointIndex >= points.size()) {
        return false;
    }

    const Point& start = points[m_startPointIndex];
    const Point& end = points[m_endPointIndex];

    // Определяем контур петли
    QPainterPath loopPath;
    qreal loopRadius = 30 * scale;
    QPointF loopCenter(start.x, start.y - loopRadius);
    loopPath.addEllipse(loopCenter, loopRadius, loopRadius);



    QPointF parallelPoints[4];
    double angle = atan2(end.y - start.y, end.x - start.x) - PI / 2.0;
    double offset = 10.0; // Оффсет от стрелки

    parallelPoints[0] = QPointF(start.x + offset * cos(angle), start.y + offset * sin(angle));
    parallelPoints[1] = QPointF(end.x + offset * cos(angle), end.y + offset * sin(angle));
    parallelPoints[2] = QPointF(end.x - offset * cos(angle), end.y - offset * sin(angle));
    parallelPoints[3] = QPointF(start.x - offset * cos(angle), start.y - offset * sin(angle));

    // Применяем обратное преобразование координат
    QTransform transform;
    transform.scale(scale, scale);
    QTransform invTransform = transform.inverted();
    QPointF transformedPoint = invTransform.map(point);

    if (m_startPointIndex == m_endPointIndex) {
        if (loopPath.contains(transformedPoint)) {
            return true;
        }
    } else {
        QPolygonF arrowPolygon;
        arrowPolygon << parallelPoints[0] << parallelPoints[1] << parallelPoints[2] << parallelPoints[3];

        if (arrowPolygon.containsPoint(transformedPoint, Qt::OddEvenFill)) {
            return true;
        }
    }

    return false;
}


