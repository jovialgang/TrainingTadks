#include "ConstellationWidget.h"
#include "ui_ConstellationWidget.h"

ConstellationWidget::ConstellationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConstellationWidget)
{
    ui->setupUi(this);
}

ConstellationWidget::~ConstellationWidget()
{
    delete ui;
}



ResultCode ConstellationWidget::setPoints(QVector<Point> &points) {


    if (ui->graphicsView) {
        delete ui->graphicsView;
        ui->graphicsView = nullptr;
    }

    // Создаем новый объект PointView
    ui->graphicsView = new PointView(this); // Указываем родительский виджет (this)
    // Добавляем новый PointView на форму
    ui->verticalLayout->addWidget(ui->graphicsView);

    ui->graphicsView->setButtons(ui->spinBox, ui->undoButton, ui->redoButton, ui->deleteArrow, ui->lineEdit, ui->showValuesCheckBox);
    return ui->graphicsView->addPoints(points);


}

ResultCode ConstellationWidget::setPoints(std::vector<Point> &points) {


    if (ui->graphicsView) {
        delete ui->graphicsView;
        ui->graphicsView = nullptr;
    }

    // Создаем новый объект PointView
    ui->graphicsView = new PointView(this); // Указываем родительский виджет (this)
    // Добавляем новый PointView на форму
    ui->verticalLayout->addWidget(ui->graphicsView);

    ui->graphicsView->setButtons(ui->spinBox, ui->undoButton, ui->redoButton, ui->deleteArrow, ui->lineEdit, ui->showValuesCheckBox);
    return ui->graphicsView->addPoints(QVector<Point>(points.begin(), points.end()));

}

QPair<ResultCode, int> ConstellationWidget::setArrowsByXY(QVector<QPointF> &arrowPoints) {
    return ui->graphicsView->addArrowsByXY(arrowPoints);
}

QPair<ResultCode, int> ConstellationWidget::setArrowsByValues(QVector<QString> &arrowValues) {
    return ui->graphicsView->addArrowsByValues(arrowValues);
}

QVector<Point> ConstellationWidget::getPoints() {

    return ui->graphicsView->takePoints();
}

QVector<Point> ConstellationWidget::getConnectedPoints() {

    return ui->graphicsView->takeConnectedPoints();
}

void ConstellationWidget::setTheme(Theme color) {
    ui->graphicsView->setTheme(color);
}


