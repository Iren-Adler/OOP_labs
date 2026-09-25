#ifndef CIRCLE_H
#define CIRCLE_H


#include <QPoint>
#include <QPainter>

class Circle
{
public:
    static const int RADIUS = 40;

    Circle(const QPoint& center);
    bool contains(const QPoint& point) const;
    void draw(QPainter& painter, bool isSelected) const;
    QPoint getCenter() const {return center_;}
    void setSelected(bool selected) {isselected_ = selected;}
    bool isSelected() const {return isselected_;}

private:
    QPoint center_;
    bool isselected_ = false;

};

#endif // CIRCLE_H
