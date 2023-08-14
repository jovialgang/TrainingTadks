#include "PointItem.h"
#include <QPainter>
#include <QToolTip>


PointItem::PointItem(const Point& point, QGraphicsItem* parent) : QGraphicsObject(parent), pointData(point) {
    pointColor = Qt::black;


}

QRectF PointItem::boundingRect() const {
    return QRectF(-pointSize / 2, -pointSize / 2, pointSize, pointSize);
}



void PointItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (showValue) {
        painter->drawText(QPointF(-30, -10), pointData.value);
    }

    qreal haloSize = pointSize * 1.4;

    if (selected) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0, 0, 0, 100));
        painter->drawEllipse(QPointF(2, 2), (haloSize / 2) * 1.3, (haloSize / 2) * 1.3);

        painter->setPen(Qt::black);
        painter->setBrush(pointColor);
        painter->drawEllipse(QPointF(0, 0), (pointSize / 2) * 1.3, (pointSize / 2) * 1.3);
    } else {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0, 0, 0, 100));
        painter->drawEllipse(QPointF(2, 2), haloSize / 2, haloSize / 2);

        painter->setPen(Qt::black);
        painter->setBrush(pointColor);
        painter->drawEllipse(QPointF(0, 0), pointSize / 2, pointSize / 2);
    }

}

void PointItem::setPointSize(qreal size) {
    pointSize = size;
}

void PointItem::setPointColor(const QColor& color) {
    pointColor = color;
    update();
}

// Обработчик тажатия на точку
void PointItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    // При двойном щелчке на точке создаем диалог для изменения значения
    if (event->button() != Qt::LeftButton) return;
    pointSize *= 1.4;
    EditValueDialog* dialog = new EditValueDialog();
    connect(dialog, &EditValueDialog::valueChanged, this, &PointItem::getNewValue);
    connect(dialog, &EditValueDialog::dialogClosed, this, &PointItem::editDialogClosed);
    dialog->setPointMaxValueSize(maxValueSize);
    dialog->setPointValue(pointData.value);
    dialog->exec();
    event->setAccepted(true);
}


void PointItem::getNewValue(const QString value) {
    pointData.value = value;
    emit pointItemDoubleClicked();
    update();

}

void PointItem::editDialogClosed() {
    pointSize /= 1.4;
    update();
}
