#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawingWidget_ = new DrawingWidget(this);
    drawingWidget_->setContainer(&container_);

    setCentralWidget(drawingWidget_);
}

MainWindow::~MainWindow()
{
    delete ui;
}
