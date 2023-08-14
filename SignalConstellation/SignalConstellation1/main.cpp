#include <QApplication>
#include <vector>
#include <QFile>
#include <QStyle>
#include <QtWidgets/QApplication>
#include <filesystem>
#include <iostream>
#include "UserTest.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    UserTest userTest; // Создание тестового приложения с использованием моего виджета
    userTest.show();

    return a.exec();
}
