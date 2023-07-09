#include "FileCounter.h"


FileCounter::FileCounter(QObject *parent)
    : QObject(parent), m_stopFlag(false)
{
    moveToThread(&m_thread); // Перемещение объекта в отдельный поток
    connect(&m_thread, &QThread::started, this, &FileCounter::countLines); // Подключение метода countLines() к сигналу started() потока
    connect(this, &FileCounter::countFinished, this, &FileCounter::handleCountingFinished); // Подключение метода handleCountingFinished() к сигналу countFinished()
}


void FileCounter::setFilePath(const QString &filePath)
{
    m_filePath = filePath; // Установка пути к файлу
}

void FileCounter::startCounting()
{
    m_stopFlag = false; // Сброс флага остановки
    m_thread.start(); // Запуск потока
}

void FileCounter::stopCounting()
{
    m_stopFlag = true; // Установка флага остановки
}

void FileCounter::countLines()
{
    int lineCount = 0; // Счетчик строк

    QFile file(m_filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            if (m_stopFlag) // Проверка флага остановки
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

void FileCounter::handleCountingFinished()
{
    m_thread.quit(); // Остановка потока
}
