#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QFileDialog>
#include <QHBoxLayout>

#include "FileCounter.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

private slots:
    void browseFile();  // Обработчик события выбора файла
    void startCounting();  // Обработчик события начала подсчета
    void stopCounting();  // Обработчик события остановки подсчета
    void updateProgress(int progress, int count);  // Обновление прогресса

private:
    QLabel *m_fileLabel;  // Метка для отображения выбранного файла
    QLabel *m_progressLabel;  // Метка для отображения прогресса
    QLabel *m_countLabel;  // Метка для отображения результата подсчета
    QLabel *m_timeLabel;  // Метка для отображения оставшегося времени
    QPushButton *m_browseButton;  // Кнопка для выбора файла
    QPushButton *m_startButton;  // Кнопка для начала подсчета
    QPushButton *m_stopButton;  // Кнопка для остановки подсчета
    QProgressBar *m_progressBar;  // Прогресс-бар для отображения прогресса подсчета

    QString m_filePath;  // Путь к файлу
    FileCounter *m_counter;  // Экземпляр класса FileCounter для подсчета
    QElapsedTimer m_timer;  // Таймер для измерения затраченного времени

    void updateRemainingTime(int progress);  // Обновление оставшегося времени
    QString formatTime(int milliseconds);  // Форматирование времени в формат "чч:мм:сс"
};

#endif // WIDGET_H
