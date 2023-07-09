#include "Widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent), m_counter(nullptr)
{

    setFixedSize(400, 250);

    m_fileLabel = new QLabel("File:");
    m_browseButton = new QPushButton("Browse");
    m_progressLabel = new QLabel("Progress:");
    m_countLabel = new QLabel("Count:");
    m_timeLabel = new QLabel("Time remaining:");
    m_startButton = new QPushButton("Start");
    m_stopButton = new QPushButton("Stop");
    m_progressBar = new QProgressBar();

    connect(m_browseButton, &QPushButton::clicked, this, &Widget::browseFile);
    connect(m_startButton, &QPushButton::clicked, this, &Widget::startCounting);
    connect(m_stopButton, &QPushButton::clicked, this, &Widget::stopCounting);

    QHBoxLayout *fileLayout = new QHBoxLayout();
    fileLayout->addWidget(m_fileLabel);
    fileLayout->addWidget(m_browseButton);

    QHBoxLayout *progressLayout = new QHBoxLayout();
    progressLayout->addWidget(m_progressLabel);
    progressLayout->addWidget(m_progressBar);

    QHBoxLayout *countLayout = new QHBoxLayout();
    countLayout->addWidget(m_countLabel);

    QHBoxLayout *timeLayout = new QHBoxLayout(); // Макет для метки времени
    timeLayout->addWidget(m_timeLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(progressLayout);
    mainLayout->addLayout(countLayout);
    mainLayout->addLayout(timeLayout); // Добавление макета времени в главный макет
    mainLayout->addWidget(m_startButton);
    mainLayout->addWidget(m_stopButton);

    m_progressBar->setMinimum(0);
    m_progressBar->setMaximum(100);
    m_progressBar->setValue(0);
}


void Widget::browseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File"); // Открытие диалогового окна выбора файла
    if (!filePath.isEmpty())
    {
        m_filePath = filePath;
        m_fileLabel->setText("File: " + filePath); // Обновление метки с выбранным файлом
    }
}

void Widget::startCounting()
{
    if (!m_filePath.isEmpty())
    {
        if (m_counter && m_counter->thread()->isRunning()) // Проверка, запущен ли уже счетчик
            return;

        m_counter = new FileCounter(); // Создание экземпляра класса FileCounter
        m_counter->setFilePath(m_filePath);

        connect(m_counter, &FileCounter::progressUpdated, this, &Widget::updateProgress); // Подключение метода updateProgress() к сигналу progressUpdated()

        m_timer.start(); // Запуск таймера
        m_counter->startCounting(); // Запуск подсчета
    }
}

void Widget::stopCounting()
{
    if (m_counter && m_counter->thread()->isRunning()) // Проверка, запущен ли счетчик
    {
        m_counter->stopCounting(); // Вызов метода stopCounting() на экземпляре класса FileCounter
    }
}

void Widget::updateProgress(int progress, int count)
{
    m_progressBar->setValue(progress); // Обновление значения прогресс-бара
    updateRemainingTime(progress); // Обновление оставшегося времени
    m_countLabel->setText("Count: " + QString::number(count)); // Обновление метки с количеством строк

}

void Widget::updateRemainingTime(int progress)
{
    qint64 elapsedTime = m_timer.elapsed(); // Получение прошедшего времени
    if (progress > 0 && elapsedTime > 0)
    {
        qint64 totalTime = (elapsedTime * 100) / progress; // Вычисление общего времени
        qint64 remainingTime = totalTime - elapsedTime; // Вычисление оставшегося времени

        QString remainingTimeString = formatTime(remainingTime); // Форматирование оставшегося времени в строку
        m_timeLabel->setText("Time remaining: " + remainingTimeString); // Обновление метки с оставшимся временем
    }
}

QString Widget::formatTime(int milliseconds)  // Форматирование времени из миллисекунд в формат "чч:мм:сс"
{
    int seconds = (milliseconds / 1000) % 60;
    int minutes = ((milliseconds / 1000) / 60) % 60;
    int hours = ((milliseconds / 1000) / 3600) % 24;

    return QString("%1:%2:%3")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}
