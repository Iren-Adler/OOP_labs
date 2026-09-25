#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QColorDialog>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawingWidget_ = new DrawingWidget(this);
    drawingWidget_->setContainer(&container_);

    setCentralWidget(drawingWidget_);
    createToolBar();
    drawingWidget_->setCurrentColor(currentColor_);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createToolBar()
{
    QToolBar* toolBar = addToolBar("Инструменты");
    toolBar->setMovable(false);


    circleAction_ = new QAction("Круг", this);
    circleAction_->setCheckable(true);
    circleAction_->setChecked(true);  // Круг выбран по умолчанию
    connect(circleAction_, &QAction::triggered, this, &MainWindow::setCircleMode);
    toolBar->addAction(circleAction_);


    rectangleAction_ = new QAction("Прямоугольник", this);
    rectangleAction_->setCheckable(true);
    connect(rectangleAction_, &QAction::triggered, this, &MainWindow::setRectangleMode);
    toolBar->addAction(rectangleAction_);



    ellipseAction_ = new QAction("Эллипс", this);
    ellipseAction_->setCheckable(true);
    connect(ellipseAction_, &QAction::triggered, this, &MainWindow::setEllipseMode);
    toolBar->addAction(ellipseAction_);


    toolBar->addSeparator();


    colorAction_ = new QAction("Выбрать цвет", this);
    connect(colorAction_, &QAction::triggered, this, &MainWindow::chooseColor);
    toolBar->addAction(colorAction_);

    // Отображаем текущий цвет
    QLabel* colorLabel = new QLabel("  Цвет: ");
    toolBar->addWidget(colorLabel);
    QWidget* colorIndicator = new QWidget();
    colorIndicator->setFixedSize(20, 20);
    colorIndicator->setStyleSheet(QString("background-color: %1; border: 1px solid black;").arg(currentColor_.name()));
    colorIndicator->setProperty("colorIndicator", true);
    toolBar->addWidget(colorIndicator);

    // Сохраняем указатель на индикатор, чтобы обновлять позже
    colorIndicator->setObjectName("colorIndicator");
}

void MainWindow::setCircleMode()
{
    rectangleAction_->setChecked(false);
    circleAction_->setChecked(true);
    ellipseAction_->setChecked(false);
    drawingWidget_->setDrawMode(DrawingWidget::Mode::Circle);
}

void MainWindow::setRectangleMode()
{
    circleAction_->setChecked(false);
    rectangleAction_->setChecked(true);
    ellipseAction_->setChecked(false);
    drawingWidget_->setDrawMode(DrawingWidget::Mode::Rectangle);
}

void MainWindow::setEllipseMode()
{
    circleAction_->setChecked(false);
    rectangleAction_->setChecked(false);
    ellipseAction_->setChecked(true);
    drawingWidget_->setDrawMode(DrawingWidget::Mode::Ellipse);
}

void MainWindow::chooseColor()
{
    QColor newColor = QColorDialog::getColor(currentColor_, this, "Выберите цвет фигуры");

    if (newColor.isValid()) {
        currentColor_ = newColor;

        // Обновляем цвет в DrawingWidget
        drawingWidget_->setCurrentColor(currentColor_);

        // Обновляем индикатор цвета на панели
        QWidget* colorIndicator = findChild<QWidget*>("colorIndicator");
        if (colorIndicator) {
            colorIndicator->setStyleSheet(QString("background-color: %1; border: 1px solid black;").arg(currentColor_.name()));
        }

        // Если есть выделенные фигуры - меняем их цвет
        for (int i = 0; i < container_.getCount(); ++i) {
            Shape* shape = container_.getObject(i);
            if (shape->isSelected()) {
                shape->setColor(currentColor_);
            }
        }
        drawingWidget_->update();
    }
}

