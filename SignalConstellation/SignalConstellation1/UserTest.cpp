#include "UserTest.h"
#include "ui_UserTest.h"

UserTest::UserTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserTest)
{
    ui->setupUi(this);
    emit on_LightTheme_clicked();



//    QVector<Point> points;
    std::vector<Point> points;
    int z = 0;
    for (float y = -10; y <= 10; y += 2) { // Потенциальная проблема при использовании переменных с
        for (float x = -10; x <= 10; x += 2) { // плавающей точкой в качестве счетчиков циклов (точность и округление)
            z++;
            Point point;
            point.x = qRound(x * 10); //Решение этой преблемы
            point.x /= 10;
            point.y = qRound(y * 10);
            point.y /= 10;
//            point.value = QString::number(z * 100, 2); // Проверка
            point.value = QString::number(z, 2);
            points.push_back(point);
        }
    }
    qDebug() << points.size();
    ui->label->setText(ui->label->text() + tr("Quantity of points: %1").arg(points.size()));

    ResultCode resultPoints = ui->widget->setPoints(points);


    { // Проверка
        QVector<QString> values;
        values.append(QString::number(111100));
        values.append(QString::number(1001001));
        values.append(QString::number(1000111));
        QPair<ResultCode, int> resultArrows1 = ui->widget->setArrowsByValues(values);

        values.clear();
        values.append(QString::number(1000111));
        values.append(QString::number(110100));
        values.append(QString::number(110001));
        values.append(QString::number(110000));
        QPair<ResultCode, int> resultArrows2 = ui->widget->setArrowsByValues(values);

        QString message;

        if (resultPoints == ResultCode::ErrorTooManyPoints) message += "ErrorTooManyPoints";
        if (resultPoints == ResultCode::InvalidPointValues) message += "InvalidPointValues";
        if (resultPoints == ResultCode::Success) message += "success points\n";
        if (resultArrows1.first == ResultCode::Success) message += "success Arrows1 \n";
        if (resultArrows2.first == ResultCode::Success) message += "success Arrows2 \n";
        if (resultArrows2.first == ResultCode::EndStartPointError) message += "Arrow2 EndStartPointError\n";

        ui->label->setText(message);
        ui->LightTheme->setChecked(true);


    }

}

UserTest::~UserTest()
{
    delete ui;
}



void UserTest::on_ShowPointsCoord_clicked()
{
    QString pointList;
    const QVector<Point>& points = ui->widget->getPoints();

    if (points.isEmpty()) {
        ui->textEdit->clear();
        return;
    }

    int pointCount = 0;

    for (const Point& point : points) {
        pointCount++;

        // Формирование строки с параметрами точки
        pointList += QString("Point № %1:\n").arg(pointCount);
        pointList += QString("PosX: %1, PosY: %2, Value: %3\n\n")
                         .arg(point.x)
                         .arg(point.y)
                         .arg(point.value);
    }

    // Установка текста в TextEdit
    ui->textEdit->setPlainText(pointList);
}


void UserTest::on_ShowArrowssCoord_clicked()
{
    QString connectedPointsList;
    const QVector<Point>& points = ui->widget->getConnectedPoints();

    if (points.isEmpty()) {
        ui->textEdit->clear();
        return;
    }

    int arrowCount = 0;

    const Point& startPoint = points.first();

    connectedPointsList += QString("Arrow № 1:\n");

       connectedPointsList += QString("Start: PosX: %1, PosY: %2, Value: %3\n\n")
                                      .arg(startPoint.x)
                                      .arg(startPoint.y)
                                      .arg(startPoint.value);


        for (int i = 1; i < points.size(); ++i){
        arrowCount++;
        const Point& endPoint = points.at(i);

        connectedPointsList += QString(tr("Arrow № %1, \n"))
                                              .arg(arrowCount);

        connectedPointsList += QString(tr("End: PosX: %1, PosY: %2, Value: %3\n\n"))
                                   .arg(endPoint.x)
                                   .arg(endPoint.y)
                                   .arg(endPoint.value);
   }

    ui->textEdit->setPlainText(connectedPointsList);

}


void UserTest::on_AddArrowsByValue_clicked()
{
    QVector<QString> vectorValues;
    AddArrowsByValue addArrowDialog;
    addArrowDialog.exec();
    QString values = addArrowDialog.getValues();
    vectorValues = QVector<QString>::fromList( values.split(" "));

    if (!values.isEmpty()) {
        QPair<ResultCode, int> resultArrows3 = ui->widget->setArrowsByValues(vectorValues);
        if (resultArrows3.first == ResultCode::EndStartPointError) ui->label->setText("EndStartPointError");
        if (resultArrows3.first == ResultCode::Success) ui->label->setText("success Arrows3\n");
    }

}

void UserTest::changeTheme(Theme theme)
{
    ui->widget->setTheme(theme);

    if (theme == Theme::Light)
    {
        QFile styleSheetFile(":/styles/styles/LightTheme.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        qApp->setStyleSheet(styleSheet);

    }
    else if (theme == Theme::Dark)
    {
        QFile styleSheetFile(":/styles/styles/DarkTheme.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}

void UserTest::on_DarkTheme_clicked()
{
    ui->LightTheme->setEnabled(true);
    ui->LightTheme->setChecked(false);
    changeTheme(Theme::Dark);
    ui->DarkTheme->setEnabled(false);
}


void UserTest::on_LightTheme_clicked()
{
    ui->DarkTheme->setEnabled(true);
    ui->DarkTheme->setChecked(false);
    changeTheme(Theme::Light);
    ui->LightTheme->setEnabled(false);
}

