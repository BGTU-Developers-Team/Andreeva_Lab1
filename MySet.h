#ifndef ANDREEVA_MYSET_H
#define ANDREEVA_MYSET_H

#include <iostream>
#include <vector>

using namespace std;

class MySet {
private:
    vector<int> elements; // Переменная для хранения элементов множества
    int length; // переменная для хранения длины множества

    int getMin(); // находит минимальное значение в множестве
    int getMax(); // находит максимальное значение в множестве

public:
    MySet(); // классический конструктор
    MySet(int min, int max); // конструктор создающий множество от min до max включительно

    void unitWith(const MySet &set); // объединяет текущее множество с переданным
    void crossWith(const MySet &set); // пересекает текущее мнржество с переданным
    void addElement(const int &element); // добавляет элемент в множество
    bool contains(const int &element); // проверяет, есть ли переданный элемент во множестве
    void diffTo(const MySet &set); // находит разность текущее множества с переданым

    void drawTable(); // выводит в консоль бинарную карту множества
};

#endif //ANDREEVA_MYSET_H
