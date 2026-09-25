#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>


class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);


    void clear() { m_draw = false; update(); }

protected:

    void paintEvent(QPaintEvent *event) override;


    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    bool m_draw = false;  // рисовать ли круг
    int m_x = 50;
    int m_y = 50;
};

#endif
