#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>

#include "FileLinesCounterModel.h"

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
    QLabel *fileLabel;  // Метка для отображения выбранного файла
    QLabel *progressLabel;  // Метка для отображения прогресса
    QLabel *countLabel;  // Метка для отображения результата подсчета
    QLabel *timeLabel;  // Метка для отображения оставшегося времени
    QPushButton *browseButton;  // Кнопка для выбора файла
    QPushButton *startButton;  // Кнопка для начала подсчета
    QPushButton *stopButton;  // Кнопка для остановки подсчета
    QProgressBar *progressBar;  // Прогресс-бар для отображения прогресса подсчета

    QString filePath;  // Путь к файлу
    FileLinesCounterModel *counter;  // Экземпляр класса FileCounter для подсчета
    QElapsedTimer timer;  // Таймер для измерения затраченного времени

    void updateRemainingTime(int progress);  // Обновление оставшегося времени
    QString formatTime(int milliseconds);  // Форматирование времени в формат "чч:мм:сс"
    void updateButtonState();
};

#endif // WIDGET_H
