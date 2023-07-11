#include "FileLinesCounterModel.h"


FileLinesCounterModel::FileLinesCounterModel(QObject *parent)
    : QObject(parent), stopFlag(false)
{
    moveToThread(&count_thread); // Перемещение объекта в отдельный поток
    connect(&count_thread, &QThread::started, this, &FileLinesCounterModel::countLines); // Подключение метода countLines() к сигналу started() потока
    connect(this, &FileLinesCounterModel::countFinished, this, &FileLinesCounterModel::handleCountingFinished); // Подключение метода handleCountingFinished() к сигналу countFinished()
}


void FileLinesCounterModel::setFilePath(const QString &new_filePath)
{
    filePath = new_filePath; // Установка пути к файлу
}

void FileLinesCounterModel::startCounting()
{
    stopFlag = false; // Сброс флага остановки
    count_thread.start(); // Запуск потока
}

void FileLinesCounterModel::stopCounting()
{
    stopFlag = true; // Установка флага остановки
}

void FileLinesCounterModel::countLines()
{
    int lineCount = 0; // Счетчик строк

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if (file.size() == 0) // Обрабатываем файл размером 0 байт
        {
            file.close();
            emit progressUpdated(0, 0);
            emit countFinished();
            return;
        }

        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            if (stopFlag.load()) // Проверка флага остановки
                break;

            stream.readLine();
            ++lineCount;

            // Рассчитываем и отправляем прогресс
            int progress = static_cast<int>((file.pos() * 100) / file.size());
            emit progressUpdated(progress, lineCount); // Отправка сигнала обновления прогресса

        }

        file.close();
        emit countFinished(); // Отправка сигнала завершения подсчета
    }
}

void FileLinesCounterModel::handleCountingFinished()
{
    count_thread.quit(); // Остановка потока
}
