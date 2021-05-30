//T10_G01

#include <fstream>
#include <iostream>
#include <vector>

#include "./files.h"

std::string FileManager::cwd; // this line is needed so that cwd is not undefined

bool FileManager::fileExists(const std::string& fileName, const std::string& relativePathInCwd) {

    std::ifstream file(FileManager::cwd + relativePathInCwd + fileName);

    if (file.is_open()) {
        file.close();
        return file.good(); // the file could be deleted by an external process unknown to us, by returning 'file.good()' we ensure that even if the file does get deleted, the correct status is returned.
    }

    return false; // default behavior
};

std::vector<std::string> FileManager::readFileLines(const std::string& filename, const std::string& relativePathInCwd) {

    std::vector<std::string> fileLines;

    std::fstream f;

    f.open(FileManager::cwd + relativePathInCwd + filename, std::ios::in);

    if (f.is_open()) {

        // file exists, read lines

        std::string line;

        while (std::getline(f, line))   
            fileLines.push_back(line);      
    
        f.close();
    }

    return fileLines;
};

void FileManager::setCWD(std::string newCWD) {
    FileManager::cwd = newCWD; 
}