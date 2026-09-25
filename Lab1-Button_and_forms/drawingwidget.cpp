#include "drawingwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>


DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent)
{

    setMinimumSize(300, 300);

    setStyleSheet("background-color: white;");

    qDebug() << "Виджет создан, жду двойного клика";
}


void DrawingWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    m_x = event->pos().x();
    m_y = event->pos().y();

    m_draw = true;

    update();


    qDebug() << "Двойной клик в точке:" << m_x << m_y;


    QWidget::mouseDoubleClickEvent(event);
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); //инструмент рисования



    painter.drawRect(rect().adjusted(0, 0, -1, -1));


    if (m_draw) {

        painter.setBrush(Qt::red);
        painter.setPen(Qt::darkRed);


        painter.drawEllipse(m_x - 20, m_y - 20, 40, 40);

        painter.setPen(Qt::black);
        painter.drawText(m_x - 20, m_y - 25,
                         QString("(%1, %2)").arg(m_x).arg(m_y));
    }
}
