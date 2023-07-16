#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPainter>
#include <QTransform>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent), m_PointModel(nullptr), ui(new Ui::MainWindow) {
    // Инициализация пользовательского интерфейса
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
    setMouseTracking(true);

    // Создание экземпляров объектов PointEditor, AddArrowWidget и Helper
    m_pointEditor = new PointEditor(this);
    m_addArrow = new AddArrowDialog(this);
    m_helper = new Helper(this);

    // Установка соединений сигналов и слотов
    {
        connect(m_pointEditor, &PointEditor::pointUpdated, this, &MainWindow::updatePointValue);
        connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::spinBox_valueChanged);
        connect(ui->deleteButton, &QPushButton::released, this, &MainWindow::deleteArrow);
        connect(ui->addArrowButton, &QPushButton::released, m_addArrow, &AddArrowDialog::showArrowAdder);
        connect(ui->undoButton, &QPushButton::released, this, &MainWindow::undoAction);
        connect(ui->redoButton, &QPushButton::released, this, &MainWindow::redoAction);
        connect(ui->updatePoints, &QPushButton::released, this, &MainWindow::updatePointList);
        connect(ui->updateConnectedPoints, &QPushButton::released, this, &MainWindow::updateConnectedPointsList);
        connect(m_addArrow, &AddArrowDialog::arrowsAdded, this, &MainWindow::buildAddedArrows);
        connect(m_addArrow, &AddArrowDialog::arrowsAddedByValue, this, &MainWindow::buildArrowsByValues);
        connect(ui->helpButton, &QPushButton::released, this, &MainWindow::helpButton_pressed);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Установка модели PointModel для класса MainWindow
void MainWindow::setModel(PointModel *PointModel) {
    m_PointModel = PointModel;
    update();
}



// Выделение выбранной стрелки и связанных с ней точек
void MainWindow::highlightSelectedArrow() {
    // Снятие выделения со всех точек
    for (int i = 0; i < m_PointModel->getPoints().size(); ++i) {
        m_PointModel->setHighlighted(i, false);
    }

    // Снятие выделения со всех стрелок
    for (int i = 0; i < m_arrows.size(); i++) {
        m_arrows[i].setHighlighted(false);
    }

    // Выделение точек, связанных с выбранной стрелкой
    if (m_selectedArrowIndex != -1 && m_selectedArrowIndex <= m_arrows.size()) {
        Arrow& selectedArrow = m_arrows[m_selectedArrowIndex];
        selectedArrow.setHighlighted(true);
        m_PointModel->setHighlighted(selectedArrow.getStartPointIndex(), true);
        m_PointModel->setHighlighted(selectedArrow.getEndPointIndex(), true);
    }

    // Установка доступности кнопок deleteButton, undoButton и redoButton
    ui->deleteButton->setEnabled(m_selectedArrowIndex != -1);
    ui->undoButton->setEnabled(!m_undoArrows.isEmpty());
    ui->redoButton->setEnabled(!m_arrows.isEmpty());

    // Обновление отображения
    update();
}



// Обработка события перерисовки окна
void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Проверка наличия модели PointModel
    if (!m_PointModel) return;

    ui->spinBox->setMaximum(m_arrows.size());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(m_scale, m_scale);

    // Отрисовка точек и стрелок
    m_PointModel->draw(painter);
    drawArrows(painter, m_PointModel->getPoints());
}


// Отрисовка стрелок
void MainWindow::drawArrows(QPainter& painter, const QVector<Point>& points) const {
    for (const Arrow& arrow : m_arrows) {
        arrow.draw(painter, points);
    }
}



// Обработка события перемещения мыши
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (!m_PointModel) return;

    // Перебор точек и проверка наличия перемещения мыши над точкой
    for (int i = 0; i < m_PointModel->getPoints().size(); ++i) {
        const Point& point = m_PointModel->getPoints().at(i);

        // Применение обратного преобразования координат
        qreal mouseX = event->pos().x() / m_scale;
        qreal mouseY = event->pos().y() / m_scale;

        QRectF rect(point.x, point.y, 20, 20);

        // Проверка, что точка содержит координаты мыши и нажата левая кнопка мыши
        // Обработка обычной стрелки
        if (rect.contains(mouseX, mouseY) && event->buttons() & Qt::LeftButton) {
            if (m_selectedPointIndex == -1) {
                m_selectedPointIndex = i;
            } else if (m_selectedPointIndex != i) {
                int startPointIndex = m_selectedPointIndex;
                int endPointIndex = i;

                // Проверка, является ли выбранная точка концом предыдущей стрелки
                if (m_arrows.isEmpty() || m_arrows.last().getEndPointIndex() == startPointIndex) {
                    Arrow arrow;
                    arrow.setStartPointIndex(startPointIndex);
                    arrow.setEndPointIndex(endPointIndex);
                    m_arrows.append(arrow);
                    highlightSelectedArrow();
                }

                m_selectedPointIndex = -1;

                update();
            }
        }


        // Обработка петли
        if (m_selectedPointIndex != -1 && event->buttons() & Qt::RightButton) {
            int startPointIndex = m_selectedPointIndex;
            int endPointIndex = startPointIndex;

            Arrow arrow;
            arrow.setStartPointIndex(startPointIndex);
            arrow.setEndPointIndex(endPointIndex);
            m_arrows.append(arrow);
            ui->spinBox->setMaximum(m_arrows.size());

            m_selectedPointIndex = -1;
            update();
        }

        // Отображение параметров точки при наведении мыши
        if (rect.contains(mouseX, mouseY)) {
            QString pointValue = tr("PosX: %1 \nPosY: %2 \nValue: %3")
                                     .arg(point.x)
                                     .arg(point.y)
                                     .arg(point.value);
            QToolTip::showText(event->globalPos(), pointValue, this);
            return;
        }
    }


    QToolTip::hideText();
}



// Обработка события двойного клика мыши
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    if (!m_PointModel) return;

    QTransform transform;
    transform.scale(m_scale, m_scale);
    QTransform invTransform = transform.inverted();
    QPointF transformedMousePos = invTransform.map(event->pos());

    // Проверка, что щелчок мыши произошел на стрелке (выделяем стрелку)
    for (int i = m_arrows.size() - 1; i >= 0; --i) {
        const Arrow& arrow = m_arrows[i];
        if (arrow.contains(transformedMousePos, m_PointModel->getPoints(), m_scale)) {
            m_selectedArrowIndex = i;
            ui->spinBox->setValue(i + 1);
            highlightSelectedArrow();
            return;
        }
    }

    // Проверка, что щелчок мыши произошел на точке (открываем редактор точки)
    for (int i = 0; i < m_PointModel->getPoints().size(); ++i) {
        const Point& point = m_PointModel->getPoints().at(i);

        qreal mouseX = event->pos().x() / m_scale;
        qreal mouseY = event->pos().y() / m_scale;

        QRectF rect(point.x, point.y, pointSize, pointSize);

        if (rect.contains(mouseX, mouseY) && event->button() == Qt::LeftButton) {
            m_currentPointIndex = i;
            m_pointEditor->showPointEditor(event->pos(), point);
            return;
        }
    }
}


// Обработка события одинарного клика мыши
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (!m_PointModel) return;

    // Проверка, что щелчок мыши произошел на объекте
    bool clickedOnObject = false;
    for (int i = 0; i < m_PointModel->getPoints().size(); ++i) {
        const Point& point = m_PointModel->getPoints().at(i);

        qreal mouseX = event->pos().x() / m_scale;
        qreal mouseY = event->pos().y() / m_scale;

        QRectF rect(point.x, point.y, pointSize, pointSize);

        if (rect.contains(mouseX, mouseY)) {
            clickedOnObject = true;
            break;
        }
    }

    // Сброс выбора стрелки и выделение
    if (!clickedOnObject) {
        ui->spinBox->setValue(0);
        m_selectedArrowIndex = -1;
        highlightSelectedArrow();
        update();
    }

    QWidget::mousePressEvent(event);
}


// Обработка события прокрутки колёсика мыши
void MainWindow::wheelEvent(QWheelEvent *event) {
    // Определяем величину изменения масштаба
    const qreal scaleFactor = 1.005;
    int delta = event->angleDelta().y();

    // Масштабирование содержимого виджета
    if (delta > 0) {
        // Zoom in
        m_scale *= scaleFactor;
    } else {
        // Zoom out
        m_scale /= scaleFactor;
    }
    update();

}


// Обновление значения точки
void MainWindow::updatePointValue(Point point) {
    m_PointModel->updatePoint(point, m_currentPointIndex);
//    updatePointList();
    update();
}


// Обработка изменения значения в spinBox
void MainWindow::spinBox_valueChanged(int arg1)
{
    m_selectedArrowIndex = arg1 - 1;
    highlightSelectedArrow();
    update();
}


// Удаление выбранной стрелки
void MainWindow::deleteArrow() {
    if (m_selectedArrowIndex != -1) {
        // Подтверждение удаления стрелки
        int confirmResult = QMessageBox::question(this, tr("Подтверждение"), tr("Вы уверены, что хотите удалить выбранную стрелку?"
                                                                                             "\nВсе последующие так же будут удалены."), QMessageBox::Yes | QMessageBox::No);
        if (confirmResult == QMessageBox::Yes) {
            // Сохранение удаленных стрелок для возможности отмены действия
            m_undoArrows.clear();
            for (int i = m_selectedArrowIndex; i < m_arrows.size(); i++) {
                m_undoArrows.append(m_arrows.at(i));
            }

            // Удаление выбранных стрелок
            m_arrows.erase(m_arrows.begin() + m_selectedArrowIndex, m_arrows.end());
            highlightSelectedArrow();

            // Сброс выбранной точки, если стрелок больше нет
            if (m_arrows.empty()) {
                m_selectedPointIndex = -1;
            }

            // Сброс выбранной стрелки и обновление интерфейса
            m_selectedArrowIndex = -1;
            ui->spinBox->setMaximum(m_arrows.size());
            ui->spinBox->setValue(0);
            highlightSelectedArrow();
//            updatePointList();
            update();
        }
    }
}

// Восстановление последней удаленной стрелки
void MainWindow::undoAction() {
    if (!m_undoArrows.isEmpty()) {
        Arrow lastDeletedArrow = m_undoArrows.takeFirst();
        m_arrows.append(lastDeletedArrow);

        // Выбор восстановленной стрелки и обновление интерфейса
        m_selectedArrowIndex = m_arrows.size() - 1;
        ui->spinBox->setMaximum(m_arrows.size());
        ui->spinBox->setValue(m_selectedArrowIndex + 1);
        highlightSelectedArrow();
//        updatePointList();
        update();
    }
}

// Удаление последней добавленной стрелки
void MainWindow::redoAction() {
    if (!m_arrows.isEmpty()) {
        // Удаление последней добавленной стрелки
        Arrow lastRestoredArrow = m_arrows.takeLast();
        m_undoArrows.prepend(lastRestoredArrow);

        // Выбор предыдущей стрелки и обновление интерфейса
        m_selectedArrowIndex = m_arrows.size() - 1;
        ui->spinBox->setMaximum(m_arrows.size());
        ui->spinBox->setValue(m_selectedArrowIndex + 1);
        highlightSelectedArrow();
//        updatePointList();
        update();
    }
}


// Обновление списка точек
void MainWindow::updatePointList() {
    QString pointList;
    const QVector<Point>& points = m_PointModel->getPoints();

    int pointCount = 0;

    for (const Point& point : points) {
        pointCount++;

        // Формирование строки с параметрами точки
        pointList += QString("Point № %1:\n").arg(pointCount);
        pointList += QString("PosX: %1, PosY: %2, Value: %3\n\n")
                         .arg(point.x)
                         .arg(point.y)
                         .arg(point.value);
    }

    // Установка текста в plainTextEdit
    ui->plainTextEdit->setPlainText(pointList);
}

// Обновление списка связанных точек
void MainWindow::updateConnectedPointsList() {
    if (m_arrows.empty()){
        ui->plainTextEdit->clear();
        return;
    }

    QString connectedPointsList;
    const QVector<Point>& points = m_PointModel->getPoints();

    int arrowCount = 0;

    const Point& startPoint = points[m_arrows.at(0).getStartPointIndex()];

    connectedPointsList += QString("Arrow № 1:\n").arg(arrowCount);

    connectedPointsList += QString("Start: PosX: %1, PosY: %2, Value: %3\n\n")
                               .arg(startPoint.x)
                               .arg(startPoint.y)
                               .arg(startPoint.value);

    for (const Arrow& arrow : m_arrows) {

        if (arrow.getStartPointIndex() < points.size() && arrow.getEndPointIndex() < points.size()) {
            arrowCount++;
            const Point& endPoint = points[arrow.getEndPointIndex()];

            connectedPointsList += QString(tr("Arrow № %1, \n"))
                                        .arg(arrowCount);


            connectedPointsList += QString(tr("End: PosX: %1, PosY: %2, Value: %3\n\n"))
                                       .arg(endPoint.x)
                                       .arg(endPoint.y)
                                       .arg(endPoint.value);
        }
    }

    ui->plainTextEdit->setPlainText(connectedPointsList);
}

// Обработка добавления стрелок по координатам
void MainWindow::buildAddedArrows(const QVector<QPointF>& arrowPoints) {

    m_helper->buildAddedArrows(arrowPoints, m_PointModel->getPoints(), m_arrows);

    // Обновление интерфейса и отображение стрелок
    ui->spinBox->setMaximum(m_arrows.size());
    highlightSelectedArrow();
    update();
}


// Построение стрелок по значениям точек
void MainWindow::buildArrowsByValues(const QVector<QString>& values) {

    m_helper->buildArrowsByValues(values, m_PointModel->getPoints(), m_arrows);

    // Обновление интерфейса и отображение стрелок
    ui->spinBox->setMaximum(m_arrows.size());
    highlightSelectedArrow();
    update();
}


// Отображение справки
void MainWindow::helpButton_pressed() {
    m_helper->show();
}
