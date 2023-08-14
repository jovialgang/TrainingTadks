#include "ArrowItem.h"
#include <QtCore/qobject.h>
#include <QPainter>
#include <cmath>
//#include <QtMath>

ArrowItem::ArrowItem(const QPointF& startPoint, const QPointF& endPoint, QGraphicsItem* parent)
    : QGraphicsLineItem(parent), arrowCount(1)
{
    setLine(QLineF(startPoint, endPoint));
    setPen(QPen(Qt::black, 1));
    originalColor = Qt::black;
}


void ArrowItem::setScale(qreal scale){
    currentScale = scale;
}

void ArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    // Проверка на совпадение точки старта и точки конца стрелки (петля)
    if (line().p1() == line().p2()) {

        double arrowSize = 10.0 / currentScale;
        double penWidth = 1.0 / currentScale;
        painter->setPen(QPen(pen().color(), penWidth));

        // Увеличиваем радиус в зависимости от количесва стрелок на данной позиции
        loopRadius = ((arrowCount * 5) + 10) / currentScale;
        const double loopAngle = - PI / 2;


        QPointF loopCenter = line().p1() + QPointF(loopRadius * std::cos(loopAngle), loopRadius * std::sin(loopAngle));

        QPainterPath loopPath;
        loopPath.arcMoveTo(loopCenter.x() - loopRadius, loopCenter.y() - loopRadius, 2 * loopRadius, 2 * loopRadius, 0);
        loopPath.arcTo(loopCenter.x() - loopRadius, loopCenter.y() - loopRadius, 2 * loopRadius, 2 * loopRadius, 0, 360);

        painter->setBrush(Qt::transparent);
        painter->drawPath(loopPath);

        double angle = std::atan2(0, line().p2().x() - loopCenter.x());

        QPointF arrowP1 = line().p2() - QPointF(arrowSize * std::cos(angle + PI / 6),
                                                arrowSize * std::sin(angle + PI / 6));
        QPointF arrowP2 = line().p2() - QPointF(arrowSize * std::cos(angle - PI / 6),
                                                arrowSize * std::sin(angle - PI / 6));

        QPolygonF arrowHead;
        arrowHead << line().p2() << arrowP1 << arrowP2;
        painter->setBrush(pen().color());
        painter->drawPolygon(arrowHead);


    } else { // Если стрелка не петля:
            if (arrowCount == 1) { // На данной позиции одна срелка - рисуем простую линию
            double arrowSize = 10.0 / currentScale;
            double penWidth = 1.0 / currentScale;
            painter->setPen(QPen(pen().color(), penWidth));

            painter->setBrush(pen().color());
            painter->drawLine(line());

            double angle = std::atan2(line().dy(), line().dx());

            QPointF arrowP1 = line().p2() - QPointF(arrowSize * std::cos(angle + PI / 6),
                                                    arrowSize * std::sin(angle + PI / 6));
            QPointF arrowP2 = line().p2() - QPointF(arrowSize * std::cos(angle - PI / 6),
                                                    arrowSize * std::sin(angle - PI / 6));

            QPolygonF arrowHead;
            arrowHead << line().p2() << arrowP1 << arrowP2;
            painter->drawPolygon(arrowHead);

        } else if (arrowCount > 1){ // На данной позиции уже есть стрелки значит ризуем закруглённую стрелку

            double arrowSize = 10.0 / currentScale;
            double penWidth = 1.0 / currentScale;
            painter->setPen(QPen(pen().color(), penWidth));

            double angle = std::atan2(line().dy(), line().dx());

            arrowRadius = arrowCount * 10; // радиус закругления

            QPointF arrowP1 = line().p2() - QPointF(arrowSize * std::cos(angle + PI / 6),
                                                    arrowSize * std::sin(angle + PI / 6));
            QPointF arrowP2 = line().p2() - QPointF(arrowSize * std::cos(angle - PI / 6),
                                                    arrowSize * std::sin(angle - PI / 6));

            QPointF middlePoint = (line().p1() + line().p2()) * 0.5;
            QPointF controlPoint = middlePoint + QPointF(arrowRadius * std::cos(angle - PI / 2),
                                                         arrowRadius * std::sin(angle - PI / 2));

            QPainterPath path;
            path.moveTo(line().p1());
            path.quadTo(controlPoint, line().p2()); // Отрисовываем закруглённую стрелку с помощью кривой Безье

            painter->setBrush(Qt::transparent);
            painter->drawPath(path);

            QPolygonF arrowHead;
            painter->setBrush(pen().color());
            arrowHead << line().p2() << arrowP1 << arrowP2;
            painter->drawPolygon(arrowHead);
        }
    }

}


// Обработчик двойного нажатия на стрелку
void ArrowItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) return;
    emit arrowItemDoubleClicked(index);
    QGraphicsLineItem::mouseDoubleClickEvent(event);
}


// Переопределение метода, отвечающего за определение области, реагирующей на нажатия
// Области определяются почти так же как и рисовались + обводка пути с помощью QPainterPathStroker
QPainterPath ArrowItem::shape() const {
    QPainterPath path;

    if (line().p1() == line().p2()) {
        double loopRadius = ((arrowCount * 5) + 10) / currentScale;
        const double loopAngle = - PI / 2;

        QPointF loopCenter = line().p1() + QPointF(loopRadius * std::cos(loopAngle), loopRadius * std::sin(loopAngle));

        QPainterPath loopPath;
        loopPath.arcMoveTo(loopCenter.x() - loopRadius, loopCenter.y() - loopRadius, 2 * loopRadius, 2 * loopRadius, 0);
        loopPath.arcTo(loopCenter.x() - loopRadius, loopCenter.y() - loopRadius, 2 * loopRadius, 2 * loopRadius, 0, 360);
        path = loopPath;
    } else if (arrowCount > 1){
        double angle = std::atan2(line().dy(), line().dx());

        QPointF middlePoint = (line().p1() + line().p2()) * 0.5;
        QPointF controlPoint = middlePoint + QPointF(arrowRadius * std::cos(angle - PI / 2),
                                                     arrowRadius * std::sin(angle - PI / 2));

        QPainterPathStroker stroker;
        stroker.setWidth(10 / currentScale);
        path.moveTo(line().p1());
        path.quadTo(controlPoint, line().p2());
        path = stroker.createStroke(path);
    } else if (arrowCount == 1) {
        QPainterPathStroker stroker;
        stroker.setWidth(20 / currentScale);
        path.moveTo(line().p1());
        QPointF controlPoint = (line().p1() + line().p2()) * 0.5;
        path.quadTo(controlPoint, line().p2());
        path = stroker.createStroke(path);
    }
    return path;
}




