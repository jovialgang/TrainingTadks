#ifndef FILELINESCOUNTERMODEL_H
#define FILELINESCOUNTERMODEL_H

#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <atomic>

class FileLinesCounterModel : public QObject
{
    Q_OBJECT

public:
    FileLinesCounterModel(QObject *parent = nullptr);

    void setFilePath(const QString &new_filePath);  // Установка пути к файлу
    void startCounting();  // Начало подсчета
    void stopCounting();  // Остановка подсчета

signals:
    void progressUpdated(int progress, int lineCount);  // Сигнал обновления прогресса
    void countFinished();  // Сигнал о завершении подсчета

private:
    QString filePath;  // Путь к файлу
    QThread count_thread;  // Поток для выполнения подсчета
    std::atomic<bool> stopFlag;  // Флаг для остановки подсчета

    void countLines();  // Метод для подсчета количества строк

private slots:
    void handleCountingFinished();  // Обработчик завершения подсчета
};

#endif // FILELINESCOUNTERMODEL_H
