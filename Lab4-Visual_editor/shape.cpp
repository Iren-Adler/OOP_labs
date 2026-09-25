#include "shape.h"


bool Shape::canMove(int dx, int dy, const QRect& bounds) const
{
    QRect currentRect = getBoundingRect();
    QRect newRect = currentRect.translated(dx, dy);
    return bounds.contains(newRect);
}
