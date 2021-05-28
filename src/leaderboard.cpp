#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cmath>

#include "../include/utils.h"
#include "../include/leaderboard.h"
#include "../include/files.h"

std::vector<Node> Leaderboard::leaderboardEntries = std::vector<Node>();

int Leaderboard::pickLeaderboard() {

    unsigned int mazeNumber;

    while (true) {
        std::cout << "Which maze's leaderboard do you want to see? (maze numbers range from 1 to 99, 0 to go back to the previous menu)\n\n-> ";
        if (!(std::cin >> mazeNumber) || std::cin.peek() != '\n') {

            clearScreen();
            clearInput();

            std::cout << "Please input a number.\n" << std::endl;
            continue;
        }

        clearInput();

        if (mazeNumber == 0) {
            break; // go back
        } else if (mazeNumber > 99) { // we only need to check if the input is greater because we declared the var as 'unsigned'
            clearScreen();
            std::cout << "Not a valid maze number. \n\n";
            continue;
        }

        if (!FileManager::fileExists(LEADERBOARD_FILE_NAME(mazeNumber), LEADERBOARDS_PATH)) {
            clearScreen();
            std::cout << "The leaderboard for that maze doesn't exist.\n\n";
            continue;
        }

        return mazeNumber;
    }

    return 0; // returning 0 (not a valid maze number) signals that we wish to go back to the menu
};

void Leaderboard::sortLeaderboard() {
    std::sort(Leaderboard::leaderboardEntries.begin(), Leaderboard::leaderboardEntries.end(), [](const Node& rhs, const Node& lhs){ return rhs.score < lhs.score;});
}

void Leaderboard::showLeaderboard(const int &mazeNumber) {

    clearScreen();

    std::vector<std::string> rules = FileManager::readFileLines(LEADERBOARD_FILE_NAME(mazeNumber), LEADERBOARDS_PATH);

    std::cout << "Maze: " << (mazeNumber < 10 ? "0" : "") << mazeNumber << '\n' << std::endl;

    for (auto line : rules) {
        std::cout << line << "\n";
    }

    std::cout << std::endl;
};

void Leaderboard::addEntryToLeaderboard(Node newEntry) {
    Leaderboard::leaderboardEntries.push_back(newEntry);
};

void Leaderboard::readLeaderboardFromFile(const std::string &fileName)
{

    if (!FileManager::fileExists(fileName, LEADERBOARDS_PATH))
        return;

    auto fileLines = FileManager::readFileLines(fileName, LEADERBOARDS_PATH);

    // the first 2 lines are header information, we can skip them
    for (int i = 2; i < fileLines.size(); i++)
    {

        auto line = fileLines.at(i);

        // the last CHARS_PER_SCORE characters are the score

        int score = 0;

        // extract the score
        for (int j = 0; j < CHARS_PER_SCORE; j++)
        {
            char c = line.at(line.size() - CHARS_PER_SCORE + j);
            score = score * 10 + ((c == ' ' ? '0' : c) - '0');
        }

        // the name that the user inputted might have more than 2 words, store each in tmp and work from there
        std::string name, tmp;

        std::stringstream ss(line.substr(0, line.find_last_of('-'))); // substring to remove score part, and only get the name

        ss >> tmp; // read first token

        name += tmp;

        while (ss.peek() == ' ')
            ss.ignore(1, ' '); // try to clear as many blank spaces as possible

        if (ss.peek() != EOF){
            ss >> tmp;
            name += (' ' + tmp);
        }

        Leaderboard::addEntryToLeaderboard({name, score});
    }
};

void Leaderboard::writeLeaderboardToFile(const std::string &fileName) {

    std::ofstream file;

    file.open(std::string(RESOURCES_PATH) + LEADERBOARDS_PATH + fileName);

    file << "Player";
    file << std::string(MAX_PLAYER_NAME_LENGTH - std::string("Player").length(), ' ');
    file << "- Time";
    file << '\n';

    file << "----------------------" << '\n';

    for (auto entry : Leaderboard::leaderboardEntries) {
        file << entry.playerName;
        file << std::string(MAX_PLAYER_NAME_LENGTH - getPlayerNameLength(entry.playerName), ' ');
        file << " - ";

        int numDigitsInScore = (entry.score <= 0) ? 0 : floor(log10(entry.score)) + 1;

        file << std::string(CHARS_PER_SCORE - numDigitsInScore, ' '); // allign scores to the right
        file << entry.score;
        file << '\n';
    }

    file.close();
};

std::string Leaderboard::getPlayerName() {

    std::string name;

    while (true) {

        std::cout << "What is your name?: ";

        if (!getline(std::cin, name)) { // use getline instead of the extraction operator in order to get the whole line
            clearInput();
            clearScreen();
            std::cout << "There was an error getting input from the user, please retype your name.\n" << std::endl;
            continue;
        }

        // we got no errors extracting player name, check if is within length
        int length = getPlayerNameLength(name);

        if (length < 0 || length > MAX_PLAYER_NAME_LENGTH) {
            clearScreen();
            std::cout << "Name given is longer than the max amount of characters allowed (" << MAX_PLAYER_NAME_LENGTH << "), please retype your name.\n" << std::endl;
            continue;
        }

        // name is within bounds, return it
        return name;
    }
}

int Leaderboard::getPlayerNameLength(const std::string &playerName) {
    int counter = 0;

    for (char c : playerName) {
        if ((c & 0b11000000) == 0b10000000)
            continue; // utf-8 code points that have more than one byte always have a '10' as the most significant bits of the bytes other than the first one, we can just skip them
        counter++;
    }

    return counter;
}
