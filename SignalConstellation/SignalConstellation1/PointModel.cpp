#include "PointModel.h"
#include <QSet>

PointModel::PointModel() {

        // Инициализация точек
    int z = 0;
    for (int y = 100; y < 500; y += 100) {
        for (int x = 100; x < 600; x += 100) {
            z++;
            Point point;
            point.x = x;
            point.y = y;
            point.value = QString::number(x + y + z);
            addPoint(point);
        }
    }

}

// Добавление точек и проверка мксимального количества точек
void PointModel::addPoint(Point &point){
    if (m_points.size() < 10000){
        m_points.push_back(point);
    }
}


// Отрисовка точек
void PointModel::draw(QPainter& painter) const {

    // Сначала рисуем точки
    for (int i = 0; i < m_points.size(); ++i) {
        const Point& point = m_points.at(i);

        // Определяем цвет точки
        if (findDuplicates().contains(i)) {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::red); // Используем красный цвет для повторяющихся точек
        } else if (point.highlighted) {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::yellow); // Используем желтый цвет для выделенных точек
        } else {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::green); // Используем зеленый цвет для остальных точек
        }

        painter.drawEllipse(point.x, point.y, 10, 10);
    }
}

QVector<Point> PointModel::getPoints() {
    return m_points;
}

void PointModel::updatePoint(Point point, int m_selectedPointIndex)
{
    m_points[m_selectedPointIndex].value = point.value;
}

void PointModel::setHighlighted(int pointIndex, bool highlighted)
{
    m_points[pointIndex].highlighted = highlighted;
}

// Поиск дубликатов точек (дубликаты Value)
QSet<int> PointModel::findDuplicates() const
{
    QSet<int> indexes;
    for (int i = 0; i < m_points.size(); i++) {
        for (int j = i+1; j < m_points.size(); j++) {
            if (m_points[i].value == m_points[j].value) {
                indexes.insert(i);
                indexes.insert(j);
            }
        }
    }
    return indexes;
}

