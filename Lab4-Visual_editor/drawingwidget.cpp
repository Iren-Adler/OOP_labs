#include "drawingwidget.h"
#include "circle.h"
#include "rectangle.h"
#include "ellipse.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>

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
    if (!container_) return;

    QPoint clickPos = event->pos();
    bool ctrlPressed = QApplication::keyboardModifiers() & Qt::ControlModifier;

    // Проверяем, попали ли в какую-нибудь фигуру
    bool hitShape = false;
    for (int i = 0; i < container_->getCount(); ++i) {
        Shape* shape = container_->getObject(i);
        if (shape->contains(clickPos)) {
            hitShape = true;
            break;
        }
    }

    if (!hitShape) {
        // Создаем новую фигуру с текущим цветом
        if (drawMode_ == Mode::Circle) {
            Circle* circle = new Circle(clickPos, 40);
            circle->setColor(currentColor_);
            container_->add(circle);
            qDebug() << "Created circle at" << clickPos;

        } else if (drawMode_ == Mode::Rectangle){
            QPoint topLeft(clickPos.x() - 40, clickPos.y() - 30);
            Rectangle* rect = new Rectangle(topLeft, 80, 60);
            rect->setColor(currentColor_);
            container_->add(rect);
            qDebug() << "Created rectangle at" << clickPos;
        }
        else if (drawMode_ == Mode::Ellipse) {
            Ellipse* ellipse = new Ellipse(clickPos, 50, 35);
            ellipse->setColor(currentColor_);
            container_->add(ellipse);
            qDebug() << "Created ellipse at" << clickPos;
        }
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
        Shape* shape = container_->getObject(i);
        shape->draw(painter, shape->isSelected());
    }
}

void DrawingWidget::keyPressEvent(QKeyEvent* event)
{
    if (!container_) return;
    int g = event->key();
    qDebug() << g;

    if (event->key() == 16777219) {
        qDebug() << "Delete pressed";
        // Удаляем все выделенные фигуры (ищем с конца)
        for (int i = container_->getCount() - 1; i >= 0; --i) {
            Shape* shape = container_->getObject(i);
            if (shape->isSelected()) {
                container_->removeAt(i);
            }
        }
        update();
    }

    int dx = 0, dy = 0;
    bool movePressed = false;

    if (event->key() == 16777234) {
        dx = -5;
        movePressed = true;
    } else if (event->key() == 16777236) {
        dx = 5;
        movePressed = true;
    } else if (event->key() == 16777235) {
        dy = -5;
        movePressed = true;
    } else if (event->key() ==  16777237) {
        dy = 5;
        movePressed = true;
    }

    if (movePressed) {
        // Получаем границы рабочей области
        QRect bounds = rect();

        // Перемещаем все выделенные фигуры
        for (int i = 0; i < container_->getCount(); ++i) {
            Shape* shape = container_->getObject(i);
            if (shape->isSelected()) {
                shape->move(dx, dy, bounds);
            }
        }
        update();
    }


    if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
        qDebug() << "Resize +";
        for (int i = 0; i < container_->getCount(); ++i) {
            Shape* shape = container_->getObject(i);
            if (shape->isSelected()) {
                shape->resize(5, rect());
            }
        }
        update();
        return;
    }

    if (event->key() == Qt::Key_Minus) {
        qDebug() << "Resize -";
        for (int i = 0; i < container_->getCount(); ++i) {
            Shape* shape = container_->getObject(i);
            if (shape->isSelected()) {
                shape->resize(-5, rect());
            }
        }
        update();
        return;
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

    // Находим самую верхнюю фигуру (идём с конца)
    Shape* topShape = nullptr;
    for (int i = container_->getCount() - 1; i >= 0; --i) {
        Shape* shape = container_->getObject(i);
        if (shape->contains(pos)) {
            if (ctrlPressed) {
                // Инвертируем выделение
                shape->setSelected(!shape->isSelected());
            } else {
                topShape = shape;
                break;
            }
        }
    }

    // Выделяем только верхнюю фигуру (если без Ctrl)
    if (!ctrlPressed && topShape) {
        topShape->setSelected(true);
    }

    update();
}
