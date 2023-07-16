#include "Widget.h"
#include <QDebug>



Widget::Widget(QWidget *parent)
    : QWidget(parent), counter(nullptr)
{

    setFixedSize(400, 250);

    fileLabel = new QLabel(tr("%1").arg("File:"));
    browseButton = new QPushButton(tr("%1").arg("Browse"));
    progressLabel = new QLabel(tr("%1").arg("Progress:"));
    countLabel = new QLabel(tr("%1").arg("Count:"));
    timeLabel = new QLabel(tr("%1").arg("Time remaining:"));
    startButton = new QPushButton(tr("%1").arg("Start"));
    stopButton = new QPushButton(tr("%1").arg("Stop"));
    progressBar = new QProgressBar();

    connect(browseButton, &QPushButton::clicked, this, &Widget::browseFile); // Подключение сигналов кнопок к слотам
    connect(startButton, &QPushButton::clicked, this, &Widget::startCounting);
    connect(stopButton, &QPushButton::clicked, this, &Widget::stopCounting);

    QHBoxLayout *fileLayout = new QHBoxLayout(); // Макет для файла
    fileLayout->addWidget(fileLabel);
    fileLayout->addWidget(browseButton);

    QHBoxLayout *progressLayout = new QHBoxLayout(); // Макет для отображения прогресса
    progressLayout->addWidget(progressLabel);
    progressLayout->addWidget(progressBar);

    QHBoxLayout *countLayout = new QHBoxLayout(); // Макет для подсчета
    countLayout->addWidget(countLabel);

    QHBoxLayout *timeLayout = new QHBoxLayout(); // Макет для метки времени
    timeLayout->addWidget(timeLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(fileLayout); // Добавление макета файла на главный макет
    mainLayout->addLayout(progressLayout); // Добавление макета прогресс-бара на главный макет
    mainLayout->addLayout(countLayout); // Добавление макета подсчета на главный макет
    mainLayout->addLayout(timeLayout); // Добавление макета времени на главный макет
    mainLayout->addWidget(startButton); // Добавление кнопки старта на главный макет
    mainLayout->addWidget(stopButton); // Добавление кнопки остановки на главныйй макет

    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(0);

    updateButtonState();
}


void Widget::browseFile()
{
    QString text_filePath = QFileDialog::getOpenFileName(this, tr("%1").arg("Select File")); // Открытие диалогового окна выбора файла
    if (text_filePath.isEmpty())
    {
        return;
    }
    filePath = text_filePath;
    fileLabel->setText(tr("%1").arg("File: ") + text_filePath); // Обновление метки с выбранным файлом
}

void Widget::startCounting()
{
    if (filePath.isEmpty())
    {
        return;
    }

    if (counter->checkThread()) // Проверка, запущен ли уже поток
        return;


    // Проверяем, существует ли выбранный файл
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists())
    {
        QMessageBox::critical(this, "Ошибка", "Выбранный файл не существует!");
        return;
    }

    counter = new FileLinesCounterModel(); // Создание экземпляра класса FileCounter
    counter->setFilePath(filePath);

    connect(counter, &FileLinesCounterModel::progressUpdated, this, &Widget::updateProgress); // Подключение метода updateProgress() к сигналу progressUpdated()


    timer.start(); // Запуск таймера
    counter->startCounting(); // Запуск подсчета

    updateButtonState(); // Обновление состояния кнопок
}

void Widget::stopCounting()
{
    if (counter->checkThread()) // Проверка, запущен ли счетчик
    {
        counter->stopCounting(); // Вызов метода stopCounting() на экземпляре класса FileCounter
    }

}

void Widget::updateProgress(int progress, int count)
{
    progressBar->setValue(progress); // Обновление значения прогресс-бара
    updateRemainingTime(progress); // Обновление оставшегося времени
    countLabel->setText(tr("%1").arg("Count: ") + QString::number(count)); // Обновление метки с количеством строк
    updateButtonState();

}

void Widget::updateRemainingTime(int progress) // Обновление оставшегося времени
{
    qint64 elapsedTime = timer.elapsed(); // Получение прошедшего времени
    {
        qint64 totalTime = (elapsedTime * 100) / progress; // Вычисление общего времени
        qint64 remainingTime = totalTime - elapsedTime; // Вычисление оставшегося времени

        QString remainingTimeString = formatTime(remainingTime); // Форматирование оставшегося времени в строку
        timeLabel->setText(tr("Time remaining: ") + remainingTimeString); // Обновление метки с оставшимся временем
    }
}

QString Widget::formatTime(int milliseconds)  // Форматирование времени из миллисекунд в формат "чч:мм:сс"
{
    int seconds = (milliseconds / 1000) % 60;
    int minutes = ((milliseconds / 1000) / 60) % 60;
    int hours = ((milliseconds / 1000) / 3600) % 24;

    return tr("%1:%2:%3")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

void Widget::updateButtonState()
{
    // Блокировка или разблокировка кнопок start и stop в зависимости от состояния потока
    if (counter->checkThread())
    {
        startButton->setEnabled(false);
        stopButton->setEnabled(true);
    }
    else
    {
        startButton->setEnabled(true);
        stopButton->setEnabled(false);
    }
}

//bool Widget::checkThread()
//{
////    qDebug() << counter->thread()->isRunning();
//    if (counter && counter->thread()) return true;
//    return counter && counter->thread()->isRunning() && counter->thread()!=nullptr;
//}
