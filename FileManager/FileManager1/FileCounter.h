#ifndef FILECOUNTER_H
#define FILECOUNTER_H

#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

class FileCounter : public QObject
{
    Q_OBJECT

public:
    FileCounter(QObject *parent = nullptr);

    void setFilePath(const QString &filePath);  // Установка пути к файлу
    void startCounting();  // Начало подсчета
    void stopCounting();  // Остановка подсчета

signals:
    void progressUpdated(int progress, int lineCount);  // Сигнал обновления прогресса
    void countFinished();  // Сигнал о завершении подсчета

private:
    QString m_filePath;  // Путь к файлу
    QThread m_thread;  // Поток для выполнения подсчета
    volatile bool m_stopFlag;  // Флаг для остановки подсчета

    void countLines();  // Метод для подсчета количества строк

private slots:
    void handleCountingFinished();  // Обработчик завершения подсчета
};

#endif // FILECOUNTER_H
