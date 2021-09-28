#include <iostream>
#include "MySet.h"

int main() {

    auto ms1 = MySet(-5, 10);
    auto ms2 = MySet(2, 5);

    ms1.diffTo(ms2);
//    ms1.drawTable();
    auto ms3 = MySet(-7, 1);
    auto ms4 = MySet(-1, 7);

//    ms3.crossWith(ms4);
    ms3.unitWith(ms4);
    ms3.addElement(10);
    ms3.drawTable();

    return 0;
}
