#include <iostream>
#include "MySet.h"

int main() {

//    auto ms1 = MySet(-5, 10);
//    auto ms2 = MySet(2, 5);
//
//    ms1.diffTo(ms2);
////    ms1.drawTable();
//    auto ms3 = MySet(-7, 1);
//    auto ms4 = MySet(-1, 7);
//    ms3.unitWith(ms4);
//    ms3.crossWith(ms4);
//    ms3.diffTo(ms4);

//    ms3.drawTable();

//    ms3.addElement(10);
//    ms3.drawTable();

//    MySet *msStr = new MySet("[1,2,3,4, -10, 6]"); // экземпляр класса
//    msStr->drawTable();
    //    msStr->drawTable();
//
//    MySet *msStr1 = new MySet(*msStr); // разыменовать = *ukazatel
//    msStr1->drawTable();











    MySet *desires = new MySet();
    desires->addElement(12);
    desires->drawTable();
    auto newDesires = new MySet(*desires);
    auto mySet = new MySet(-5, 5);
    newDesires->crossWith(*mySet);
    newDesires->drawTable();


    return 0;
}
