#include "SnakeWidget.h"


SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent)
{
    game = new SnakeGameModel(this);
    connect(game, &SnakeGameModel::snakeUpdated, this, &SnakeWidget::updateSnake); // Подключение сигнала обновления игры к слоту
    connect(game, &SnakeGameModel::gameFinished, this, &SnakeWidget::gameFinished); // Подключение сигнала о завершении игры к слоту
    game->show();
}

void SnakeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

     // Отрисовка еды
    painter.fillRect(game->food.x(), game->food.y(), SnakeGameModel::SIZE, SnakeGameModel::SIZE, Qt::red);

    // Отрисовка сегментов
    for (const auto& segment : game->snakeSegments) {
        painter.fillRect(segment.x(), segment.y(), SnakeGameModel::SIZE, SnakeGameModel::SIZE, Qt::green);
    }
}

void SnakeWidget::updateSnake(const QList<QPoint>& segments)
{
    game->snakeSegments = segments;
    update(); // Обновление виджета
}

void SnakeWidget::gameFinished()
{
    QMessageBox::information(this, "Game Over", "Вы проиграли! Игра завершена."); // Вывод сообщения о проигрыше
    QApplication::quit(); // Завершение приложения
}
