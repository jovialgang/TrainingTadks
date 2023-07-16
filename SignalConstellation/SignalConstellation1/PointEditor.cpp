#include "PointEditor.h"
#include "ui_PointEditor.h"
#include <QDebug>

PointEditor::PointEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointEditor)
{
    ui->setupUi(this);
}

PointEditor::~PointEditor()
{
    delete ui;
}

void PointEditor::setPoint(Point point)
{
    m_point = point;
    ui->lineEdit->setText(point.value);
}

Point PointEditor::getPoint() const
{
    return m_point;
}

void PointEditor::showPointEditor(const QPoint &pos, Point point) {
    setPoint(point);
    move(pos);
    show();
}

void PointEditor::on_buttonBox_accepted()
{
    m_point.value = ui->lineEdit->text();
    emit pointUpdated(m_point);
    close();
}

void PointEditor::on_buttonBox_rejected()
{
    close();
}

