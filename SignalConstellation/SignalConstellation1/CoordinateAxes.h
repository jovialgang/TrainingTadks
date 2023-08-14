#ifndef COORDINATEAXES_H
#define COORDINATEAXES_H

#include <QGraphicsItem>
#include <QObject>
#include <QDebug>

class CoordinateAxes : public QGraphicsItem
{
public:
    explicit CoordinateAxes(qreal maxX, qreal maxY, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void setPointsCount(qreal count);
    bool showValue = false;

private:
    qreal ABSmaxX;
    qreal ABSmaxY;
    qreal pointCount;
};

#endif // COORDINATEAXES_H
