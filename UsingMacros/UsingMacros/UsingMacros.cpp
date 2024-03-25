// Library
#include <iostream>
#include <fstream>
#include <string>

// Files
#include "ConfigFile/Config.cpp"

//Function
int check_filesname(std::string filename, std::string admin_filename) {

    return (filename.find(admin_filename) != std::string::npos) ? 1 : 0;
}

int main() {
    
    CAdmin obj;

    if (obj.access_permission) {
        std::string filename;
        int lineNumber;
        std::cout << "Input name file: ";
        std::cin >> filename;
        if (obj.check_FilesName) {
            while (check_filesname(filename, obj.FilesName))
            {
            std::cout << "Error: You cannot use ";
            std::cout << filename;
            std::cout << "\n";
            std::cout << "Input name file: ";
            std::cin >> filename;
            }
        }
        if (obj.source_code) {
            std::ifstream file(filename);

            if (!file.is_open()) {
                std::cerr << "Не удалось открыть файл!" << std::endl;
                return 1;
            }
            std::string line;
            while (std::getline(file, line)) { 
                std::cout << line << std::endl; 
            }
            file.close(); 
            return 0;
        }
        else {
        std::cout << "Input number line: ";
        std::cin >> lineNumber;

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error open file " << filename << std::endl;
            return 1;
        }
        std::string line;
        int currentLine = 0;
        while (std::getline(file, line)) {
            currentLine++;
            if (currentLine == lineNumber) {
                std::cout << "Line number " << lineNumber << ": " << line << std::endl;
                break;
            }
        }
        if (currentLine < lineNumber) {
            std::cout << "Mnogo vvel " << lineNumber << std::endl;
        }
        file.close();
        return 0;
        }
        
    }
}