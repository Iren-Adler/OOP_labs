#ifndef CIRCLE_H
#define CIRCLE_H


#include <QPoint>
#include <QPainter>
#include "shape.h"

class Circle : public Shape
{
public:

    Circle(const QPoint& center, int radius_ = 40);

    bool contains(const QPoint& point) const override;
    void draw(QPainter& painter, bool isSelected) const override;
    void move(int dx, int dy, const QRect& bounds) override;
    void resize(int delta, const QRect& bounds) override;
    QRect getBoundingRect() const override;

    QPoint getCenter() const { return position_; }
    int getRadius() const { return radius_; }
    void setRadius(int radius) { radius_ = radius; }


private:
    int radius_;


};

#endif // CIRCLE_H
