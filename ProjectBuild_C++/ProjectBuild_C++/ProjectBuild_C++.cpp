
#include <iostream>
#include <string>

using namespace std;

template <typename Ta, size_t T, typename Fa, size_t F>
void func(Ta(&arr1)[T], Fa(&arr2)[F]) {
    int size1 = T;
    int size2 = F;
    for (int i = 0; i < size1-20; i++) {
        for (char с : arr1)
            int a = 0;
    }
    cout << size1 << endl;
    cout << size2 << endl;

}


int main()
{

    std::string keywords[] = {
      "auto", "bool", "break", "case"
    };

    std::string chars[] = {
    "a", "b", "c", "d", "e", "f",
    "g", "h", "i", "j", "k", "l",
    "m", "n", "o", "p", "q", "r",
    "s", "t", "u", "v", "w", "x",
    "y", "z",
    "A", "B", "C", "D", "E", "F",
    "G", "H", "I", "J", "K", "L",
    "M", "N", "O", "P", "Q", "R",
    "S", "T", "U", "V", "W", "X",
    "Y", "Z"
    };
    func(keywords, chars);
}

/*
    std::string keywords[] = {
      "auto", "bool", "break", "case", "char", "class", "const", "continue", "default", "delete",
      "do", "double", "else", "enum", "extern", "float", "for", "friend", "goto", "if",
      "inline", "int", "long", "mutable", "namespace", "new", "operator", "private", "protected", "public",
      "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast",
      "struct", "switch", "synchronized", "template", "this", "throw", "true", "try", "typedef", "typeid",
      "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while"
    };

    std::string chars[] = {
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