#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(const QPoint& topLeft, int width = 80, int height = 60);


    bool contains(const QPoint& point) const override;
    void draw(QPainter& painter, bool isSelected) const override;
    void move(int dx, int dy, const QRect& bounds) override;
    void resize(int delta, const QRect& bounds) override;
    QRect getBoundingRect() const override;

    // Специфичные методы
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    void setSize(int width, int height) { width_ = width; height_ = height; }

private:
    int width_;
    int height_;
};

#endif // RECTANGLE_H
