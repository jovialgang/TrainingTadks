#ifndef CONSTELLATIONWIDGET_H
#define CONSTELLATIONWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QVector>
#include <QPointF>
#include <QString>
#include <vector>
#include "ResultCode.h"
#include "point.h"
#include "Theme.h"



namespace Ui {
class ConstellationWidget;
}

class ConstellationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConstellationWidget(QWidget *parent = nullptr);
    ~ConstellationWidget();

    ResultCode setPoints(QVector<Point> &points);
    ResultCode setPoints(std::vector<Point> &points);
    QPair<ResultCode, int> setArrowsByXY(QVector<QPointF> &arrowPoints);
    QPair<ResultCode, int> setArrowsByValues(QVector<QString> &arrowValues);
    QVector<Point> getPoints();
    QVector<Point> getConnectedPoints();
    void setTheme(Theme color);

private:
    Ui::ConstellationWidget *ui;
};

#endif // CONSTELLATIONWIDGET_H
