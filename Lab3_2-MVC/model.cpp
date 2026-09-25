#include "model.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Model::Model(QObject *parent)
    : QObject(parent)
    , settings_("Ir", "MVC")


{ loadValues();
}


int Model::clamp(int value, int min, int max) const
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}


void Model::setAllValues(int newA, int newB, int newC)
{
    if (m_a == newA && m_b == newB && m_c == newC)
        return;

    m_a = newA;
    m_b = newB;
    m_c = newC;

    emit dataChanged();
}

void Model::setA(int value)
{
    int newA = clamp(value, 0, 100);
    int newB = m_b;
    int newC = m_c;

    // Если новое A больше B, поднимаем B
    if (newA > newB) newB = newA;
    // Если новое A больше C, поднимаем C
    if (newA > newC) newC = newA;
    // Если после этого B оказался больше
    if (newB > newC) newC = newB;

    setAllValues(newA, newB, newC);
    saveValues();
}

void Model::setB(int value)
{
    int newB = clamp(value, 0, 100);

    if (newB < m_a) {
        newB = m_a;
    } if (newB > m_c){
        newB = m_c;
    }

    setAllValues(m_a, newB, m_c);
    saveValues();

}

void Model::setC(int value)
{
    int newC = clamp(value, 0, 100);
    int newA = m_a;
    int newB = m_b;

    // Если новое C меньше B, опускаем B
    if (newC < newB) newB = newC;
    // Если новое C меньше A, опускаем A
    if (newC < newA) newA = newC;
    // Если после этого B оказался меньше A
    if (newB < newA) newB = newA;

    setAllValues(newA, newB, newC);
    saveValues();
}


void Model::saveValues(){
    settings_.setValue("a", m_a);
    settings_.setValue("b", m_b);
    settings_.setValue("c", m_c);

}


void Model::loadValues() {
    int newA, newB, newC;
    newA = settings_.value("a", 0).toInt();
    newB = settings_.value("b", 0).toInt();
    newC =  settings_.value("c", 0).toInt();
    if (newB < newA) {
        newB = newA;
    }

    // Коррекция загруженных значений, чтобы они удовлетворяли A ≤ B ≤ C
    if (newA > newB) newB = newA;
    if (newB > newC) newB = newC;
    if (newA > newC) newC = newA;


    setAllValues(newA, newB, newC);
}

