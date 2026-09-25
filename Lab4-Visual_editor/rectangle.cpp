#include "rectangle.h"
#include <QBrush>
#include <QPen>

Rectangle::Rectangle(const QPoint& topLeft, int width, int height)
    : Shape(topLeft)
    , width_(width)
    , height_(height)
{
}

bool Rectangle::contains(const QPoint& point) const
{
    QRect rect(position_.x(), position_.y(), width_, height_);
    return rect.contains(point);
}

void Rectangle::draw(QPainter& painter, bool isSelected) const
{
    painter.setBrush(QBrush(color_));


    if (isSelected) {
        painter.setPen(QPen(Qt::red, 2));
    } else {
        painter.setPen(QPen(Qt::black, 1));
    }

    painter.drawRect(position_.x(), position_.y(), width_, height_);
}

void Rectangle::move(int dx, int dy, const QRect& bounds)
{
    if (canMove(dx, dy, bounds)) {
        position_ += QPoint(dx, dy);
    }
}

void Rectangle::resize(int delta, const QRect& bounds)
{
    int newWidth = width_ + delta;
    int newHeight = height_ + delta;

    QRect newRect(position_.x(), position_.y(), newWidth, newHeight);
    if (bounds.contains(newRect)) {
        width_ = newWidth;
        height_ = newHeight;
    }
}

QRect Rectangle::getBoundingRect() const
{
    return QRect(position_.x(), position_.y(), width_, height_);
}
