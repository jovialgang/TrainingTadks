#include <QApplication>
#include "SnakeWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SnakeWidget snakeWidget; // Создание виджета с игрой
    snakeWidget.show(); // Отображение виджета

    return app.exec(); // Запуск цикла обработки событий приложения
}
