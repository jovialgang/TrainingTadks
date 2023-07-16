#ifndef HELPER_H
#define HELPER_H

#include <QDialog>
#include "point.h"
#include "Arrow.h"
#include "AddArrowDialog.h"

namespace Ui {
class Helper;
}

class Helper : public QDialog
{
    Q_OBJECT

public:
    Helper(QWidget *parent = nullptr);
    ~Helper();

    void buildAddedArrows(const QVector<QPointF>& arrowPoints, const QVector<Point>& points, QVector<Arrow>& arrows);
    void buildArrowsByValues(const QVector<QString>& values, const QVector<Point>& points, QVector<Arrow>& arrows);

private slots:
    void OKButton_pressed();

private:
    Ui::Helper *ui;

    int findPointIndex(const QVector<Point>& points, const QPointF& point);
    int findPointIndexByValue(const QVector<Point>& points, const QString& value);
};

#endif // HELPER_H
