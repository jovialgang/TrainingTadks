#ifndef POINTITEM_H
#define POINTITEM_H

#include <QGraphicsObject>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QToolTip>
#include <QDebug>
#include "point.h"
#include "EditValueDialog.h"
#include "ui_EditValueDialog.h"


class PointItem : public QGraphicsObject {
    Q_OBJECT
public:
    PointItem(const Point& point, QGraphicsItem* parent = nullptr);
    void setDuplicate(bool duplicate);
    void setPointSize(qreal size);
    void setPointColor(const QColor& color);

    qreal pointSize = 10; // Размер точки
    Point pointData;
    int index;
    int maxValueSize;
    bool showValue = false;
    bool selected = false;


signals:
    void pointItemDoubleClicked();


protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QColor pointColor;
    QColor originalColor;


private slots:
    void getNewValue(const QString value);
    void editDialogClosed();

};

#endif // POINTITEM_H
