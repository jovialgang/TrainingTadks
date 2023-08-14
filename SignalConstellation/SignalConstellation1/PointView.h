#ifndef POINTVIEW_H
#define POINTVIEW_H

#include <QGraphicsView>
#include <QVector>
#include <QDebug>
#include <QSpinBox>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QtMath>
#include <QHash>
#include <QPointF>
#include <QLabel>
#include <QCheckBox>
#include "ArrowItem.h"
#include "PointItem.h"
#include "CoordinateAxes.h"
#include "ResultCode.h"
#include "Theme.h"




class PointView : public QGraphicsView {
    Q_OBJECT
public:
    PointView(QWidget* parent = nullptr);
    ResultCode addPoints(const QVector<Point>& points);
    void setButtons(QSpinBox* spinBox, QPushButton* undoButton, QPushButton* redoButton, QPushButton* deleteButton,
                    QLineEdit* lineEdit, QCheckBox* showValuesCheckBox);
    QPair<ResultCode, int> addArrowsByXY(QVector<QPointF>& coordinates);
    QPair<ResultCode, int> addArrowsByValues(QVector<QString> &values);

    QVector<Point> takePoints();
    QVector<Point> takeConnectedPoints();
    void setTheme(Theme color);

signals:
    void setLabelText(QString text);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    QSpinBox* spinBox = nullptr;
    QLineEdit* lineEdit = nullptr;
    QPushButton* undoButton = nullptr;
    QPushButton* redoButton = nullptr;
    QPushButton* deleteButton = nullptr;
    QCheckBox* showValuesCheckBox = nullptr;

    ArrowItem* selectedArrowItem = nullptr;
    PointItem* selectedPoint = nullptr;
    PointItem* lastArrowEndItem = nullptr;

    CoordinateAxes* coordinateAxes;
    QVector<PointItem*> pointItems = QVector<PointItem*>();
    QVector<ArrowItem*> arrowItems = QVector<ArrowItem*>();
    QVector<QPair<PointItem*, PointItem*>> undoVector = QVector<QPair<PointItem*, PointItem*>>();
    QHash<QPair<QPointF, QPointF>, int> arrowCountMap;

    double currentScale;
    qreal maxCurrentScale;
    QColor pointColor;
    QColor arrowColor;

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();


    void arrowAndPointHighlighter(int arrowIndex);
    void updatePiontAndArrowSize();
    void setStartScale();
    void updatePointDuplicatColors();
    void updateLineEdit();
    bool checkPointValues(const QVector<Point>& points);

    void addArrow(PointItem* startPointItem, PointItem* endPointItem);
    void deleteSelectedArrow();
    void deleteArrow(ArrowItem* arrow);



private slots:
    void spinBoxChanged(int arg1);
    void onShowValuesCheckBoxChanged(bool checked);
    void undoAction();
    void redoAction();
};

#endif // POINTVIEW_H
