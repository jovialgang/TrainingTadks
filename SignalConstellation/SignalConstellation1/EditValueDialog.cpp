#include "EditValueDialog.h"
#include "ui_EditValueDialog.h"

EditValueDialog::EditValueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditValueDialog)
{
    ui->setupUi(this);
}

EditValueDialog::~EditValueDialog()
{
    delete ui;
}

void EditValueDialog::setPointValue(const QString& value) {
    ui->lineEditValue->setText(value);
}

void EditValueDialog::setPointMaxValueSize(const int valueSize) {
    maxValueSize = valueSize;
}


void EditValueDialog::on_lineEditValue_textChanged(const QString &arg1)
{
    if (arg1.isEmpty() || arg1.contains(QRegExp("[^01]")) || arg1.length() > maxValueSize) {
        ui->OkButton->setEnabled(false);
    }
    else {
        ui->OkButton->setEnabled(true);
    }

}

void EditValueDialog::on_OkButton_clicked()
{
    QString newValue = ui->lineEditValue->text();
    emit valueChanged(newValue);
    close();
}

void EditValueDialog::on_cancelButton_clicked()
{
    close();
}


void EditValueDialog::on_EditValueDialog_rejected()
{
    emit dialogClosed();
    close();

}

