#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(const QPoint& center, int radiusX = 50, int radiusY = 35);

    bool contains(const QPoint& point) const override;
    void draw(QPainter& painter, bool isSelected) const override;
    void move(int dx, int dy, const QRect& bounds) override;
    void resize(int delta, const QRect& bounds) override;
    QRect getBoundingRect() const override;

    int getRadiusX() const { return radiusX_; }
    int getRadiusY() const { return radiusY_; }
    void setRadiusX(int rx) { radiusX_ = rx; }
    void setRadiusY(int ry) { radiusY_ = ry; }

private:
    int radiusX_;  // ширина/2
    int radiusY_;  // высота/2
};

#endif // ELLIPSE_H
