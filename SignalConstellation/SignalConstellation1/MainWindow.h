#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QVector>
#include <QMouseEvent>
#include <QSpinBox>
#include "PointEditor.h"
#include "AddArrowDialog.h"
#include "PointModel.h"
#include "Helper.h"
#include "Arrow.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {

        Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setModel(PointModel *PointModel);
    int m_currentPointIndex;
    int m_selectedPointIndex = -1;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;



private:
    PointModel *m_PointModel;
    Ui::MainWindow *ui;
    PointEditor *m_pointEditor;
    AddArrowDialog *m_addArrow;
    Helper *m_helper;
    int pointSize = 10;
    double m_scale = 1.0;
    QSet<int> m_duplicateIndices;
    QVector<Arrow> m_arrows;
    int m_selectedArrowIndex = -1;

    QVector<Arrow> m_undoArrows = QVector<Arrow>();  // Вектор для хранения удаленных стрелок
    QVector<Arrow> m_redoArrows = QVector<Arrow>();

    void drawArrows(QPainter& painter, const QVector<Point>& points) const;




private slots:
    void updatePointValue(Point point);

    void highlightSelectedArrow();

    void spinBox_valueChanged(int arg1);

    void undoAction();
    void redoAction();

    void updatePointList();
    void updateConnectedPointsList();

    void deleteArrow();
    void buildAddedArrows(const QVector<QPointF>& arrowPoints);
    void buildArrowsByValues(const QVector<QString>& values);

    void helpButton_pressed();
};

#endif // _MAINWINDOW_H
