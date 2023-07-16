#include "Helper.h"
#include "ui_Helper.h"

Helper::Helper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Helper)
{
    ui->setupUi(this);

    connect(ui->OKButton, &QPushButton::released, this, &Helper::OKButton_pressed);
}

Helper::~Helper()
{
    delete ui;
}

int Helper::findPointIndex(const QVector<Point>& points, const QPointF& point) {
    for (int i = 0; i < points.size(); ++i)
    {
        const Point& existingPoint = points[i];
        if (existingPoint.x == point.x() && existingPoint.y == point.y())
        {
            return i;
        }
    }
    return -1; // Возвращаем -1, если точка не найдена
}

int Helper::findPointIndexByValue(const QVector<Point>& points, const QString& value) {
    for (int i = 0; i < points.size(); ++i)
    {
        const Point& existingPoint = points[i];
        if (existingPoint.value == value)
        {
            return i;
        }
    }
    return -1; // Возвращаем -1, если точка с указанным Value не найдена
}

void Helper::buildAddedArrows(const QVector<QPointF>& arrowPoints, const QVector<Point>& points, QVector<Arrow>& arrows)
{
    // Проверка существования точек на плоскости
    for (const QPointF& point : arrowPoints) {
        bool pointExists = false;
        for (const Point& existingPoint : points) {
            if (existingPoint.x == point.x() && existingPoint.y == point.y()) {
                pointExists = true;
                break;
            }
        }

        if (!pointExists) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Точка (%1, %2) не существует на плоскости.").arg(point.x()).arg(point.y()));
            return;

        }
    }

    // Проверка наличия стрелок
    if (!arrows.isEmpty()) {
        const Arrow& lastArrow = arrows.last();
        int startPointIndex = findPointIndex(points, arrowPoints.first());
        int endPointIndex = lastArrow.getEndPointIndex();
        if (startPointIndex != -1 && endPointIndex != -1) {
            Arrow arrow;
            arrow.setStartPointIndex(endPointIndex);
            arrow.setEndPointIndex(startPointIndex);
            arrows.append(arrow);
        }
    }

    // Создание стрелок и добавление их в m_arrows
    for (int i = 0; i < arrowPoints.size() - 1; i++) {
        int startPointIndex = findPointIndex(points, arrowPoints[i]);
        int endPointIndex = findPointIndex(points, arrowPoints[i + 1]);

        // Проверка наличия уже нарисованной стрелки
        bool arrowExists = false;
        for (const Arrow& arrow : arrows) {
            if (arrow.getStartPointIndex() == startPointIndex && arrow.getEndPointIndex() == endPointIndex) {
                arrowExists = true;
                break;
            }
        }

        if (!arrowExists) {
            Arrow arrow;
            arrow.setStartPointIndex(startPointIndex);
            arrow.setEndPointIndex(endPointIndex);
            arrows.append(arrow);
        }
    }
}


void Helper::buildArrowsByValues(const QVector<QString>& values, const QVector<Point>& points, QVector<Arrow>& arrows)
{

        // Проверка существования точек с указанными значениями
        for (const QString& value : values) {
            bool pointExists = false;
            for (const Point& existingPoint : points) {
                if (existingPoint.value == value) {
                    pointExists = true;
                    break;
                }
            }



            if (!pointExists) {
                QMessageBox::warning(this, tr("Ошибка"), tr("Точка со значением %1 не существует на плоскости.").arg(value));
                return;
            }
        }

    // Проверка наличия стрелок
    if (!arrows.isEmpty()) {
        const Arrow& lastArrow = arrows.last();
        int startPointIndex = findPointIndexByValue(points, values.first());
        int endPointIndex = lastArrow.getEndPointIndex();
        if (startPointIndex != -1 && endPointIndex != -1) {
            Arrow arrow;
            arrow.setStartPointIndex(endPointIndex);
            arrow.setEndPointIndex(startPointIndex);
            arrows.append(arrow);
        }
    }


    // Создание стрелок на основе значений точек
    for (int i = 0; i < values.size() - 1; i++) {
        int startPointIndex = findPointIndexByValue(points, values[i]);
        int endPointIndex = findPointIndexByValue(points, values[i + 1]);

        Arrow arrow;
        arrow.setStartPointIndex(startPointIndex);
        arrow.setEndPointIndex(endPointIndex);
        arrows.append(arrow);
    }
}


void Helper::OKButton_pressed()
{
    close();
}

