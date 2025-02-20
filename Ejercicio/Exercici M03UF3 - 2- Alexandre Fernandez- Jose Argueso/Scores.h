#ifndef SCORES_H
#define SCORES_H
#define MAX_LIQUIDS 3


#include <string>
#include <vector>
using namespace std;
int calculateScore(const std::vector<std::vector<char>>& bottles, int movesLeft);

void saveScore(const string& playerName, int score);
vector<pair<string, int>> loadScores();
void displayScores();

#endif
