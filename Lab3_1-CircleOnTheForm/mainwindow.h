#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "container.h"
#include "drawingwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DrawingWidget* drawingWidget_;
    Container  container_;
};
#endif // MAINWINDOW_H
