#include "MySet.h"

MySet::MySet() {
    length = 0;
}

MySet::MySet(int min, int max) {
    length = max - min + 1; // найдем длину множества
    elements = new int[length];
    for (int i = min; i <= max; ++i) {
        elements[i - min] = i; // сохраняем все значения от min до max
    }
}

MySet::MySet(const MySet &orig) {
    length = orig.length;
    elements = new int[length];
    std::memcpy(elements, orig.elements, sizeof(int) * length);
}

MySet::MySet(const std::string &setStr) {
    length = 0;

    auto errorProtocolMsg = "Ошибка! Строка должна иметь вид: [1,2,3,4,5,10,-10]"; // запишем текст ошибки, чтобы потом его выводить много раз

    if (setStr[0] != '[') // если множество не начинается с [
        throw std::invalid_argument(errorProtocolMsg); // то нужно вызвать исключение


    if (setStr[0] == '[' && setStr.find(']') !=
                            std::string::npos) { // Прежде всего нужно проверить какую строчку нам передали в конструктор: если в этой срочке нет, как минимум, символов { и }, то она уже неправильная и нет смысла её парсить(обрабатывать).
        if (setStr[1] ==
            ']') { // Если второй символ в строчке является }, то она пустая, а кто у нас пустую матрицу создает..? Правильно!
            MySet();
        } else {

            // Если все нормуль, то начием считывать элементы:

            std::string stringBuilder;
            bool isBracetClosed = false;

            for (int i = 1; !isBracetClosed; ++i) { // начинаем считывать элементы строки
                if (setStr[i] == '[') { // Постоянная проверка, что если скобка открывается снова, то это ошибка.
                    throw std::invalid_argument(errorProtocolMsg);
                }

                switch (setStr[i]) {
                    case ']': { // Если линия закрывается, то надо:
                        if (!stringBuilder.empty()) {
                            saveElement(stringBuilder);
                        } else {
                            throw std::invalid_argument(errorProtocolMsg);
                        }

                        isBracetClosed = true;

                        break;
                    }
                    case ',': { // Если запитая, то надо сохранить новый элемент матрицы
                        if (!stringBuilder.empty()) { // если в сборщике строки ничего нет, и текущий симвлол запятая, то это ошибка
                            saveElement(stringBuilder);
                        } else {
                            throw std::invalid_argument(errorProtocolMsg);
                        }

                        break;
                    }
                    case ' ': // Пустота она и в Африке пустота, а тут и подабно. Короче на пробел ничего делать не надо.
                        break;
                    default: { // Если у нас ничего из выше упомянутого не было, то запишем новый символ нового элемента матрицы
                        stringBuilder.push_back(setStr[i]);
                        break;
                    }
                }

            }
        }
    } else {
        throw std::invalid_argument(errorProtocolMsg);
    }
}

void MySet::saveElement(std::string &stringBuilder) { // -10
    int element; // переменная для временного хранения элемента матрицы (Для его сохранения)

    std::istringstream ss(
            stringBuilder); // мы берем нашу строку с записанными данными и делаем из него поток данных для того, чтобы потом можно было сделать проверку, а можно ли его вообще записать в наше временную переменную.
    stringBuilder.clear(); // очищаем собранный из символов элемент матрицы
    if (ss >> element) { // Пытаемся записать строку, собранную до того посимвольно, во временную переменную
        // Если успешно, то:
        if (!contains(element)) {
            length++; // увеличиваем длину на 1

            // сохраняем новый элемент
            if (length == 1) {
                elements = new int[1]{element};
            } else {
                int *temp = new int[length];
                std::memcpy(temp, elements, sizeof(int) * length);
                delete[] elements;
                elements = temp;
            }
        }

    } else {
        // Если не удалось записать собранную строчку во временную переменную, то:

        // очистить лементы. Они уже не нужны, потому что матрица неправильно пришла на обработку.
        delete[] elements;

        length = 0; // обнуолим длину множества

        throw std::invalid_argument("Error! Value is invalid: " + std::to_string(
                element)); // вызываем (выбрасываем) ошибку, где говорим, что значение некорректное и показываем, что за значение мы получили.
    }
}

void MySet::unitWith(const MySet &set) {
    // создадим пустой вектор, куда запишем нужные значения
    int *temp;
    int idx = 0;
    int newLength = 0;
    int *temp4temp;
    for (int i = 0; i < length; ++i) { // перебираем элемента текущего множества
        for (int j = 0; j < set.length; ++j) { // перебираем элементы переданного множества
            if (elements[i] ==
                set.elements[j]) { // проверяем, нашелся ли такой же элемент из текущего множества в переданном
                // если нашелся, то сохраняем его в вектор с нужными значениями
                if (newLength == 0) {
                    temp = new int[++newLength]{elements[i]};
                    ++idx;
                } else {
                    temp4temp = new int[newLength + 1];
                    std::memcpy(temp4temp, temp, sizeof(int) * newLength++);
                    delete[] temp;
                    temp = temp4temp;
                    temp[idx++] = elements[i];
                }

                break; // больше искать не надо, можно прервать цикл
            }
        }
    }

    // после прохода по всем элементам текущего множества, переписываем временные нужные значения в долговечные
    delete[] elements;
    elements = temp;

    // сохраняем новую длину множества
    length = newLength;
}

void MySet::crossWith(const MySet &set) {
    bool hasFoundSimilar = false; // создадим переменную (флаг), которая следит за тем, нашли ли мы такой же элемент в другом множестве
    int *temp;
    int idx = 1;
    int newLength = length;
    for (int i = 0; i < set.length; ++i) { // перебираем элементы переданного множества
        for (int j = 0; j < length; ++j) { // перебираем элементы текущего множества
            if (set.elements[i] ==
                elements[j]) { // проверяем, нашелся ли в текущем множестве такой же элемент, что и в переданном
                hasFoundSimilar = true; // если нашелся, то меняем флаг на true
                break; // перерываем цикл, потому что больше нет смысла идти по множеству дальше
            }
        }

        if (!hasFoundSimilar) {
            // если не нашелся такой же элемент, то мы сохраняем в текущее множетсво тот элемент из переданного, который не нашелся в текущем
            temp = new int[++newLength];
            std::memcpy(temp, elements, sizeof(int) * (newLength - 1));
            temp[newLength - 1] = set.elements[i];
            delete[] elements;
            elements = temp;
        }

        hasFoundSimilar = false; // обновляем флаг для дальнейшего поиска
    }

    // сохраняем новую длину текущего множества
    length = newLength;
}

void MySet::addElement(const int &element) {
    for (int i = 0; i < length; ++i) { // перебираем элементы текущего множества
        if (elements[i] == element) // если переданный элемент уже существует, то мы ничего не делаем
            return;
    }

    // если мы дошли до сюда, значит переданного элемента не нашлось в текущем множестве, поэтому надо его добавить
    if (length == 0) {
        elements = new int[1]{element};
        ++length;
    } else {
        int *temp = new int[length + 1];
        std::memcpy(temp, elements, sizeof(int) * length++);
        delete[] elements;
        temp[length - 1] = element;
        elements = temp;
    }
}

bool MySet::contains(const int &element) {
    for (int i = 0; i < length; ++i) { // перебираем элементы множества
        if (elements[i] == element) // если мы нашли переданный элемент, то вернем true
            return true;
    }

    return false; // если не нашли, то вернем false
}

void MySet::diffTo(const MySet &set) {
    // создадим пустой вектор, куда запишем нужные значения
    int *temp;
    int idx = 0;
    int newLength = 0;
    int *temp4temp;

    bool hasFoundSimilar = false; // создадим переменную (флаг), которая следит за тем, нашли ли мы такой же элемент в другом множестве
    for (int i = 0; i < length; ++i) { // перебираем элементы текущего множества
        for (int j = 0; j < set.length; ++j) { // перебираем элементы переданного множества
            if (elements[i] == set.elements[j]) { // если мы нашли такой же элемент в переданном множестве, то:
                hasFoundSimilar = true;
                break; // прерываем цикл
            }
        }

        // если мы не смогли найти такой же элемент в переданном, то:
        if (!hasFoundSimilar) {
            // сохраним его в нужных элеменах
            if (newLength == 0) {
                temp = new int[++newLength]{elements[i]};
                ++idx;
            } else {
                temp4temp = new int[newLength + 1];
                std::memcpy(temp4temp, temp, sizeof(int) * newLength++);
                delete[] temp;
                temp = temp4temp;
                temp[idx++] = elements[i];
            }
        }

        hasFoundSimilar = false; // обновим флаг для дальнейших поисков
    }

    // пересохраним нужные элементы в текущее множество
    delete[] elements;
    elements = temp;

    // обновим длину текущего множества
    length = newLength;
}

int MySet::getMin() {
    int min = elements[0]; // за минимальный элемент примим самый первый элемент множества

    for (int i = 1; i < length; ++i) { // перебираем текущее множество, начиная со второго элемента
        if (elements[i] < min) // если какой-то элемент множества меньше значения в минимальной переменной, то:
            min = elements[i]; // сохраним значение этого элемента в минимальной переменной
    }

    return min; // возвращаем минимальное значение множества
}

int MySet::getMax() {
    int max = elements[0]; // за максимальный элемент примим самый первый элемент множества

    for (int i = 1; i < length; ++i) { // перебираем текущее множество, начиная со второго элемента
        if (elements[i] > max) // если какой-то элемент больше значени в максимальной переменной, то:
            max = elements[i]; // сохраним значение этого элемента в минимальной переменной
    }

    return max; // возвращаем максимальное значение множества
}

void MySet::drawTable() {
    std::cout << std::endl; // делаем отступ вначале
    std::cout << "Бинарная карта\n\n";

    int val; // создадим переменную для получения бита отображения на карта ( Короче тут будет либо 1, либо 0)
    int min = getMin(); // получаем минимальное значение
    int max = getMax(); // получаем максимальное значение

    for (int i = min; i <= max; ++i) { // перебираем значение от минимальное до максимально текущего множества ПОДРЯД
        // contains() проверяет, есть ли такое число во множестве. ? заменяет if(). То, что перед ? можно мысленно поставить в (), если бы мы писали привычный if(). Если перед ? выражение истина, то подставляется то, что перед : Если же ложь, тогда то, что после : Таким образом, если значение i содержится во множество, то val = 1; если нет, то val = 0;
        val = contains(i) ? 1 : 0;

        // Так как val может оказаться отрицательным, вернее, равен -1, то следует сделать похожую проверку: если val < 0 (отрицательный), то пусть val = 1; если же val не отрицательный, то пусть val = val, т.е. не изменится. А значит останется 0
        val = val < 0 ? 1 : val;

        cout << i << '\t' << val
             << endl; // выводим в консоль сначала элемент, а потом 1 если он входит в множество и 0 если нет
    }

    cout << endl;
}