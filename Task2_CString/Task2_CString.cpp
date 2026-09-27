// Лабораторная работа №1. Вариант 19.
// Способ хранения строки: строка в стиле C (char*, завершается '\0')
// Задание: переставить все слова в строке в обратном порядке,
// если длина строки больше 10 символов и содержит хотя бы одно
// заглавное слово (слово, состоящее целиком из заглавных букв).
// Иначе - поменять местами первое и последнее слова.
//
// Требование: обработка выполняется через указатели (char*) и
// признак конца строки '\0', без использования дополнительных
// массивов. strlen() используется только для измерения длины,
// а не для хранения данных.

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_SIZE = 1000;

// Проверка, является ли символ латинской буквой
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Проверка, является ли буква заглавной
bool isUpper(char c) {
    return c >= 'A' && c <= 'Z';
}

// Реверс участка строки между указателями left и right (включительно)
void reverseRange(char* left, char* right) {
    while (left < right) {
        char temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

// Проверка наличия хотя бы одного "заглавного" слова
bool hasUpperWord(char* str) {
    char* p = str;
    while (*p != '\0') {
        while (*p == ' ') p++;               // пропуск пробелов
        if (*p == '\0') break;

        bool hasLetterInWord = false;
        bool allUpper = true;
        while (*p != '\0' && *p != ' ') {
            if (isLetter(*p)) {
                hasLetterInWord = true;
                if (!isUpper(*p)) {
                    allUpper = false;
                }
            }
            p++;
        }
        if (hasLetterInWord && allUpper) {
            return true;
        }
    }
    return false;
}

// Реверс порядка слов в строке (без доп. массивов)
void reverseWordsOrder(char* str) {
    int len = strlen(str);
    reverseRange(str, str + len - 1);

    char* p = str;
    while (*p != '\0') {
        while (*p == ' ') p++;
        char* wordStart = p;
        while (*p != '\0' && *p != ' ') p++;
        char* wordEnd = p - 1;
        if (wordStart <= wordEnd) {
            reverseRange(wordStart, wordEnd);
        }
    }
}

// Обмен местами первого и последнего слова строки (без доп. массивов),
// логика та же, что и в варианте с массивом (4 реверса подряд)
void swapFirstAndLastWord(char* str) {
    int len = strlen(str);

    char* firstStart = str;
    while (*firstStart == ' ') firstStart++;
    char* firstEnd = firstStart;
    while (*firstEnd != '\0' && *firstEnd != ' ') firstEnd++;
    firstEnd--;

    char* lastEnd = str + len - 1;
    while (lastEnd >= str && *lastEnd == ' ') lastEnd--;
    char* lastStart = lastEnd;
    while (lastStart >= str && *lastStart != ' ') lastStart--;
    lastStart++;

    if (firstStart >= lastStart) {
        return; // в строке только одно слово
    }

    int a = firstEnd - firstStart + 1;
    int c = lastStart - firstEnd - 1;
    int b = lastEnd - lastStart + 1;

    reverseRange(firstStart, lastEnd);
    reverseRange(firstStart, firstStart + b - 1);
    if (c > 0) {
        reverseRange(firstStart + b, firstStart + b + c - 1);
    }
    reverseRange(firstStart + b + c, lastEnd);
}

int main() {
    char str[MAX_SIZE];

    cout << "Vvedite stroku: ";
    cin.getline(str, MAX_SIZE);

    int len = strlen(str);
    cout << "Iskhodnaya stroka: \"" << str << "\"" << endl;
    cout << "Dlina stroki: " << len << endl;

    if (len > 10 && hasUpperWord(str)) {
        cout << "Uslovie vypolneno (dlina > 10 i est' zaglavnoe slovo)." << endl;
        cout << "Deystvie: reverse poryadka slov." << endl;
        reverseWordsOrder(str);
    }
    else {
        cout << "Uslovie NE vypolneno." << endl;
        cout << "Deystvie: obmen pervogo i poslednego slova." << endl;
        swapFirstAndLastWord(str);
    }

    cout << "Rezultat: \"" << str << "\"" << endl;

    return 0;
}