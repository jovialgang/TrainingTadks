#include "SnakeGameModel.h"

SnakeGameModel::SnakeGameModel(QWidget *parent)
    : QWidget(parent), timer(nullptr)
{
    setFixedSize(500, 700); // Фиксированный размер игрового поля

    controller.setTarget(this); // Установка игрового поля как цели для контроллера

    int startX = width() / 2;
    int startY = height() / 2;

    for (int i = 0; i < snakeSize; ++i) {
        snakeSegments.append(QPoint(startX, startY - i * SIZE/5)); // Создание начальных сегментов змейки
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SnakeGameModel::moveSnake); // Подключение таймера к слоту перемещения змейки
    connect(&controller, &SnakeController::directionChanged, this, &SnakeGameModel::changeDirection); // Подключение сигнала изменения направления к слоту изменения направления змейки
    timer->start(25); // Запуск таймера для перемещения змейки

    setFocusPolicy(Qt::StrongFocus); // Установка фокуса на игровое поле

    generateFood(); // Генерация начальной еды
}


void SnakeGameModel::moveSnake()
{
    QPoint newHead = snakeSegments.first(); // Получение координат головы змейки

    switch (currentDirection) {
    case 0: // Вверх
            newHead.setY(newHead.y() - SIZE/5);
        break;
    case 1: // Вниз
        newHead.setY(newHead.y() + SIZE/5);
        break;
    case 2: // Влево
        newHead.setX(newHead.x() - SIZE/5);
        break;
    case 3: // Вправо
        newHead.setX(newHead.x() + SIZE/5);
        break;
    default:
        break;
    }

    if (newHead.x() < 0 || newHead.x() >= width() ||
        newHead.y() < 0 || newHead.y() >= height()) {
        emit gameFinished(); // Сигнал о завершении игры, если змейка столкнулась со стеной
        return;
    }

    for (int i = 1; i < snakeSegments.size(); ++i) {
        if (newHead == snakeSegments.at(i)) {
            emit gameFinished(); // Сигнал о завершении игры, если змейка столкнулась с самой собой
            return;
        }
    }

    snakeSegments.prepend(newHead); // Добавление новой головы в начало списка сегментов змейки
    if (snakeSegments.size() > snakeSize) {
        snakeSegments.pop_back(); // Удаление последнего сегмента, если змейка достигла максимального размера
    }

    if (qAbs(newHead.x() - food.x()) <= SIZE && qAbs(newHead.y() - food.y()) <= SIZE) {
        generateFood(); // Генерация новой еды, если змейка съела текущую еду
        snakeSize += 10; // Увеличение размера змейки
    }

    emit snakeUpdated(snakeSegments); // Cигнал обновления отрисовки игрового поля
}

void SnakeGameModel::generateFood() // Генерация еды
{
    QRandomGenerator *random = QRandomGenerator::global(); // Генератор случайных чисел
    int posOfFoodX = random->bounded(10, width()-40);
    int posOfFoodY = random->bounded(10, height()-40);

    for (const auto& segment : snakeSegments) {
        if (QPoint(posOfFoodX, posOfFoodY) == segment) {
            generateFood(); // Повторная генерация позиции еды, если она совпадает с позицией сегмента змейки
            return;
        }
    }

    food = QPoint(posOfFoodX, posOfFoodY); // Установка новой позиции еды
}


void SnakeGameModel::changeDirection(int direction) // Изменение направления змейки
{
    currentDirection = direction; // Изменение текущего направления змейки в соответствии с полученным направлением
}
