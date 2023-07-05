#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QApplication>
#include <QMessageBox>
#include "SnakeGameModel.h"

class SnakeWidget : public QWidget
{
    Q_OBJECT

public:
    SnakeWidget(QWidget *parent = nullptr);

private slots:
    void updateSnake(const QList<QPoint>& segments); // Слот обновления сегментов змейки
    void gameFinished(); // Слот завершения игры

private:
    void paintEvent(QPaintEvent *event) override; // Переопределения метода обновления виджета
    SnakeGameModel *game;
};

#endif // SNAKEWIDGET_H

