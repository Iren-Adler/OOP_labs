#include "ellipse.h"
#include <QBrush>
#include <QPen>
#include <QPainterPath>

Ellipse::Ellipse(const QPoint& center, int radiusX, int radiusY)
    : Shape(center)
    , radiusX_(radiusX)
    , radiusY_(radiusY)
{
}

bool Ellipse::contains(const QPoint& point) const
{
    // Уравнение эллипса: (x - h)^2 / a^2 + (y - k)^2 / b^2 <= 1
    int dx = point.x() - position_.x();
    int dy = point.y() - position_.y();

    double a = radiusX_;
    double b = radiusY_;

    return (dx * dx) / (a * a) + (dy * dy) / (b * b) <= 1.0;
}

void Ellipse::draw(QPainter& painter, bool isSelected) const
{
    painter.setBrush(QBrush(color_));

    if (isSelected) {
        painter.setPen(QPen(Qt::red, 2));
    } else {
        painter.setPen(QPen(Qt::black, 1));
    }

    // Рисуем эллипс по bounding rect
    painter.drawEllipse(position_.x() - radiusX_,
                        position_.y() - radiusY_,
                        radiusX_ * 2,
                        radiusY_ * 2);
}

void Ellipse::move(int dx, int dy, const QRect& bounds)
{
    if (canMove(dx, dy, bounds)) {
        position_ += QPoint(dx, dy);
    }
}

void Ellipse::resize(int delta, const QRect& bounds)
{
    int newRadiusX = radiusX_ + delta;
    int newRadiusY = radiusY_ + delta;

    if (newRadiusX < 15 || newRadiusY < 10) return;

    QRect newRect(position_.x() - newRadiusX,
                  position_.y() - newRadiusY,
                  newRadiusX * 2,
                  newRadiusY * 2);

    if (bounds.contains(newRect)) {
        radiusX_ = newRadiusX;
        radiusY_ = newRadiusY;
    }
}

QRect Ellipse::getBoundingRect() const
{
    return QRect(position_.x() - radiusX_,
                 position_.y() - radiusY_,
                 radiusX_ * 2,
                 radiusY_ * 2);
}
