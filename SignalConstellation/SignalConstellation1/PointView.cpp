#include "PointView.h"

inline uint qHash(const QPointF& point, uint seed = 0) noexcept {
    return qHash(qRound(point.x()) ^ qRound(point.y()), seed);
}

PointView::PointView(QWidget* parent) : QGraphicsView(parent), currentScale(1.0) {
    setScene(new QGraphicsScene(this));
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    pointColor = Qt::black;
    arrowColor = QColor(84, 83, 83);


}

void PointView::setTheme(Theme color) {
    if (color == Theme::Light) {
        pointColor = Qt::black;
        arrowColor = QColor(84, 83, 83);
    } else if (color == Theme::Dark) {
        pointColor = Qt::white;
        arrowColor = QColor(148, 146, 146);

    }

    if (selectedArrowItem) {
        arrowAndPointHighlighter(selectedArrowItem->index);
    } else {
        arrowAndPointHighlighter(-1);
    }

    viewport()->update();
}

void PointView::setButtons(QSpinBox* spinBox, QPushButton* undoButton, QPushButton* redoButton, QPushButton* deleteButton,
                           QLineEdit* lineEdit, QCheckBox* showValuesCheckBox){
    this->spinBox = spinBox;
    this->undoButton = undoButton;
    this->redoButton = redoButton;
    this->deleteButton = deleteButton;
    this->lineEdit = lineEdit;
    this->showValuesCheckBox = showValuesCheckBox;
    this->spinBox->setMaximum(0);
    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &PointView::spinBoxChanged);
    connect(undoButton, &QPushButton::clicked, this, &PointView::undoAction);
    connect(redoButton, &QPushButton::clicked, this, &PointView::redoAction);
    connect(deleteButton, &QPushButton::clicked, this, &PointView::deleteSelectedArrow);
    connect(showValuesCheckBox, &QCheckBox::stateChanged, this, &PointView::onShowValuesCheckBoxChanged);



}

void PointView::onShowValuesCheckBoxChanged(bool checked) {
    foreach (PointItem* pointItem, pointItems) {
        pointItem->showValue = checked;
    }
    coordinateAxes->showValue = checked;

    viewport()->update();
}

// Метод добавления точек и координатных осей
ResultCode PointView::addPoints(const QVector<Point>& points) {
    if (points.size() > 10000) {
        return ResultCode::ErrorTooManyPoints;
    }

    if (!checkPointValues(points)) {
        // Обработка ошибки: неверные значения точек
        return ResultCode::InvalidPointValues;
    }

    for (int i = 0; i < points.size(); ++i) {
        const Point& point = points[i];
        PointItem* pointItem = new PointItem(point);
        pointItem->index = i;
        pointItem->setPos(point.x * 100, - point.y * 100);
        pointItem->maxValueSize = static_cast<int>(log2(points.size())) + 1;
        scene()->addItem(pointItem);
        pointItems.append(pointItem);
        connect(pointItem, &PointItem::pointItemDoubleClicked, this, &PointView::updatePointDuplicatColors);
    }


    updatePointDuplicatColors();
    setStartScale();
    updatePiontAndArrowSize();

    coordinateAxes = new CoordinateAxes(qMax(abs(maxX), abs(minX)), qMax(abs(maxY), abs(minY)));
    scene()->addItem(coordinateAxes);
    coordinateAxes->setZValue(-1);
    coordinateAxes->setPointsCount(qSqrt(pointItems.size()));



    return ResultCode::Success;

}

// Метод для подгонки начального масштаба
void PointView::setStartScale() {
    if (pointItems.isEmpty()) return;

    foreach (PointItem* pointItem, pointItems) {
        double x = pointItem->x();
        double y = pointItem->y();

        minX = qMin(x, minX);
        maxX = qMax(x, maxX);
        minY = qMin(y, minY);
        maxY = qMax(y, maxY);
    }

    double width = maxX - minX;
    double height = maxY - minY;



    double scaleX = (viewport()->width() * 1) / (width / 10);
    double scaleY = (viewport()->height() * 1) / (height / 10);

    qreal scaleFactor = std::min(scaleX, scaleY);

    scale(scaleFactor, scaleFactor);
    currentScale *= scaleFactor;
    maxCurrentScale = currentScale;
}


void PointView::updatePointDuplicatColors() {
    // Хэш таблица для хранения точек с одинаковыми значениями Value
    QHash<QString, QList<PointItem*>> valuePointsMap;

    foreach (PointItem* pointItem, pointItems) {
        // Группируем точки по значениям Value
        valuePointsMap[pointItem->pointData.value].append(pointItem);
        if (selectedArrowItem)
            if (pointItem != selectedArrowItem->startPointItem && pointItem != selectedArrowItem->endPointItem){
                pointItem->setPointColor(pointColor);
            }
    }

    // Переменная для хранения уникального цвета для подсветки
    int hue = 0;

    // Проходим по значениям Value и подсвечиваем точки с разными значениями разными цветами
    foreach (const QList<PointItem*>& pointsWithSameValue, valuePointsMap) {
        if (pointsWithSameValue.size() > 1) {
            // Вычисляем уникальный цвет для подсветки
            int uniqueHue = hue % 360;
            foreach (PointItem* pointItem, pointsWithSameValue) {
                if (uniqueHue == 60) hue += 60;
                pointItem->setPointColor(QColor::fromHsv(uniqueHue, 255, 205));
            }
            hue += 60; // Интервал между уникальными цветами
        }
    }
}




// Метод для выделения точек и стрелок
void PointView::arrowAndPointHighlighter(int arrowIndex) {
    if (deleteButton) deleteButton->setEnabled(arrowIndex != -1);
    if (undoButton) undoButton->setEnabled(!arrowItems.isEmpty());
    if (redoButton) redoButton->setEnabled(!undoVector.isEmpty());
    if (spinBox) spinBox->setMaximum(arrowItems.size());

    foreach (PointItem* pointItem, pointItems) {
        pointItem->setPointColor(pointColor);
        pointItem->selected = false;
    }

    foreach (ArrowItem* arrowItem, arrowItems) {
        arrowItem->setPen(QPen(arrowColor, 1));

    }

    updatePointDuplicatColors();


    if (!arrowItems.isEmpty()) arrowItems.last()->endPointItem->setPointColor(Qt::green);
    if (arrowIndex < 0) {
        selectedArrowItem = nullptr;
        if (spinBox) spinBox->setValue(0);
        return;
    }

    foreach (ArrowItem* arrowItem, arrowItems) {
        if (arrowItem->index == arrowIndex) {
            arrowItem->setPen(QPen(Qt::red, 2));
            arrowItem->startPointItem->setPointColor(Qt::yellow);
            arrowItem->endPointItem->setPointColor(Qt::yellow);
            arrowItem->startPointItem->selected = true;
            arrowItem->endPointItem->selected = true;
            selectedArrowItem = arrowItem;
            spinBox->setValue(arrowIndex + 1);
            break;
        }
    }

    if (!arrowItems.isEmpty()) lastArrowEndItem = arrowItems.last()->endPointItem;

    viewport()->update();
}



// Метод используется для выбора точки, с которой начинается стрелка.
void PointView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        QPointF startPos = mapToScene(event->pos());
        lastArrowEndItem = nullptr;
        selectedPoint = nullptr;
        QList<QGraphicsItem*> items = scene()->items(startPos);
        foreach (QGraphicsItem* item, items) {
            PointItem* pointItem = dynamic_cast<PointItem*>(item);
            if (pointItem) {
                if (!arrowItems.isEmpty()) {
                    if (QPointF(pointItem->x(), pointItem->y()) != arrowItems.last()->endPointItem->pos()){
                        lastArrowEndItem = nullptr;
                    } else {
                        lastArrowEndItem = pointItem;
                        selectedPoint = pointItem;
                        selectedPoint->setPointColor(Qt::yellow);
                    }
                } else {
                    lastArrowEndItem = pointItem;
                    selectedPoint = pointItem;
                    selectedPoint->setPointColor(Qt::yellow);
                }
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}


// Метод используется для выборта точки, на которой стрелка заканчивается
void PointView::mouseReleaseEvent(QMouseEvent* event) {

    if (!selectedArrowItem) arrowAndPointHighlighter(-1);

    selectedPoint = nullptr;
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        if (lastArrowEndItem == nullptr) return;
        QPointF endPos = mapToScene(event->pos());
        QList<QGraphicsItem*> items = scene()->items(endPos);
        foreach (QGraphicsItem* item, items) {
            PointItem* endPointItem = dynamic_cast<PointItem*>(item);
            if (endPointItem) {
                endPos = QPointF(endPointItem->x(), endPointItem->y());

                if (event->button() == Qt::LeftButton && lastArrowEndItem->pos() != endPos){
                    undoVector.clear();
                    addArrow(lastArrowEndItem, endPointItem);
                    break;

                } else if (event->button() == Qt::RightButton && lastArrowEndItem->pos() == endPos) {
                    undoVector.clear();
                    addArrow(lastArrowEndItem, endPointItem);
                    break;
                }
            }
        }
    }

    viewport()->update();
    QGraphicsView::mouseReleaseEvent(event);
}

// Снятие выделения если двойной клик на свободную обрасть
void PointView::mouseDoubleClickEvent(QMouseEvent* event) {
    // Получаем координаты точки, на которую наведен курсор
    QPointF scenePos = mapToScene(event->pos());

    // Проверяем, есть ли объекты на этой позиции
    QList<QGraphicsItem*> items = scene()->items(scenePos);

    // Если нет объектов, снимаем выделение
    if (items.isEmpty()) {
        arrowAndPointHighlighter(-1);
        return;
    }
    if (items.size() == 1) { // Не считаем область координатных осей
        arrowAndPointHighlighter(-1);
        return;
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

// Обработка HotKeys
void PointView::keyPressEvent(QKeyEvent* event)
{
    // Выполнение "Undo" при нажатии Ctrl+Z
    if (event->key() == Qt::Key_Z && event->modifiers() == Qt::ControlModifier) {
        undoAction();
    }
    // Выполнение "Redo" при нажатии Ctrl+Y
    else if (event->key() == Qt::Key_Y && event->modifiers() == Qt::ControlModifier) {
        redoAction();
    }
    // Выполнение "Delete" при нажатии Backspace
    else if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
        deleteSelectedArrow();
    }
    else {
        QWidget::keyPressEvent(event);
    }
}


void PointView::mouseMoveEvent(QMouseEvent* event) {

    // При движении мыши получаем координаты точки, на которую наведен курсор
    QPointF scenePos = mapToScene(event->pos());

    // Находим все объекты на этой позиции и выводим информацию о первой точке
    QList<QGraphicsItem*> hoveredItems = scene()->items(scenePos);
    foreach (QGraphicsItem* item, hoveredItems) {
        PointItem* pointItem = dynamic_cast<PointItem*>(item);
        if (pointItem) {
            QString tooltipText = tr("X: %1\nY: %2\nValue: %3").arg(qRound((pointItem->pointData.x) * 10.0) / 10.0).arg(qRound((pointItem->pointData.y) * 10.0) / 10.0).arg(pointItem->pointData.value);

            QToolTip::showText(mapToGlobal(event->pos()), tooltipText, this);
            event->accept();
            return;
        }
    }

    // Если курсор не наведен на точку, скрываем подсказку
    QToolTip::hideText();
    QGraphicsView::mouseMoveEvent(event);
}


void PointView::wheelEvent(QWheelEvent* event) {
    qreal numDegrees = event->angleDelta().y() / 8.0;
    qreal numSteps = numDegrees / 15.0;

    qreal scaleFactor = pow(1.03, numSteps);

    if (scaleFactor < 1 && currentScale <= maxCurrentScale) return;
    if (scaleFactor > 1 && currentScale * scaleFactor > 2.0) return;


    scale(scaleFactor, scaleFactor);
    currentScale *= scaleFactor;

    updatePiontAndArrowSize();

    viewport()->update();
    event->accept();
}

// Изменение размеров объектов на сцене
void PointView::updatePiontAndArrowSize() {
    foreach (QGraphicsItem* item, scene()->items()) {
        PointItem* pointItem = dynamic_cast<PointItem*>(item);
        ArrowItem* arrowItem = dynamic_cast<ArrowItem*>(item);

        if (pointItem) pointItem->setPointSize(10 / currentScale);
        if (arrowItem) arrowItem->setScale(currentScale);
//        if (coordinateAxes) coordinateAxes->setScale(currentScale);

    }
}


void PointView::deleteSelectedArrow() {
    if (selectedArrowItem == nullptr || selectedArrowItem->index >= arrowItems.size())
        return;

    int confirmResult = QMessageBox::question(this->parentWidget(), tr("Подтверждение"), tr("Вы уверены, что хотите удалить выбранную стрелку?"
                                                                                                         "\nВсе последующие так же будут удалены."), QMessageBox::Yes | QMessageBox::No);

    if (confirmResult == QMessageBox::Yes) {

        int indexToDelete = selectedArrowItem->index;

        // Удаляем последующие стрелки (если они есть)
        while (indexToDelete < arrowItems.size()) {
            ArrowItem* subsequentArrow = arrowItems.takeLast();
            deleteArrow(subsequentArrow);
            delete subsequentArrow;
        }


        if (!arrowItems.isEmpty()) {
            arrowAndPointHighlighter(arrowItems.last()->index);
            lastArrowEndItem = arrowItems.last()->endPointItem;
        } else {
            arrowAndPointHighlighter(-1);
            lastArrowEndItem = nullptr;
        }

    }

    viewport()->update();
}


// Удаление последней добавленной стрелки
void PointView::undoAction() {
    if (!arrowItems.isEmpty()) {
        ArrowItem* lastDeletedArrow = arrowItems.takeLast();
        deleteArrow(lastDeletedArrow);
        delete lastDeletedArrow;

        if (!arrowItems.isEmpty()) {
            arrowAndPointHighlighter(arrowItems.last()->index);
            lastArrowEndItem = arrowItems.last()->endPointItem;
        } else {
            arrowAndPointHighlighter(-1);
            lastArrowEndItem = nullptr;
        }
    }
}

// Восстановление последней удаленной стрелки
void PointView::redoAction() {
    if (!undoVector.isEmpty()) {
        QPair<PointItem*, PointItem*> restoredArrowPoints = undoVector.takeFirst();
        addArrow(restoredArrowPoints.first, restoredArrowPoints.second);
//        if (!arrowItems.isEmpty()) lastArrowEndItem = arrowItems.last()->endPointItem;
    }
}

// Добавление стрелок по координатам
QPair<ResultCode, int> PointView::addArrowsByXY(QVector<QPointF> &coordinates) {

    if (lastArrowEndItem && !coordinates.isEmpty()) {
        if (lastArrowEndItem->pos() != QPointF(coordinates.first().x() * 100, coordinates.first().y() * (-100))) {
            return QPair(ResultCode::EndStartPointError, coordinates.indexOf(coordinates.first()));
        }
    }

    if (coordinates.size() < 2) {
        return QPair(ResultCode::NeedAtLeastTwoValues, -1);
    }

    QList<PointItem*> pointsToAddArrows = QList<PointItem*>();
    foreach (QPointF coordinate, coordinates) {
        // Поиск точки с соответствующими координатами
        PointItem* foundPoint = nullptr;
        foreach (PointItem* pointItem, pointItems) {
            double posX = (qRound(static_cast<qreal>(pointItem->pointData.x) * 10));
            double posY = (qRound(static_cast<qreal>(pointItem->pointData.y) * 10));
            posX /= 10;
            posY /= 10;
            if (qFuzzyCompare(posX, coordinate.x()) && qFuzzyCompare(posY, coordinate.y())) {
                foundPoint = pointItem;
                break;
            }
        }
        if (foundPoint) {
            pointsToAddArrows.append(foundPoint);
        } else {
            return QPair(ResultCode::NoPointFound, coordinates.indexOf(coordinate));
        }
    }

    if (pointsToAddArrows.size() < 2) {
        return QPair(ResultCode::NotEnoughValidPointsFound, -1);
    }


    for (int i = 0; i < pointsToAddArrows.size() - 1; ++i) {
        addArrow(pointsToAddArrows[i], pointsToAddArrows[i + 1]);
    }
    return QPair(ResultCode::Success, -1);
}


// Добавление стрелок по Value
QPair<ResultCode, int> PointView::addArrowsByValues(QVector<QString> &values) {

    foreach (PointItem* pointItem, pointItems) {
        if (pointItem->pointData.value == values.first()) {
            if (lastArrowEndItem && lastArrowEndItem != pointItem) {
                return QPair(ResultCode::EndStartPointError, values.indexOf(values.first()));
            }
            break;
        }
    }


    if (values.size() < 2) {
        return QPair(ResultCode::NeedAtLeastTwoValues, -1);
    }

    QVector<PointItem*> pointsToAddArrows;
    foreach (const QString& value, values) {
        // Поиск точки с соответствующим значением
        PointItem* foundPoint = nullptr;
        foreach (PointItem* pointItem, pointItems) {
            if (pointItem->pointData.value == value) {
                foundPoint = pointItem;
                break;
            }
        }
        if (foundPoint) {
            pointsToAddArrows.append(foundPoint);
        } else {
            return QPair(ResultCode::NoPointFound, values.indexOf(value));
        }
    }

    if (pointsToAddArrows.size() < 2) {
        return QPair(ResultCode::NotEnoughValidPointsFound, -1);
    }



    for (int i = 0; i < pointsToAddArrows.size() - 1; ++i) {
        addArrow(pointsToAddArrows[i], pointsToAddArrows[i + 1]);
    }

    return QPair(ResultCode::Success, -1);

}

// Возвращает все актуальные точки
QVector<Point> PointView::takePoints() {
    QVector<Point> points;
    foreach (QGraphicsItem* item, scene()->items()) {
        PointItem* pointItem = dynamic_cast<PointItem*>(item);
        if (pointItem) {
            points.append(pointItem->pointData);
        }

    }
    return points;
}

// Возвращает все актуальные соединённые точки
QVector<Point> PointView::takeConnectedPoints() {
    QVector<Point> points;
    if (!arrowItems.isEmpty()) points.append(arrowItems.first()->startPointItem->pointData);
    foreach (ArrowItem* arrowItem, arrowItems) {
        points.append(arrowItem->endPointItem->pointData);
    }
    return points;
}


void PointView::spinBoxChanged(int arg1) {
    arrowAndPointHighlighter(arg1 - 1);
}


// Метод добавления стрелки
void PointView::addArrow(PointItem* startPointItem, PointItem* endPointItem) {

    QPair<QPointF, QPointF> arrowPos1(startPointItem->pos(), endPointItem->pos());
    QPair<QPointF, QPointF> arrowPos2(endPointItem->pos(), startPointItem->pos());

    int count1 = arrowCountMap.value(arrowPos1) + 1;
    int count2 = arrowCountMap.value(arrowPos2) + 1;

    int arrowCount = qMax(count1, count2) + 1;
    arrowCountMap[arrowPos1] = arrowCount; // Считаем количество стрелок с такими же и обратными координатами
    arrowCountMap[arrowPos2] = arrowCount;
    ArrowItem* arrowItem = new ArrowItem(startPointItem->pos(), endPointItem->pos());
    arrowItem->startPointItem = startPointItem;
    arrowItem->endPointItem = endPointItem;
    arrowItems.append(arrowItem);
    arrowItem->index = arrowItems.size() - 1;
    connect(arrowItem, &ArrowItem::arrowItemDoubleClicked, this, &PointView::arrowAndPointHighlighter);
    arrowItem->arrowCount = arrowCount;
    scene()->addItem(arrowItem);
    lastArrowEndItem = endPointItem;
    arrowItem->setScale(currentScale);
    spinBox->setMaximum(arrowItems.size());
    arrowAndPointHighlighter(arrowItem->index);
    updateLineEdit();
    viewport()->update();

}

void PointView::deleteArrow(ArrowItem* arrow) {

    undoVector.prepend(QPair<PointItem*, PointItem*>(arrow->startPointItem, arrow->endPointItem));


    QPointF startPos = arrow->startPointItem->pos();
    QPointF endPos = arrow->endPointItem->pos();
    QPair<QPointF, QPointF> arrowPos1(startPos, endPos);
    QPair<QPointF, QPointF> arrowPos2(endPos, startPos);

    if (arrow->startPointItem == arrow->endPointItem && arrowCountMap[arrowPos1]){
        arrowCountMap[arrowPos1] -= 1;
    } else if (arrow->startPointItem != arrow->endPointItem && arrowCountMap[arrowPos1] & arrowCountMap[arrowPos2]) {
        arrowCountMap[arrowPos1] -= 1;
        arrowCountMap[arrowPos2] -= 1;
    }
    updateLineEdit();
}

void PointView::updateLineEdit() {

    QVector<Point> connectedPoints = takeConnectedPoints();
    QString pointsValues;

    foreach (Point point, connectedPoints) {
        pointsValues += point.value + " ";
    }

    lineEdit->setText(pointsValues);
}

// Метод для проверки ограничений Value точек
bool PointView::checkPointValues(const QVector<Point>& points) {
    int maxSize = static_cast<int>(log2(points.size())) + 1;
    for (const Point& point : points) {
        if (point.value.isEmpty() || point.value.contains(QRegExp("[^01]")) || point.value.length() > maxSize) {
            return false;
        }
    }
    return true;
}
