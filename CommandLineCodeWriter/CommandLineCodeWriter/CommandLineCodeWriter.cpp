
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <string>
#include <cstdlib>
#include <Windows.h>

void CodeWriter(std::string FileName, std::string buffer) {
    std::ofstream outfile(FileName);
    if (outfile.is_open()) {
        outfile << buffer;
        outfile.close();
        std::cout << "File "<< FileName <<" close" << std::endl;
    }
    else {
        std::cout << "File "<< FileName << "no open" << std::endl;
    }
}

void  CodeWriterCppFile(std::string format) {

    std::string FileName = "CodeWriterCppFile/CppFile.cpp"; //Файл для изменения
    std::ifstream file(FileName); // Открываем файл для чтения
    std::string line;
    std::string buffer;
 
    std::regex pragma_info_regex("FOR");

    if (file.is_open()) { 
        if (std::getline(file, line)){
            while (std::getline(file, line)) {
                if (std::regex_search(line, pragma_info_regex)) {
                    buffer += "buffer " + format + "\n"; // Записываем измененную строку в буфер
                }
            }
            file.close();
        } else {
            buffer += "buffer " + format + "\n"; // Записываем измененную строку в буфер
            CodeWriter(FileName, buffer);
            std::cout << "CodeWriter"<<std::endl;
        }
    }
    else {
        std::cout << "File no created" << std::endl;
    }
    CodeWriter(FileName, buffer);
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string line;
    std::string text;

    std::cout << "Enter the text (enter an empty line to complete the input):" << std::endl;

    while (true) {
        std::getline(std::cin, line);

        // Если введена пустая строка, то ввод завершается
        if (line.empty()) {
            std::system("cls");
            std::cout << "Консоль очищена для предотвращения засорения кода. Ваш введённый текст: ";
            std::cout << "\n";
            std::cout << text;
            std::cout << "\n";
            break;
        }
            // Добавляем введенную строку к общему тексту
            text += line;
    }

    CodeWriterCppFile(text);
    

    return 0;
}