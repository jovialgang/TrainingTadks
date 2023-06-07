#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Простое приложение Qt");
    mainWindow.resize(250, 150);

    QPushButton button("Нажми меня!", &mainWindow);
    button.setGeometry(QRect(30, 50, 200, 50));

    QObject::connect(&button, &QPushButton::clicked, [&]() {
        static int clickCount = 0;
        clickCount++;

        if (clickCount % 2 == 1) {
            button.setText("Нажата!");
        } else {
            button.setText("Нажми меня снова!");
        }
    });

    mainWindow.setCentralWidget(&button);
    mainWindow.show();

    return app.exec();
}


//#include <QApplication>
//#include <QPushButton>

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    // Создаем окно приложения
//    QWidget window;
//    window.setWindowTitle("Простое приложение Qt");
//    window.resize(250, 150);

//    // Создаем кнопку
//    QPushButton button("Нажми меня!", &window);
//    button.setGeometry(30, 50, 200, 50);

//    // Подключаем обработчик сигнала нажатия на кнопку
//    QObject::connect(&button, &QPushButton::clicked, [&]() {
//        button.setText("Нажата!");
//    });

//    QObject::connect(&button, &QPushButton::clicked, [&]() {
//        button.setText("Нажата ещё раз!");
//    });

//    QObject::connect(&button, &QPushButton::clicked, [&]() {
//        button.setText("Слыш, иди уже от сюда!");
//    });

//    // Отображаем окно и запускаем главный цикл приложения
//    window.show();
//    return app.exec();
//}
