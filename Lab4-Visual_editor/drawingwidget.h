#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H


#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>
#include "container.h"


class DrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget* parent = nullptr);
    enum class Mode {
        Circle,
        Rectangle,
        Ellipse
    };

    void setContainer(Container* container); //из mainwindow

    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void setDrawMode(Mode mode) { drawMode_ = mode; }
    void setCurrentColor(const QColor& color) { currentColor_ = color; }

private:
    Mode drawMode_ = Mode::Circle;
    QColor currentColor_ = Qt::blue;

    Container* container_;
    // вспомогательные методы
    void handleSelection(const QPoint& pos, bool ctrlPressed);
};

#endif // DRAWINGWIDGET_H
