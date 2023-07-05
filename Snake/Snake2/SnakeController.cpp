#include "SnakeController.h"

SnakeController::SnakeController(QObject *parent)
    : QObject(parent)
{
}

void SnakeController::setTarget(QWidget *target)
{
    this->Target = target; // Установка целевого виджета
    if (target)
        target->installEventFilter(this); // Установка фильтра событий для целевого виджета
}

void SnakeController::handleKeyPress(QKeyEvent *event)
{

    static int direction = -1;

    switch (event->key()) {
    case Qt::Key_Up:
        if (direction != 1) direction = 0; // Направление вверх
        break;
    case Qt::Key_Down:
        if (direction != 0) direction = 1; // Направление вниз
        break;
    case Qt::Key_Left:
        if (direction != 3) direction = 2; // Направление влево
        break;
    case Qt::Key_Right:
        if (direction != 2) direction = 3; // Направление вправо
        break;
    default:
        break;
    }

    if (direction != -1)
        emit directionChanged(direction); // Сигнал об изменении направления
}

bool SnakeController::eventFilter(QObject *obj, QEvent *event)
{
    if ((obj == Target) && (event->type() == QEvent::KeyPress)) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        handleKeyPress(keyEvent); // Обработка нажатия клавиши
        return true;
    }

    return QObject::eventFilter(obj, event);
}
