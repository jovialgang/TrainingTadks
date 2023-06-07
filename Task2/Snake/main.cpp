#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QMessageBox>

class SnakeGame : public QWidget
{
public:
    SnakeGame(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedSize(500, 700);
        direction = Direction::Left;

        // Задаем начальное положение головы и хвоста змейки
        int startX = width() / 2;
        int startY = height() / 2;

        for (int i = 0; i < snakeSize; ++i) {
            snakeSegments.append(QPoint(startX, startY - i * SIZE));
        }

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SnakeGame::moveSnake);
        timer->start(100);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);

        for (const auto& segment : snakeSegments) {
            painter.fillRect(segment.x(), segment.y(), SIZE, SIZE, Qt::green);
        }
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        switch (event->key()) {
        case Qt::Key_Up:
            if (direction != Direction::Down) // Запрещаем поворот на 180 градусов
                direction = Direction::Up;
            break;
        case Qt::Key_Down:
            if (direction != Direction::Up)
                direction = Direction::Down;
            break;
        case Qt::Key_Left:
            if (direction != Direction::Right)
                direction = Direction::Left;
            break;
        case Qt::Key_Right:
            if (direction != Direction::Left)
                direction = Direction::Right;
            break;
        default:
            break;
        }
    }

private slots:

    void moveSnake()
    {
        QPoint newHead = snakeSegments.first(); // Получаем голову змейки

        switch (direction) {
        case Direction::Up:
            newHead.setY(newHead.y() - SIZE);
            break;
        case Direction::Down:
            newHead.setY(newHead.y() + SIZE);
            break;
        case Direction::Left:
            newHead.setX(newHead.x() - SIZE);
            break;
        case Direction::Right:
            newHead.setX(newHead.x() + SIZE);
            break;
        default:
            break;
        }

        // Проверяем столкновение со стенками
        if (newHead.x() < 0 || newHead.x() >= width() ||
            newHead.y() < 0 || newHead.y() >= height()) {
            gameOver();
            return;
        }

        // Проверяем столкновение с соседними сегментами
        for (int i = 2; i < snakeSegments.size(); ++i) {
            if (newHead == snakeSegments.at(i)) {
                gameOver();
                return;
            }
        }

        snakeSegments.prepend(newHead); // Добавляем новую голову в начало вектора сегментов
        if (snakeSegments.size() > snakeSize) {
            snakeSegments.pop_back(); // Если змейка превышает заданный размер, удаляем последний сегмент
        }

        update();
    }





    void gameOver()
    {
        timer->stop();
        QMessageBox::information(this, "Game Over", "Вы проиграли! Игра завершена.");
        QApplication::quit();
    }

private:
    enum class Direction { None, Up, Down, Left, Right };

    static constexpr int SIZE = 15;

    Direction direction;
    QTimer *timer;
    QVector<QPoint> snakeSegments;
    int snakeSize = 20; // Размер змейки (длина хвоста)
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SnakeGame game;
    game.show();

    return app.exec();
}
