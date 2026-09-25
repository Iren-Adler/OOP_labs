// drawingwidget.cpp
#include "drawingwidget.h"
#include <QPainter>
#include <QApplication>

DrawingWidget::DrawingWidget(QWidget* parent)
    : QWidget(parent)
    , container_(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);
    setMinimumSize(400, 300);
}

void DrawingWidget::setContainer(Container* container)
{
    container_ = container;
}

void DrawingWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) return;
    if (! container_) return;

    QPoint clickPos = event->pos();
    bool ctrlPressed = QApplication::keyboardModifiers() & Qt::ControlModifier;

    //попали ли в какой-нибудь круг
    bool hitCircle = false;
    for (int i = 0; i < container_->getCount(); ++i) {
        Circle* circle = container_->getObject(i);
        if (circle->contains(clickPos)) {
            hitCircle = true;
            break;
        }
    }

    if (!hitCircle) {
        container_->add(new Circle(clickPos));
        update();
    } else {
        handleSelection(clickPos, ctrlPressed);
    }
}

void DrawingWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    if (!container_) return;

    for (int i = 0; i < container_->getCount(); ++i) {
        Circle* circle = container_->getObject(i);
        circle->draw(painter, circle->isSelected());
    }
}

void DrawingWidget::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "keyPressEvent, key:" << event->key();
    if (! container_) return;

    if (event->key() == 16777219) {
        qDebug() << "Delete pressed";
        for (int i = container_->getCount() - 1; i >= 0; --i) {
            Circle* circle = container_->getObject(i);
            if (circle->isSelected()) {
                container_->removeAt(i);
            }
        }
        update();
    }
}

void DrawingWidget::handleSelection(const QPoint& pos, bool ctrlPressed)
{
    if (!container_) return;

    // Если не зажат Ctrl - снимаем выделение со всех
    if (!ctrlPressed) {
        for (int i = 0; i < container_->getCount(); ++i) {
            container_->getObject(i)->setSelected(false);
        }
    }

    // Находим самый верхний круг (идём с конца)
    Circle* topCircle = nullptr;
    for (int i = container_->getCount() - 1; i >= 0; --i) {
        Circle* circle = container_->getObject(i);
        if (circle->contains(pos)) {
            if (ctrlPressed) {
                // Инвертируем выделение
                circle->setSelected(!circle->isSelected());
            } else {
                topCircle = circle;
                break;
            }
        }
    }

    // Выделяем только верхний круг (если без Ctrl)
    if (!ctrlPressed && topCircle) {
        topCircle->setSelected(true);
    }

    update();
}
