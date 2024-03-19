#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
#include <vector>
#include <string>


void  SettingsAct(std::string format) {
    //strings.push_back("billing/billinggui/build/Win32/report/blank/include/act.header.a.hh");

    std::vector<std::string> strings;

    strings.push_back("temp.cpp");

    for (const auto& str : strings) {
        std::ifstream file(str); // Открываем файл для чтения
        std::string line;
        std::string buffer;
        std::regex pragma_info_regex("#pragma format");

        if (file.is_open()) {
            while (std::getline(file, line)) {
                if (std::regex_search(line, pragma_info_regex)) {
                    //buffer << "#pragma format <time> \"D' 'MM' 'YYYY' г.'\"" << std::endl; // Записываем измененную строку в буфер
                    buffer += "#pragma format <time> " + format + "\n"; // Записываем измененную строку в буфер
                    std::cout << buffer + "\n";

                }
                else {
                    buffer += line + "\n";
                    std::cout << buffer + "\n";
                }
            }
            file.close();
        }
        else {
            std::cout << "ne ok." << std::endl;
        }
        std::ofstream outfile("temp.cpp");
        if (outfile.is_open()) {
            outfile << buffer;
            outfile.close();
            std::cout << "ok." << std::endl;
        }
        else {
            std::cout << "dada neok." << std::endl;
        }
    }
}

int main() {
    std::string format = "\"D' '3333333' 'YYYY' г.'\"";
    SettingsAct(format);
}