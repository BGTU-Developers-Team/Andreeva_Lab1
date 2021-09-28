#include "MySet.h"

MySet::MySet() {
    length = 0;
}

MySet::MySet(int min, int max) {
    length = max - min + 1;
    for (int i = min; i <= max; ++i) {
        elements.push_back(i);
    }
}

void MySet::unitWith(const MySet &set) {
    std::vector<int> temp;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < set.length; ++j) {
            if (elements[i] == set.elements[j]) {
                temp.push_back(elements[i]);
                break;
            }
        }
    }

    elements = temp;
    length = elements.size();
}

void MySet::crossWith(const MySet &set) {
    bool hasFoundSimilar = false;
    for (int i = 0; i < set.length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (set.elements[i] == elements[j]) {
                hasFoundSimilar = true;
                break;
            }
        }

        if (!hasFoundSimilar)
            elements.push_back(set.elements[i]);

        hasFoundSimilar = false;
    }

    length = elements.size();
}

void MySet::addElement(const int &element) {
    for (int i = 0; i < length; ++i) {
        if (elements[i] == element)
            return;
    }

    elements.push_back(element);
    length = elements.size();
}

bool MySet::contains(const int &element) {
    for (int i = 0; i < length; ++i) {
        if (elements[i] == element)
            return true;
    }

    return false;
}

void MySet::diffTo(const MySet &set) {
    std::vector<int> temp;
    bool hasFoundSimilar = false;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < set.length; ++j) {
            if (elements[i] == set.elements[j]) {
                hasFoundSimilar = true;
                break;
            }
        }

        if (!hasFoundSimilar)
            temp.push_back(elements[i]);

        hasFoundSimilar = false;
    }

    elements = temp;
    length = elements.size();
}

int MySet::getMin() {
    int min = elements[0];

    for (int i = 1; i < length; ++i) {
        if (elements[i] < min)
            min = elements[i];
    }

    return min;
}

int MySet::getMax() {
    int max = elements[0];

    for (int i = 1; i < length; ++i) {
        if (elements[i] > max)
            max = elements[i];
    }

    return max;
}

void MySet::drawTable() {
    std::cout << std::endl;
    std::cout << "Бинарная карта\n\n";

    int val;
    int min = getMin();
    int max = getMax();

    for (int i = min; i <= max; ++i) {
        val = contains(i) ? 1 : 0;
        val = val < 0 ? 1 : val;
        cout << i << '\t' << val << endl;
    }

    cout << endl;
}