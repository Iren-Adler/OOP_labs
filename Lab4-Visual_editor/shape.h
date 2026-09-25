#ifndef SHAPE_H
#define SHAPE_H

#include <QPoint>
#include <QPainter>



class Shape
{
public:

    Shape(const QPoint& position)
        : position_(position)
        , color_(Qt::blue)      // Цвет по умолчанию
        , isselected_(false)
    {
    }

    virtual bool contains(const QPoint& point) const = 0;
    virtual void draw(QPainter& painter, bool isSelected) const = 0;

    QPoint getCPozition() const {return position_;}
    void setCPozition(const QPoint& pos) {position_ = pos;}

    QColor getColor() const {return color_;}
    void setColor(const QColor& color) {color_ = color;}

    virtual void setSelected(bool selected) {isselected_ = selected;}
    virtual bool isSelected() const {return isselected_;}

    virtual void move(int dx, int dy, const QRect& bounds) = 0;
    virtual void resize(int delta, const QRect& bounds) = 0;
    virtual QRect getBoundingRect() const = 0;
    bool canMove(int dx, int dy, const QRect& bounds) const;

protected:
    QPoint position_;
    QColor color_;
    bool isselected_ = false;

};

#endif // SHAPE_H
