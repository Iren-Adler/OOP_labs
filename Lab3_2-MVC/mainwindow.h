// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Слот для обновления всех компонентов из модели
    void updateFromModel();

    // Слоты-контроллеры: реагируют на действия пользователя
    void onAChanged(int value);
    void onBChanged(int value);
    void onCChanged(int value);

    // Обработка ввода в TextBox
    void onATextEdited(const QString &text);
    void onBTextEdited(const QString &text);
    void onCTextEdited(const QString &text);

    // Обработка потери фокуса TextBox
    void onAFocusLost();
    void onBFocusLost();
    void onCFocusLost();


    // Обработка потери фокуса для слайдеров
    void onSliderAFocusLost();
    void onSliderBFocusLost();
    void onSliderCFocusLost();

    // Обработка потери фокуса для спинбоксов
    void onSpinBoxAFocusLost();
    void onSpinBoxBFocusLost();
    void onSpinBoxCFocusLost();

private:
    Ui::MainWindow *ui;
    Model *m_model;
    bool m_updating;  // Флаг для предотвращения рекурсивных обновлений

    // Вспомогательные методы
    int getIntFromText(const QString& text) const;

};

#endif // MAINWINDOW_H
