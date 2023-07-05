#ifndef SNAKEGAMEMODEL_H
#define SNAKEGAMEMODEL_H

#include <QWidget>
#include <QTimer>
#include <QRandomGenerator>
#include "SnakeController.h"

class SnakeGameModel : public QWidget
{
    Q_OBJECT

public:
    SnakeGameModel(QWidget *parent = nullptr);
    static const int SIZE = 20; // Размер еды и сегмента змейки
    QPoint food;
    QList<QPoint> snakeSegments;

signals:
    void snakeUpdated(const QList<QPoint>& segments); // Сигнал об обновлении игры
    void gameFinished(); // Сигнал о завершении игры

private slots:
    void moveSnake(); // Слот движения змейки
    void changeDirection(int direction); // Слот изменения направления движения змейки

private:
    void generateFood(); // Генерация новой еды
    int currentDirection = 1; // Текущее направление движения змейки
    int snakeSize = 20; // Начальная дляна змейки
    QTimer *timer;
    SnakeController controller; // Контроллер
};

#endif // SNAKEGAMEMODEL_H
