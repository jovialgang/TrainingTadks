#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QGraphicsLineItem>
#include <QPointF>
#include <QLineF>
#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QDebug>
#include <iostream>
#include "PointItem.h"

class ArrowItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    ArrowItem(const QPointF& startPoint, const QPointF& endPoint, QGraphicsItem* parent = nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void setScale(qreal scale);

    PointItem* startPointItem;
    PointItem* endPointItem;
    int arrowCount;
    int index;


signals:
    void arrowItemDoubleClicked(int arrowIndex);


protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    QPainterPath shape() const override;


private:
    QColor originalColor;
    qreal currentScale;
    double arrowRadius;
    double loopRadius;

    double PI = 3.1415926;

};


#endif // ARROWITEM_H
