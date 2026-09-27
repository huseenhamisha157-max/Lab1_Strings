// Лабораторная работа №1. Вариант 19.
// Способ хранения строки: строка хранится в файле.
// Программа считывает строку из файла input.txt, обрабатывает её
// (та же логика, что и в вариантах 1/2), и записывает результат
// в файл output.txt.
//
// Задание: переставить все слова в строке в обратном порядке,
// если длина строки больше 10 символов и содержит хотя бы одно
// заглавное слово (слово, состоящее целиком из заглавных букв).
// Иначе - поменять местами первое и последнее слова.
//
// Используются стандартные функции C: fopen(), fgets(), fputs(), fclose().
// Дополнительные массивы не используются - только исходный буфер str[].

// Отключение предупреждения C4996 в Visual Studio (MSVC считает fopen
// "небезопасной" и предлагает fopen_s, но обычный fopen() полностью
// стандартен и кроссплатформенен - работает и в g++, и в других компиляторах)
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAX_SIZE = 1000;

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isUpper(char c) {
    return c >= 'A' && c <= 'Z';
}

void reverseRange(char* left, char* right) {
    while (left < right) {
        char temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

bool hasUpperWord(char* str) {
    char* p = str;
    while (*p != '\0') {
        while (*p == ' ') p++;
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
        return;
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

// Удаление символа перевода строки '\n' (и '\r' для Windows-файлов),
// который fgets() может добавить в конец буфера
void trimNewline(char* str) {
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

int main() {
    const char* inputFileName = "input.txt";
    const char* outputFileName = "output.txt";

    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Oshibka: ne udalos' otkryt' fayl %s\n", inputFileName);
        return 1;
    }

    char str[MAX_SIZE];
    if (fgets(str, MAX_SIZE, inputFile) == NULL) {
        printf("Oshibka: fayl %s pust ili ne udalos' prochitat' stroku\n", inputFileName);
        fclose(inputFile);
        return 1;
    }
    fclose(inputFile);

    trimNewline(str);

    int len = strlen(str);
    printf("Stroka, prochitannaya iz %s: \"%s\"\n", inputFileName, str);
    printf("Dlina stroki: %d\n", len);

    if (len > 10 && hasUpperWord(str)) {
        printf("Uslovie vypolneno (dlina > 10 i est' zaglavnoe slovo).\n");
        printf("Deystvie: reverse poryadka slov.\n");
        reverseWordsOrder(str);
    }
    else {
        printf("Uslovie NE vypolneno.\n");
        printf("Deystvie: obmen pervogo i poslednego slova.\n");
        swapFirstAndLastWord(str);
    }

    printf("Rezultat: \"%s\"\n", str);

    FILE* outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Oshibka: ne udalos' otkryt' fayl %s dlya zapisi\n", outputFileName);
        return 1;
    }

    fputs(str, outputFile);
    fclose(outputFile);

    printf("Rezultat uspeshno zapisan v fayl %s\n", outputFileName);

    return 0;
}