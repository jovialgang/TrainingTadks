#ifndef USERTEST_H
#define USERTEST_H

#include <QWidget>
#include <QWidget>
#include <QtWidgets>
#include <QVector>
#include <QPointF>
#include <QString>
#include <QApplication>
#include <QPalette>
#include <vector>
#include "ResultCode.h"
#include "AddArrowsByValue.h"
#include "Theme.h"


namespace Ui {
class UserTest;
}

class UserTest : public QWidget
{
    Q_OBJECT

public:
    explicit UserTest(QWidget *parent = nullptr);
    ~UserTest();

private slots:
    void on_ShowPointsCoord_clicked();

    void on_ShowArrowssCoord_clicked();

    void on_AddArrowsByValue_clicked();

    void on_DarkTheme_clicked();

    void on_LightTheme_clicked();

private:
    Ui::UserTest *ui;
    void changeTheme(Theme theme);

};

#endif // USERTEST_H
