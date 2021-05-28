// T10_G01

#pragma once

#include <string>
#include <vector>

#define MAX_PLAYER_NAME_LENGTH 15

#define CHARS_PER_SCORE 4

#define LEADERBOARD_FILE_NAME(number) (std::string("MAZE_") + (number < 10 ? "0" : "") + std::to_string(number) + "_WINNERS.TXT")

/**
 * @brief A node in the leaderboard, containing information about a player and its respective score.
 * 
 */
struct Node {

    std::string playerName;

    int score;

};

/**
 * @brief The leaderboard itself
 * 
 */
class Leaderboard {

    public:
        /**
         * @brief Displays a maze's leaderboard.
         * 
         * @param mazeNumber the number of the maze whose leaderboard we want to check.
         */
        static void showLeaderboard(const int& mazeNumber);

        /**
         * @brief Sorts the leaderboard, according to scores.
         * 
         */
        static void sortLeaderboard();

        /**
         * @brief Inserts a player's name and his respective score to the leaderboard.
         * 
         * @param newEntry the player's name and score.
         */
        static void addEntryToLeaderboard(Node newEntry);

        /**
         * @brief Parses the leaderboard object from a leaderboard file.
         * 
         * @param fileName the name of the file containing the leaderboard.
         */
        static void readLeaderboardFromFile(const std::string& fileName);

        /**
         * @brief Writes the contents of the leaderboard object to the respective file
         * 
         * @param fileName the name of the file to which we will write the leaderboard
         */
        static void writeLeaderboardToFile(const std::string& fileName);

        /**
         * @brief Choose which maze's leaderboard you want to check
         * 
         * @return the number of the maze's leaderboard
         */
        static int pickLeaderboard();

        /**
         * @brief Get the Player Name object.
         * 
         * @return the name of the player.
         */
        static std::string getPlayerName();

        /**
         * @brief Get the Player Name Length
         * 
         * @param playerName the name of the player.
         * @return the length of the player's name.
         */
        static int getPlayerNameLength(const std::string& playerName);

    private:
        // the entries of the leaderboard
        static std::vector<Node> leaderboardEntries;
};

/**
 * @brief Sorts the leaderboard by ascending order of node scores.
 * 
 * @param leaderboard the leaderboard to sort
 */
//void sortLeaderboard(Leaderboard& leaderboard);

/**
 * @brief Adds the given entry to the leaderboard
 * 
 * @param leaderboard the leaderboard to edit
 * @param newEntry the new entry to add
 */
//void addEntryToLeaderboard(Leaderboard& leaderboard, Node newEntry);

/**
 * @brief extract entries from the given file into the leaderboard if it exists, otherwise this method is a no-op.
 * 
 * @param filename the name of the file from which to extract the leaderbard entries
 */
//void readLeaderboardFromFile(const std::string& fileName, Leaderboard& leaderboard);

/**
 * @brief Writes the specified leaderboard entry to the specified file
 * 
 * @param fileName the name of the file in which to store the leaderboard
 * @param leaderboard the leaderboard object
 */
