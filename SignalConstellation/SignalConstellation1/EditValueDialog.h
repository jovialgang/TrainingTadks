#ifndef EDITVALUEDIALOG_H
#define EDITVALUEDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class EditValueDialog;
}

class EditValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditValueDialog(QWidget *parent = nullptr);
    ~EditValueDialog();

    void setPointValue(const QString& value);
    void setPointMaxValueSize(const int valueSize);
    Ui::EditValueDialog *ui;

signals:
    void valueChanged(const QString value);
    void dialogClosed();

private slots:
    void on_lineEditValue_textChanged(const QString &arg1);

    void on_OkButton_clicked();

    void on_cancelButton_clicked();

    void on_EditValueDialog_rejected();

private:
    int maxValueSize;
};

#endif // EDITVALUEDIALOG_H
