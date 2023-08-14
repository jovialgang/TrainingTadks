#include "CoordinateAxes.h"
#include <QPainter>
//#include <QtMath>

CoordinateAxes::CoordinateAxes(qreal maxX, qreal maxY, QGraphicsItem* parent)
    : QGraphicsItem(parent)
{
    ABSmaxX = maxX;
    ABSmaxY = maxY;
}

QRectF CoordinateAxes::boundingRect() const
{
    return QRectF(-ABSmaxX - (abs(ABSmaxX / 10)), -ABSmaxY - (abs(ABSmaxY / 10)), 2 * (ABSmaxX + (abs(ABSmaxX / 10))), 2 * (ABSmaxY + (abs(ABSmaxY / 10)))); // Adjust the bounding rectangle as per your requirement
}


void CoordinateAxes::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    QPen pen(QColor(0, 82, 3), 3);
    pen.setCosmetic(true);
    painter->setPen(pen);

    // Отрисовка оси X
    painter->drawLine(-ABSmaxX - (abs(ABSmaxX / 10)), 0, ABSmaxX + (abs(ABSmaxX / 10)), 0);

    // Отрисовка оси Y
    painter->drawLine(0, -ABSmaxY - (abs(ABSmaxY / 10)), 0, ABSmaxY + (abs(ABSmaxY / 10)));

    // Длина отсечек на координатной оси
    const int tickSize = 20;

    for (qreal i = -ABSmaxX; i <= ABSmaxX; i += (ABSmaxX / pointCount)) {
        painter->drawLine(i, -tickSize / 2, i, tickSize / 2);
        qreal text = (qRound(i));
        painter->setPen(Qt::red);
        if (showValue) painter->drawText(QPointF(i, -tickSize), QString::number(text / 100));
        painter->setPen(pen);


    }

    for (qreal i = - ABSmaxY; i <= ABSmaxY; i += (ABSmaxY / pointCount)){
        painter->drawLine(-tickSize / 2, i, tickSize / 2, i);
        qreal text = (qRound(i));
        painter->setPen(Qt::red);
        if (showValue) painter->drawText(QPointF(tickSize, i), QString::number(text / 100));
        painter->setPen(pen);


    }

    painter->restore();
}


void CoordinateAxes::setPointsCount(qreal count) {
    pointCount = count;
}
