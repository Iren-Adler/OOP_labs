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

    void setContainer(Container* container); //из mainwindow

    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    Container* container_;
    // Вспомогательные методы
    void handleSelection(const QPoint& pos, bool ctrlPressed);
};

#endif // DRAWINGWIDGET_H
