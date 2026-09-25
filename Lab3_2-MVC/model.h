#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QSettings>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);


    int getA() const {return m_a;}
    int getB() const {return m_b;}
    int getC() const {return m_c;}

    void setA (int value);
    void setB (int value);
    void setC (int value);

    void saveValues();
    void loadValues();

signals:
    void dataChanged();


private:
    int m_a = 0;
    int m_b = 0;
    int m_c = 0;

    void setAllValues(int newA, int newB, int newC);

    int clamp(int value, int min, int max) const; //фиксатор

    QSettings settings_;


};

#endif // MODEL_H
