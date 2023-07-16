#ifndef ADDARROWDIALOG_H
#define ADDARROWDIALOG_H

#include <QDialog>

namespace Ui {
class AddArrowDialog;
}

class AddArrowDialog : public QDialog
{
    Q_OBJECT

public:
    AddArrowDialog(QWidget *parent = nullptr);
    ~AddArrowDialog();

public:
    void showArrowAdder();

signals:
    void arrowsAdded(QVector<QPointF> arrowPoints);
    void arrowsAddedByValue(const QVector<QString>& values);

private slots:
    void addArrows_2_released();
    void cancelButton_pressed();
    void addArrowsButton_clicked();

private:
    Ui::AddArrowDialog *ui;
    void clearLineEditFields();
};

#endif // ADDARROWDIALOG_H
