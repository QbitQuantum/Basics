
#include <iostream>
#include <string>

using namespace std;

template <typename Ta, size_t T, typename Fa, size_t F>
void func(Ta(&arr1)[T], Fa(&arr2)[F]) {
    int size1 = T;
    int size2 = F;
    int hash = 0;
    for (int i = 0; i < size1; i++) {
        cout << arr1[i] << " = ";
        for (char c : arr1[i]) {
            for (int j = 0; j < size2; j++) {
                if (c == arr2[j]) {
                    hash += j;
                    cout << j << " ";
                }
            }
        }
        std::cout << "\033[1;31m";
        cout << "Hash = " << hash << endl;
        std::cout << "\033[0m";
    }
}
int main()
{

    std::string keywords[] = {
      "auto", "bool", "break", "case", "char", "class", "const", "continue", "default", "delete",
      "do", "double", "else", "enum", "extern", "float", "for", "friend", "goto", "if",
      "inline", "int", "long", "mutable", "namespace", "new", "operator", "private", "protected", "public",
      "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast",
      "struct", "switch", "synchronized", "template", "this", "throw", "true", "try", "typedef", "typeid",
      "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while"
    };

    const char chars[] = {
    'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x',
    'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z',
    '"', '\'', '/', '{', '}',
    '[', ']', '(', ')', ';',
    ',', '.', ':', '+', '*',
    '=', '%', '&', '|', '^',
    '<', '>', '!', '&', '!',
    '?'
    };

    func(keywords, chars);
}
/*

\033[0m - Сброс всех атрибутов форматирования к значениям по умолчанию

\033[1m - Жирный текст

\033[2m - Свечение текста (не поддерживается в некоторых терминалах)

\033[3m - Курсив текста

\033[4m - Подчеркнутый текст

\033[30m - Черный цвет текста

\033[31m - Красный цвет текста

\033[32m - Зеленый цвет текста

\033[33m - Желтый цвет текста

\033[34m - Синий цвет текста

\033[35m - Фиолетовый цвет текста

\033[36m - Голубой цвет текста

\033[37m - Белый цвет текста

\033[40m - Черный цвет фона

\033[41m - Красный цвет фона

\033[42m - Зеленый цвет фона

\033[43m - Желтый цвет фона

\033[44m - Синий цвет фона

\033[45m - Фиолетовый цвет фона

\033[46m - Голубой цвет фона

\033[47m - Белый цвет фона
*/


/*
    std::string keywords[] = {
      "auto", "bool", "break", "case", "char", "class", "const", "continue", "default", "delete",
      "do", "double", "else", "enum", "extern", "float", "for", "friend", "goto", "if",
      "inline", "int", "long", "mutable", "namespace", "new", "operator", "private", "protected", "public",
      "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast",
      "struct", "switch", "synchronized", "template", "this", "throw", "true", "try", "typedef", "typeid",
      "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while"
    };

    const char chars[] = {
    "a", "b", "c", "d", "e", "f",
    "g", "h", "i", "j", "k", "l",
    "m", "n", "o", "p", "q", "r",
    "s", "t", "u", "v", "w", "x",
    "y", "z",
    "A", "B", "C", "D", "E", "F",
    "G", "H", "I", "J", "K", "L",
    "M", "N", "O", "P", "Q", "R",
    "S", "T", "U", "V", "W", "X",
    "Y", "Z",
    "\"", "'", "/", "{", "}",
    "[", "]", "(", ")", ";",
    ",", ".", ":", "+", "*",
    "=", "%", "&", "|", "^",
    "<", ">", "!", "&", "!",
    "?"
    };
*/