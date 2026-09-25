#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_updating(false)
{
    ui->setupUi(this);


    m_model = new Model(this);


    connect(m_model, &Model::dataChanged, this, &MainWindow::updateFromModel);

    connect(ui->spinBoxA, &QSpinBox::valueChanged, this, &MainWindow::onAChanged);
    connect(ui->horizontalSliderA, &QSlider::valueChanged, this, &MainWindow::onAChanged);
    connect(ui->lineEditA, &QLineEdit::textEdited, this, &MainWindow::onATextEdited);
    connect(ui->lineEditA, &QLineEdit::editingFinished, this, &MainWindow::onAFocusLost);


    connect(ui->spinBoxB, &QSpinBox::valueChanged, this, &MainWindow::onBChanged);
    connect(ui->horizontalSliderB, &QSlider::valueChanged, this, &MainWindow::onBChanged);
    connect(ui->lineEditB, &QLineEdit::textEdited, this, &MainWindow::onBTextEdited);
    connect(ui->lineEditB, &QLineEdit::editingFinished, this, &MainWindow::onBFocusLost);


    connect(ui->spinBoxC, &QSpinBox::valueChanged, this, &MainWindow::onCChanged);
    connect(ui->horizontalSliderC, &QSlider::valueChanged, this, &MainWindow::onCChanged);
    connect(ui->lineEditC, &QLineEdit::textEdited, this, &MainWindow::onCTextEdited);
    connect(ui->lineEditC, &QLineEdit::editingFinished, this, &MainWindow::onCFocusLost);




    connect(ui->horizontalSliderA, &QSlider::sliderReleased, this, &MainWindow::onSliderAFocusLost);
    connect(ui->horizontalSliderB, &QSlider::sliderReleased, this, &MainWindow::onSliderBFocusLost);
    connect(ui->horizontalSliderC, &QSlider::sliderReleased, this, &MainWindow::onSliderCFocusLost);

    // Подключаем сигналы потери фокуса для спинбоксов
    connect(ui->spinBoxA, &QSpinBox::editingFinished, this, &MainWindow::onSpinBoxAFocusLost);
    connect(ui->spinBoxB, &QSpinBox::editingFinished, this, &MainWindow::onSpinBoxBFocusLost);
    connect(ui->spinBoxC, &QSpinBox::editingFinished, this, &MainWindow::onSpinBoxCFocusLost);

    updateFromModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    m_model->saveValues();
    event->accept();
}

int MainWindow::getIntFromText(const QString& text) const
{
    bool ok;
    int value = text.toInt(&ok);
    if (!ok)
        return -1;
    return value;
}



void MainWindow::updateFromModel()
{
    if (m_updating) return;
    m_updating = true;


    int a = m_model->getA();
    ui->spinBoxA->setValue(a);
    ui->horizontalSliderA->setValue(a);
    ui->lineEditA->setText(QString::number(a));

    int b = m_model->getB();
    ui->spinBoxB->setValue(b);
    ui->horizontalSliderB->setValue(b);
    ui->lineEditB->setText(QString::number(b));

    int c = m_model->getC();
    ui->spinBoxC->setValue(c);
    ui->horizontalSliderC->setValue(c);
    ui->lineEditC->setText(QString::number(c));

    m_updating = false;
}



// Контроллер для A



void MainWindow::onAChanged(int value)
{
    if (m_updating) return;
    m_model->setA(value);
}

void MainWindow::onATextEdited(const QString &text)
{
    if (m_updating) return;
    int value = getIntFromText(text);
    if (value >= 0 && value <= 100)
    {
        m_model->setA(value);
    }
}

void MainWindow::onAFocusLost()
{
    if (m_updating) return;
    // При потере фокуса корректируем значение, если оно некорректное
    int currentValue = m_model->getA();
    ui->lineEditA->setText(QString::number(currentValue));
}



// Контроллер для B



void MainWindow::onBChanged(int value)
{
    if (m_updating) return;
    m_model->setB(value);
}

void MainWindow::onBTextEdited(const QString &text)
{
    if (m_updating) return;
    int value = getIntFromText(text);
    if (value >= 0 && value <= 100)
    {
        m_model->setB(value);
    }
}

void MainWindow::onBFocusLost()
{
    if (m_updating) return;
    int currentValue = m_model->getB();
    ui->lineEditB->setText(QString::number(currentValue));
}



// Контроллер для C



void MainWindow::onCChanged(int value)
{
    if (m_updating) return;
    m_model->setC(value);
}

void MainWindow::onCTextEdited(const QString &text)
{
    if (m_updating) return;
    int value = getIntFromText(text);
    if (value >= 0 && value <= 100)
    {
        m_model->setC(value);
    }
}

void MainWindow::onCFocusLost()
{
    if (m_updating) return;

    int currentValue = m_model->getC();
    ui->lineEditC->setText(QString::number(currentValue));
}



// Обработчики для слайдера A
void MainWindow::onSliderAFocusLost()
{
    if (m_updating) return;
    int currentValue = m_model->getA();
    ui->horizontalSliderA->setValue(currentValue);

    /*   int currentValue = ui->horizontalSliderA->value();
    int correctedValue = qBound(0, currentValue, 99); // или до m_model->getC()

    if (currentValue != correctedValue) {
        m_model->setA(correctedValue);
    } */
}

// Обработчики для слайдера B
void MainWindow::onSliderBFocusLost()
{
    if (m_updating) return;
    int currentValue = m_model->getB();
    ui->horizontalSliderB->setValue(currentValue);

}

// Обработчики для слайдера C
void MainWindow::onSliderCFocusLost()
{
    if (m_updating) return;
    int currentValue = m_model->getC();
    ui->horizontalSliderC->setValue(currentValue);

}

// Обработчики для спинбокса A
void MainWindow::onSpinBoxAFocusLost()
{
   if (m_updating) return;
   int currentValue = m_model->getA();
   ui->spinBoxA->setValue(currentValue);


}

// Обработчики для спинбокса B
void MainWindow::onSpinBoxBFocusLost()
{
    if (m_updating) return;
    int currentValue = m_model->getB();
    ui->spinBoxB->setValue(currentValue);

}

// Обработчики для спинбокса C
void MainWindow::onSpinBoxCFocusLost()
{
    if (m_updating) return;
    int currentValue = m_model->getC();
    ui->spinBoxC->setValue(currentValue);

}
