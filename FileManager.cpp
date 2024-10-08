#include "FileManager.h"

FileManager& FileManager::getInstance(const std::string& filename) {
    static FileManager instance(filename);
    return instance;
}

FileManager::FileManager(const std::string& filename) : filename_(filename) {}

bool FileManager::isEmpty() {
    std::ifstream file(filename_);
    return !file || file.peek() == std::ifstream::traits_type::eof();
}

void FileManager::updateFileHash() {
    std::ifstream file(filename_, std::ios::binary);
    if (file.is_open()) {
        char byte;
        unsigned char hash = 0;

        while (file.get(byte)) {
            hash ^= static_cast<unsigned char>(byte);
        }

        file.close();

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

bool FileManager::verifyFileIntegrity() {
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
