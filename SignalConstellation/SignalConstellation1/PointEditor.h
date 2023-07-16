#ifndef POINTEDITOR_H
#define POINTEDITOR_H

#include <QDialog>
#include "point.h"
#include "PointModel.h"

namespace Ui {
class PointEditor;
}

class PointEditor : public QDialog
{
    Q_OBJECT

public:
    explicit PointEditor(QWidget *parent = nullptr);
    ~PointEditor();

    void setPoint(Point point);
    Point getPoint() const;


    PointModel *m_model;


signals:
    void pointUpdated(Point point);

public slots:
    void showPointEditor(const QPoint &pos, Point point);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PointEditor *ui;
    Point m_point;
};

#endif // POINTEDITOR_H
