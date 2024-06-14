#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm> // Для использования std::min
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
//#include <unistd.h>

namespace fs = std::filesystem;

int main() {
    const std::string desktopPath = "."; // Путь к текущей директории
    const std::string fileName = desktopPath + "file.cpp";
    const size_t fileSize = 7ull * 1024 * 1024 * 1024;

    std::ofstream file(fileName, std::ios::binary | std::ios::out);
    if (file.is_open()) {
        char buffer[1024] = { 0 }; // Буфер, заполненный нулями
        size_t totalWritten = 0;

        while (totalWritten < fileSize) {
            size_t toWrite = sizeof(buffer);
            if (fileSize - totalWritten < toWrite) {
                toWrite = fileSize - totalWritten;
            }
            file.write(buffer, toWrite);
            totalWritten += toWrite;
        }

        file.close();

        std::cout << "File created with size " << fileSize << " bytes." << std::endl;
    }
    else {
        std::cerr << "Failed to create file." << std::endl;
    }

    // Путь к директории, в которой будем искать файлы
    fs::path search_path = "."; // Текущая директория


    // Расширения файлов, которые мы ищем
    std::vector<std::string> extensions = { ".txt", ".cpp", ".h", ".jpg", ".png" };

    // Проходим по всем файлам в директории
    for (const auto& entry : fs::directory_iterator(search_path)) {
        if (entry.is_regular_file()) { // Проверяем, что это обычный файл
            // Получаем расширение файла
            std::string extension = entry.path().extension().string();
            // Проверяем, есть ли расширение в списке искомых
            if (std::find(extensions.begin(), extensions.end(), extension) != extensions.end()) {
                // Выводим название файла
                std::cout << entry.path().filename() << std::endl;
                // Если это файл .cpp, то выводим его содержимое
                if (extension == ".cpp") {
                    std::ifstream file(entry.path());
                    if (file.is_open()) {
                        std::string line;
                        while (std::getline(file, line)) {
                            std::cout << line << std::endl;
                        }
                        file.close();
                    }
                    else {
                        std::cout << "Не удалось открыть файл " << entry.path() << std::endl;
                    }
                }
            }
        }
    }
    /*
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Current working directory: " << cwd << std::endl;
    }
    else {
        std::cerr << "Error getting current working directory." << std::endl;
    }
    */
    return 0;
}