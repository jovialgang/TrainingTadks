#include "AddArrowDialog.h"
#include "ui_AddArrowDialog.h"

AddArrowDialog::AddArrowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddArrowDialog)
{
    ui->setupUi(this);

    connect(ui->addArrows, &QPushButton::released, this, &AddArrowDialog::addArrowsButton_clicked);
    connect(ui->addArrows_2, &QPushButton::released, this, &AddArrowDialog::addArrows_2_released);
    connect(ui->cancelButton, &QPushButton::released, this, &AddArrowDialog::cancelButton_pressed);

}

AddArrowDialog::~AddArrowDialog()
{
    delete ui;
}

void AddArrowDialog::showArrowAdder(){

    show();
}


void AddArrowDialog::addArrowsButton_clicked()
{
    QVector<QPointF> arrowPoints;

    // Получение значений из полей ввода и добавление в вектор arrowPoints
    // Проверка и добавление значения начальной точки
    if (!ui->startXEdit1->text().isEmpty() && !ui->startYEdit1->text().isEmpty())
    {
        QPointF startPoint(ui->startXEdit1->text().toDouble(), ui->startYEdit1->text().toDouble());
        arrowPoints.append(startPoint);
    }

    // Проверка и добавление значений конечных точек
    if (!ui->endXEdit1->text().isEmpty() && !ui->endYEdit1->text().isEmpty())
    {
        QPointF endPoint1(ui->endXEdit1->text().toDouble(), ui->endYEdit1->text().toDouble());
        arrowPoints.append(endPoint1);
    }
    if (!ui->endXEdit2->text().isEmpty() && !ui->endYEdit2->text().isEmpty())
    {
        QPointF endPoint2(ui->endXEdit2->text().toDouble(), ui->endYEdit2->text().toDouble());
        arrowPoints.append(endPoint2);
    }
    if (!ui->endXEdit3->text().isEmpty() && !ui->endYEdit3->text().isEmpty())
    {
        QPointF endPoint3(ui->endXEdit3->text().toDouble(), ui->endYEdit3->text().toDouble());
        arrowPoints.append(endPoint3);
    }
    if (!ui->endXEdit4->text().isEmpty() && !ui->endYEdit4->text().isEmpty())
    {
        QPointF endPoint4(ui->endXEdit4->text().toDouble(), ui->endYEdit4->text().toDouble());
        arrowPoints.append(endPoint4);
    }

    // Передача введенных значений в основное окно
    emit arrowsAdded(arrowPoints);

    clearLineEditFields();

    close();
}



void AddArrowDialog::addArrows_2_released()
{
    QVector<QString> values;

    if (!ui->startValueEdit1->text().isEmpty()) values.append(ui->startValueEdit1->text());
    if (!ui->endValueEdit1->text().isEmpty()) values.append(ui->endValueEdit1->text());
    if (!ui->endValueEdit2->text().isEmpty()) values.append(ui->endValueEdit2->text());
    if (!ui->endValueEdit3->text().isEmpty()) values.append(ui->endValueEdit3->text());
    if (!ui->endValueEdit4->text().isEmpty()) values.append(ui->endValueEdit4->text());

    emit arrowsAddedByValue(values);
    clearLineEditFields();
    close();
}


// Очистка полей ввода
void AddArrowDialog::clearLineEditFields()
{
    ui->startXEdit1->clear();
    ui->startYEdit1->clear();

    ui->endXEdit1->clear();
    ui->endYEdit1->clear();

    ui->endXEdit2->clear();
    ui->endYEdit2->clear();

    ui->endXEdit3->clear();
    ui->endYEdit3->clear();

    ui->endXEdit4->clear();
    ui->endYEdit4->clear();

    ui->startValueEdit1->clear();
    ui->endValueEdit1->clear();
    ui->endValueEdit2->clear();
    ui->endValueEdit3->clear();
    ui->endValueEdit4->clear();
}


void AddArrowDialog::cancelButton_pressed()
{
    close();
}

