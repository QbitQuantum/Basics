#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

// Files
#include "ConfigFile/Config.cpp"

namespace fs = std::filesystem;

// Function
std::vector<std::string> readFile(const fs::path& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return {}; 
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

int check_filesname(const std::string& filename, const std::string& admin_filename) {
    return (filename.find(admin_filename) != std::string::npos) ? 1 : 0;
}

int main() {

    CAdmin obj;

    if (obj.access_permission) {
        std::string filename;
        std::cout << "Input name file: ";
        std::cin >> filename;

        if (obj.check_FilesName && check_filesname(filename, obj.FilesName)) {
            std::cout << "Error: You cannot use " << filename << std::endl;
            return 1;
        }
        auto lines = readFile(filename);
        if (lines.empty()) {
            std::cerr << "Failed to open file or read file" << std::endl;
            return 1;
        }
        for (const auto& line : lines) {
            std::cout << line << std::endl;
        }
    }

    return 0;
}