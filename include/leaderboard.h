// T10_G01

#pragma once

#include <string>
#include <vector>

#define MAX_PLAYER_NAME_LENGTH 15

#define CHARS_PER_SCORE 4

#define LEADERBOARD_FILE_NAME(number) ("MAZE_" + std::to_string(number) + "_WINNERS.TXT")

/**
 * @brief A node in the leaderboard, containing information about a player and its respective score.
 * 
 */
struct Node {

    std::string playerName;

    int score;

};

/**
 * @brief Checks if the score of the left hand side node is less than the score of the right hand side node.
 * 
 * @param lhs the first node
 * @param rhs the second node
 * @return true if the score of the left hand side node is less than the score of the right hand side node, false otherwise
 */
inline bool operator<(const Node& lhs, const Node& rhs);

/**
 * @brief The leaderboard itself
 * 
 */
class Leaderboard {

    public:
        static void showLeaderboard(const int& mazeNumber);
        static void sortLeaderboard();
        static void addEntryToLeaderboard(Node newEntry);
        static void readLeaderboardFromFile(const std::string& fileName);
        static void writeLeaderboardToFile(const std::string& fileName);
        static int  pickLeaderboard();

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
//void writeLeaderboardToFile(const std::string& fileName, const Leaderboard& leaderboard);