#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Создаем окно приложения
    QWidget window;
    window.setWindowTitle("Простое приложение Qt");
    window.resize(250, 150);

    // Создаем кнопку
    QPushButton button("Нажми меня!", &window);
    button.setGeometry(50, 50, 150, 50);

    // Подключаем обработчик сигнала нажатия на кнопку
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        button.setText("Нажата!");
    });

    // Отображаем окно и запускаем главный цикл приложения
    window.show();
    return app.exec();
}
