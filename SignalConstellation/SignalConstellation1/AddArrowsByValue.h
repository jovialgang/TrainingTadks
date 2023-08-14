#ifndef ADDARROWSBYVALUE_H
#define ADDARROWSBYVALUE_H

#include <QDialog>

namespace Ui {
class AddArrowsByValue;
}

class AddArrowsByValue : public QDialog
{
    Q_OBJECT

public:
    explicit AddArrowsByValue(QWidget *parent = nullptr);
    ~AddArrowsByValue();
    QString getValues();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddArrowsByValue *ui;
    QString valuesToArrows;
};

#endif // ADDARROWSBYVALUE_H
