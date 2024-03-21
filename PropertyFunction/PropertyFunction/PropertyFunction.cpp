#include <iostream>
#define __PRETTY_FUNCTION__ __FUNCSIG__
#include <Windows.h>
#include <string>
#include <regex>

std::string exampleFunctionPRETTY(int a, int b) {
   return __PRETTY_FUNCTION__;
}

int exampleFunctionLINE() {
    return __LINE__;
}

void parsingExampleFunction (std::string parseString) {

    std::string word1, word2, word3;

    std::size_t pos = parseString.rfind(' ');
    if (pos != std::string::npos) {
        word3 = parseString.substr(pos + 1);

        std::size_t prev_pos = parseString.rfind(' ', pos - 1);
        if (prev_pos != std::string::npos) {

            word2 = parseString.substr(prev_pos + 1, pos - prev_pos - 1);

            word1 = parseString.substr(0, prev_pos);
        }
    }

    std::cout << "Тип функции: " << word1 << std::endl;
    std::cout << "Регистр: " << word2 << std::endl;
    std::cout << "Имя функции и параметры: " << word3 << std::endl;
}


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    std::cout << "Необработанная строка";
    std::cout << "\n";
    std::cout << exampleFunctionPRETTY(1, 2);
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Обработанная строка";
    std::cout << "\n";
    parsingExampleFunction(exampleFunctionPRETTY(1, 2));

    return 0;


    return false;
}