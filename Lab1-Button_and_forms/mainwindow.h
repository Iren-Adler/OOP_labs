#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QKeyEvent>
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

private slots:
    void on_pushButton_clicked();

    void on_checkBox_toggled(bool checked);

    void on_comboBox_currentIndexChanged(int index);

    void onTimerTimeout();

    void exitApp();

    void clearLog();

    void showAbout();

    void resizeEvent(QResizeEvent *event) override; //пересмореть

    void on_radioButton_r_toggled(bool checked);

    void on_radioButton_g_toggled(bool checked);

    void on_radioButton_b_toggled(bool checked);

    void onRadioToggled();

    void onWeatherClicked(int id);

    void on_horizontalSliderPrBar_valueChanged(int value);

    void on_any_spinbox_changed();

    void on_any_Button_clicked();

    void mousePressEvent(QMouseEvent *event) override;

    void onDynamicButtonClicked();

    void mouseMoveEvent(QMouseEvent * event) override;

    void keyPressEvent(QKeyEvent *event) override;



private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int counter;
    QButtonGroup *groupBoxWeather;
    std::vector<int> password;
    DrawingWidget *drawingWidget;


};
#endif // MAINWINDOW_H
