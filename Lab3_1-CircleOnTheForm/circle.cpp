  #include "circle.h"
#include <QBrush>
#include <QPen>

Circle::Circle(const QPoint& center) : center_(center) {}

bool Circle::contains(const QPoint& point) const {
    int x = point.x() - center_.x();
    int y = point.y() - center_.y();
    return (x*x + y*y) <= (RADIUS*RADIUS);
}


void Circle::draw(QPainter& painter, bool isSelected) const {
    QBrush brush(isSelected ? Qt::blue : Qt::red);
    QPen pen(Qt::black, 2);

    painter.setBrush(brush);
    painter.setPen(pen);

    painter.drawEllipse(center_, RADIUS, RADIUS);
}

