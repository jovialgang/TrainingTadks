#ifndef ARROW_H
#define ARROW_H

#include <QPainterPath>
#include <QPainter>
#include <QMessageBox>
#include "point.h"

class Arrow {


public:

    Arrow();
    void setStartPointIndex(int index);
    int getStartPointIndex() const;
    void setEndPointIndex(int index);
    int getEndPointIndex() const;
    void setHighlighted(bool highlighted);
    bool isHighlighted() const;

    bool contains(const QPointF& point, const QVector<Point>& points, double scale) const;
    void draw(QPainter& painter, const QVector<Point>& points) const;


private:
    int m_startPointIndex;
    int m_endPointIndex;
    bool m_highlighted;
    QPainterPath m_path;
};

#endif // ARROW_H
