#ifndef ANDREEVA_MYSET_H
#define ANDREEVA_MYSET_H

#include <iostream>
#include <vector>

using namespace std;

class MySet {
private:
    vector<int> elements;
    int length;

    int getMin();
    int getMax();

public:
    MySet();
    MySet(int min, int max);

    void unitWith(const MySet &set);
    void crossWith(const MySet &set);
    void addElement(const int &element);
    bool contains(const int &element);
    void diffTo(const MySet&set);

    void drawTable();
};

#endif //ANDREEVA_MYSET_H
