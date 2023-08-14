#include "AddArrowsByValue.h"
#include "ui_AddArrowsByValue.h"

AddArrowsByValue::AddArrowsByValue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddArrowsByValue)
{
    ui->setupUi(this);
}

AddArrowsByValue::~AddArrowsByValue()
{
    delete ui;
}

QString AddArrowsByValue::getValues() {
    return valuesToArrows;
}

void AddArrowsByValue::on_buttonBox_accepted()
{
    valuesToArrows = ui->lineEdit->text();
}


void AddArrowsByValue::on_buttonBox_rejected()
{
    valuesToArrows = "";
}

