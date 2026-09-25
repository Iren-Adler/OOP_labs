#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    counter = 0;


    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);

    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::exitApp);
    connect(ui->action_clear, &QAction::triggered, this, &MainWindow::clearLog);
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAbout);

    timer->start(1000);

    connect(ui->radioButtonMasha, &QRadioButton::toggled, this, &MainWindow::onRadioToggled);
    connect(ui->radioButtonMisha, &QRadioButton::toggled, this, &MainWindow::onRadioToggled);
    connect(ui->radioButtonSasha, &QRadioButton::toggled, this, &MainWindow::onRadioToggled);

    groupBoxWeather = new QButtonGroup(this);

    groupBoxWeather->addButton(ui->radioButtonRain, 1);
    groupBoxWeather->addButton(ui->radioButtonSnow, 2);
    groupBoxWeather->addButton(ui->radioButtonSun, 3);

    connect(groupBoxWeather, &QButtonGroup::idClicked, this, &MainWindow::onWeatherClicked);

    this->password = {1, 2, 3, 4};

    connect(ui->spinBox, &QSpinBox::valueChanged, this, &MainWindow::on_any_spinbox_changed);
    connect(ui->spinBox_2, &QSpinBox::valueChanged, this, &MainWindow::on_any_spinbox_changed);
    connect(ui->spinBox_3, &QSpinBox::valueChanged, this, &MainWindow::on_any_spinbox_changed);
    connect(ui->spinBox_4, &QSpinBox::valueChanged, this, &MainWindow::on_any_spinbox_changed);

    connect(ui->pushButton_sender1, &QPushButton::clicked, this, &MainWindow::on_any_Button_clicked);
    connect(ui->pushButton_sender2, &QPushButton::clicked, this, &MainWindow::on_any_Button_clicked);
    connect(ui->pushButton_sender3, &QPushButton::clicked, this, &MainWindow::on_any_Button_clicked);

    setMouseTracking(true);

    drawingWidget = new DrawingWidget(this);
    drawingWidget->setGeometry(300, 300, 250, 250);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText("Кнопка нажата!");
}


void MainWindow::on_checkBox_toggled(bool checked)
{
    ui->pushButton->setEnabled(checked);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString text = ui->comboBox->currentText();
    ui->labelForComboBox->setEnabled(true);
    ui->labelForComboBox->setText("Выбрано: " + text + "!");

    qDebug() << "Текст из комбобокса:" << text;
}

void MainWindow::onTimerTimeout()
{
    counter++;
    this->setWindowTitle("Счетчик:" + QString::number(counter));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //QMainWindow::resizeEvent(event); //Вызываем базовый класс
    this->setWindowTitle("Размер:" + QString::number(this->width()) + "x" + QString::number(this->height()));
}

void MainWindow::exitApp()
{

    this->close();
}

void MainWindow::clearLog()
{
    this->statusBar()->showMessage("Очищено", 2000);
}

void MainWindow::showAbout()
{
    // Показать информацию
    this->statusBar()->showMessage("Лабораторная работа №1", 3000);
}



void MainWindow::on_radioButton_r_toggled(bool checked)
{
    if (checked) {
        ui->label_color_simple->setText("Выбран красный!");
        ui->label_color_simple->setStyleSheet("color: red;");
    }
}


void MainWindow::on_radioButton_g_toggled(bool checked)
{
    if (checked) {
        ui->label_color_simple->setText("Выбран зеленый!");
        ui->label_color_simple->setStyleSheet("color: green;");
    }
}



void MainWindow::on_radioButton_b_toggled(bool checked)
{
    if (checked) {
        ui->label_color_simple->setText("Выбран синий!");
        ui->label_color_simple->setStyleSheet("color: blue;");
    }
}


void MainWindow::onRadioToggled()
{
    QRadioButton *radio = qobject_cast<QRadioButton*>(sender());


    if (radio == ui->radioButtonMasha){
        ui->textName->setText("Напортачила Маша");
    } else if (radio == ui->radioButtonMisha){
        ui->textName->setText("Напортачил Миша");
    } else if (radio == ui->radioButtonSasha){
        ui->textName->setText("Напортачил Саша");
    }
}


void MainWindow::onWeatherClicked(int id)
{
    switch(id) {
    case 1:
        ui->lineEditPogoda->setText(ui->radioButtonRain->text());
        break;
    case 2:
        ui->lineEditPogoda->setText(ui->radioButtonSnow->text());
        break;
    case 3:
        ui->lineEditPogoda->setText(ui->radioButtonSun->text());
        break;

    }

}



void MainWindow::on_horizontalSliderPrBar_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}


void  MainWindow::on_any_spinbox_changed()
{
    int val1 = ui->spinBox->value();
    int val2 = ui->spinBox_2->value();
    int val3 = ui->spinBox_3->value();
    int val4 = ui->spinBox_4->value();

    if (val1 == password[0] && val2 == password[1] && val3 == password[2] && val4 == password[3] ) {
        ui->password_label->setText("Успешно!");
        ui->password_label->setStyleSheet("color: green;");
    } else {
        ui->password_label->setText("Пароль неверен!");
        ui->password_label->setStyleSheet("color: red;");
    }

}


void MainWindow::on_any_Button_clicked()
{
    ui->pushButton_sender1->setStyleSheet("");
    ui->pushButton_sender2->setStyleSheet("");
    ui->pushButton_sender3->setStyleSheet("");

    QPushButton *colorButton = qobject_cast<QPushButton*>(sender());
    if (colorButton == ui->pushButton_sender1) {
        ui->pushButton_sender1->setStyleSheet("color: green");
        statusBar()->showMessage("Была нажата зеленая кнопка!");
    }

    if (colorButton == ui->pushButton_sender2) {
        ui->pushButton_sender2->setStyleSheet("color: blue");
        statusBar()->showMessage("Была нажата синяя кнопка!");
    }
    if (colorButton == ui->pushButton_sender3) {
        ui->pushButton_sender3->setStyleSheet("color: red");
        statusBar()->showMessage("Была нажата красная кнопка!");
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();

    QPushButton *dyn_btn = new QPushButton(this);

    dyn_btn->setText("Новая кнопка!");
    dyn_btn->setGeometry(x, y, 100, 30);

    connect(dyn_btn, &QPushButton::clicked, this, &MainWindow::onDynamicButtonClicked);
    dyn_btn->show();


    QMainWindow::mousePressEvent(event);



}
// QComboBox: currentIndex, currentText, items
// QListWidget: currentItem, items
// QSlider: value, minimum, maximum
// QProgressBar: value, minimum, maximum
// QSpinBox: value
// QCheckBox: checked (отмечен/не отмечен), text
// QRadioButton: checked, text


void MainWindow::onDynamicButtonClicked(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    btn->setStyleSheet("background-color: green");
}


void MainWindow::mouseMoveEvent(QMouseEvent *event){
    int x = event->pos().rx();
    int y = event->pos().ry();

    ui->lcdNumber_koordx->display(x);
    ui->lcdNumber_koordy->display(y);
    QMainWindow::mouseMoveEvent(event);


}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1) {
        ui->statusbar->showMessage("Был нажат F1");

    }
    if (event->key() == Qt::Key_Return) {
        ui->statusbar->showMessage("Был нажат Enter");


    }
}
