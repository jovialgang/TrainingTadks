#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include <QObject>
#include <QKeyEvent>
#include <QWidget>


class SnakeController : public QObject
{
    Q_OBJECT

public:
    SnakeController(QObject *parent = nullptr);
    void setTarget(QWidget *target); // Установка цели для контроллера

signals:
    int directionChanged(int direction); // Сигнал о изменении направления змейки

private:
    bool eventFilter(QObject *obj, QEvent *event) override; // Переопределение обработчика событий
    void handleKeyPress(QKeyEvent *event); // Обработка нажатия клавиши

    QWidget *Target = nullptr; // Целевой виджет
};

#endif // SNAKECONTROLLER_H
