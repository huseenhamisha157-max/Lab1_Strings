// Лабораторная работа №1. Вариант 19.
// Способ хранения строки: массив символов (char[])
// Задание: переставить все слова в строке в обратном порядке,
// если длина строки больше 10 символов и содержит хотя бы одно
// заглавное слово (слово, состоящее целиком из заглавных букв).
// Иначе - поменять местами первое и последнее слова.
//
// Требование: обработка выполняется ТОЛЬКО с исходным массивом,
// без использования дополнительных массивов.

#include <iostream>
using namespace std;

const int MAX_SIZE = 1000;

// Вычисление длины строки (поиск символа '\0')
int getLength(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Проверка, является ли символ латинской буквой
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Проверка, является ли буква заглавной
bool isUpper(char c) {
    return c >= 'A' && c <= 'Z';
}

// Реверс участка массива str[left..right] на месте.
// Дополнительная память - одна переменная temp (не массив).
void reverseRange(char str[], int left, int right) {
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

// Проверка наличия хотя бы одного "заглавного" слова
// (слово, все буквы которого - заглавные)
bool hasUpperWord(char str[], int len) {
    int i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') i++;   // пропуск пробелов
        if (i >= len) break;

        bool hasLetterInWord = false;
        bool allUpper = true;
        while (i < len && str[i] != ' ') {
            if (isLetter(str[i])) {
                hasLetterInWord = true;
                if (!isUpper(str[i])) {
                    allUpper = false;
                }
            }
            i++;
        }
        if (hasLetterInWord && allUpper) {
            return true;
        }
    }
    return false;
}

// Реверс порядка слов в строке (без доп. массивов).
// Алгоритм: 1) реверсировать всю строку;
//           2) реверсировать каждое слово обратно.
void reverseWordsOrder(char str[], int len) {
    reverseRange(str, 0, len - 1);

    int i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') i++;
        int wordStart = i;
        while (i < len && str[i] != ' ') i++;
        int wordEnd = i - 1;
        if (wordStart <= wordEnd) {
            reverseRange(str, wordStart, wordEnd);
        }
    }
}

// Обмен местами первого и последнего слова строки (без доп. массивов).
// Пусть строка представлена как [A][C][B], где
//   A - первое слово, B - последнее слово, C - всё, что между ними.
// Требуется получить [B][C][A].
// Это достигается последовательностью из 4-х реверсов:
//   1) реверс всего участка [A C B]  -> даёт reverse(B) reverse(C) reverse(A)
//   2) реверс первых |B| символов    -> B reverse(C) reverse(A)
//   3) реверс следующих |C| символов -> B C reverse(A)
//   4) реверс последних |A| символов -> B C A
void swapFirstAndLastWord(char str[], int len) {
    // границы первого слова
    int firstStart = 0;
    while (firstStart < len && str[firstStart] == ' ') firstStart++;
    int firstEnd = firstStart;
    while (firstEnd < len && str[firstEnd] != ' ') firstEnd++;
    firstEnd--; // включительно

    // границы последнего слова
    int lastEnd = len - 1;
    while (lastEnd >= 0 && str[lastEnd] == ' ') lastEnd--;
    int lastStart = lastEnd;
    while (lastStart >= 0 && str[lastStart] != ' ') lastStart--;
    lastStart++; // включительно

    // если в строке только одно слово - менять нечего
    if (firstStart >= lastStart) {
        return;
    }

    int a = firstEnd - firstStart + 1;      // длина слова A
    int c = lastStart - firstEnd - 1;       // длина среднего блока C (может быть 0)
    int b = lastEnd - lastStart + 1;        // длина слова B

    reverseRange(str, firstStart, lastEnd);                 // 1
    reverseRange(str, firstStart, firstStart + b - 1);       // 2
    if (c > 0) {
        reverseRange(str, firstStart + b, firstStart + b + c - 1); // 3
    }
    reverseRange(str, firstStart + b + c, lastEnd);          // 4
}

int main() {
    char str[MAX_SIZE];

    cout << "Vvedite stroku: ";
    cin.getline(str, MAX_SIZE);

    int len = getLength(str);

    cout << "Iskhodnaya stroka: \"" << str << "\"" << endl;
    cout << "Dlina stroki: " << len << endl;

    if (len > 10 && hasUpperWord(str, len)) {
        cout << "Uslovie vypolneno (dlina > 10 i est' zaglavnoe slovo)." << endl;
        cout << "Deystvie: reverse poryadka slov." << endl;
        reverseWordsOrder(str, len);
    }
    else {
        cout << "Uslovie NE vypolneno." << endl;
        cout << "Deystvie: obmen pervogo i poslednego slova." << endl;
        swapFirstAndLastWord(str, len);
    }

    cout << "Rezultat: \"" << str << "\"" << endl;

    return 0;
}