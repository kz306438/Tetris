#pragma once
#include <iostream>
#include <fstream>
#include <string>

class FileManager {
public:
    FileManager() = default;

    FileManager(const std::string& filename) : filename_(filename) {}

    template <typename T>
    void saveVariable(const std::string& variableName, const T& variable) {
        // Создаем временный файл для записи
        std::ofstream tempFile("temp.txt");

        if (tempFile.is_open()) {
            // Копируем старые переменные в новый файл, пропуская ту, которую мы хотим перезаписать
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

            // Записываем новую переменную
            tempFile << variableName << " " << variable << std::endl;

            tempFile.close();

            // Заменяем старый файл новым
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
            //std::cerr << "File integrity check failed. The file may be tampered with." << std::endl;
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

    bool isEmpty() {
        std::ifstream file(filename_);
        return !file || file.peek() == std::ifstream::traits_type::eof();
    }
private:
    std::string filename_;

    void updateFileHash() {
        std::ifstream file(filename_, std::ios::binary);
        if (file.is_open()) {
            char byte;
            unsigned char hash = 0;

            while (file.get(byte)) {
                hash ^= static_cast<unsigned char>(byte);
            }

            file.close();

            // Сохраняем хеш в файл
            std::ofstream hashFile((filename_ + ".hash").c_str(), std::ios::binary);
            if (hashFile.is_open()) {
                hashFile.put(hash);
                hashFile.close();
            }
            else {
                std::cerr << "Unable to open hash file for saving." << std::endl;
            }
        }
        else {
            std::cerr << "Unable to open file for hash calculation." << std::endl;
        }
    }

    bool verifyFileIntegrity() {
        std::ifstream hashFile((filename_ + ".hash").c_str(), std::ios::binary);
        if (hashFile.is_open()) {
            char storedHash;
            hashFile.get(storedHash);
            hashFile.close();

            unsigned char currentHash = 0;
            std::ifstream file(filename_, std::ios::binary);

            if (file.is_open()) {
                char byte;
                while (file.get(byte)) {
                    currentHash ^= static_cast<unsigned char>(byte);
                }

                file.close();

                return storedHash == currentHash;
            }
            else {
                std::cerr << "Unable to open file for hash verification." << std::endl;
            }
        }
        else {
            std::cerr << "Unable to open hash file for verification." << std::endl;
        }

        return false;
    }
};