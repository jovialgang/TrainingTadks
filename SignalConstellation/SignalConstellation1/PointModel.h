#ifndef POINTMODEL_H
#define POINTMODEL_H

#include <QVector>
#include <QString>
#include <QSet>
#include <QPainter>
#include <point.h>

class PointModel {
public:
    PointModel();

    QVector<Point> getPoints();
    void updatePoint(Point point, int m_selectedPointIndex);
    QSet<int> findDuplicates() const;
    void setHighlighted(int pointIndex, bool highlighted);
    void draw(QPainter& painter) const;

private:
    void addPoint(Point &point);
    QVector<Point> m_points;
};

#endif // POINTMODEL_H
