//T10_G01

#pragma once

#include <string>
#include <vector>

#define RESOURCES_PATH "./"

#define LEADERBOARDS_PATH ""

#define MAZES_PATH ""

class FileManager {

    public:
        static bool fileExists(const std::string& fileName, const std::string& relativePathInCwd = "");
        static void setCWD(std::string cwd);
        static std::vector<std::string> readFileLines(const std::string& filename, const std::string& relativePathInCwd = "");

    private:
        FileManager(); // declare constructor private so this class can't be instanciated
        ~FileManager();

        static std::string cwd;
};