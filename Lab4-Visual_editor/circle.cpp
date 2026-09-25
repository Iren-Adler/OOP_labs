#include "circle.h"
#include <QBrush>
#include <QPen>

Circle::Circle(const QPoint& center, int radius) : Shape(center), radius_(radius) {}

bool Circle::contains(const QPoint& point) const {
    int dx = point.x() - position_.x();
    int dy = point.y() - position_.y();
    return (dx*dx + dy*dy) <= (radius_*radius_);
}

void Circle::move(int dx, int dy, const QRect& bounds)
{
    if (canMove(dx, dy, bounds)) {
        position_ += QPoint(dx, dy);
    }
}


void Circle::resize(int delta, const QRect& bounds)
{
    int newRadius = radius_ + delta;
    if (newRadius >= 10) {
        QRect newRect(position_.x() - newRadius,
                      position_.y() - newRadius,
                      newRadius * 2,
                      newRadius * 2);

        if (bounds.contains(newRect)) {
            radius_ = newRadius;
        }
    }
}


void Circle::draw(QPainter& painter, bool isSelected) const {
    painter.setBrush(QBrush(color_));

    if (isSelected) {
        painter.setPen(QPen(Qt::red, 2));
    } else {
        painter.setPen(QPen(Qt::black, 1));
    }
    painter.drawEllipse(position_, radius_, radius_);
}

QRect Circle::getBoundingRect() const
{
    return QRect(position_.x() - radius_,
                 position_.y() - radius_,
                 radius_ * 2,
                 radius_ * 2);
}
