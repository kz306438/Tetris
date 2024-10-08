#pragma once
#include <string>
#include <fstream>
#include <iostream>

class FileManager {
public:
    static FileManager& getInstance(const std::string& filename = "default.txt");

    template <typename T>
    void saveVariable(const std::string& variableName, const T& variable) {
        std::ofstream tempFile("temp.txt");

        if (tempFile.is_open()) {
            std::ifstream inputFile(filename_);
            std::string name;
            while (inputFile >> name) {
                if (name == variableName) {
                    inputFile.ignore(100, '\n');
                }
                else {
                    tempFile << name << " ";
                    std::string value;
                    std::getline(inputFile, value);
                    tempFile << value << std::endl;
                }
            }
            inputFile.close();

            tempFile << variableName << " " << variable << std::endl;
            tempFile.close();

            std::remove(filename_.c_str());
            if (std::rename("temp.txt", filename_.c_str()) != 0) {
                std::cerr << "Error renaming temp file to " << filename_ << std::endl;
            }
            updateFileHash();
        }
        else {
            std::cerr << "Unable to open temp file for saving." << std::endl;
        }
    }


    template <typename T>
    bool loadVariable(const std::string& variableName, T& variable) {
        if (!verifyFileIntegrity()) {
            return false;
        }

        std::ifstream file(filename_);
        if (file.is_open()) {
            std::string name;
            while (file >> name) {
                if (name == variableName) {
                    if constexpr (std::is_same_v<T, std::string>) {
                        std::getline(file, variable);
                    }
                    else {
                        file >> variable;
                    }
                    return true;
                }
            }
            file.close();
            std::cerr << "Variable '" << variableName << "' not found in the file." << std::endl;
        }
        else {
            std::cerr << "Unable to open file for loading." << std::endl;
        }
        return false;
    }


    bool isEmpty();

private:
    FileManager() = default;
    FileManager(const std::string& filename);

    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    std::string filename_;

    void updateFileHash();
    bool verifyFileIntegrity();
};