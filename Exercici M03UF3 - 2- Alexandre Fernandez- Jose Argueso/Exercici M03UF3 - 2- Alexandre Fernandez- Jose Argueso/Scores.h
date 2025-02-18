#ifndef SCORES_H
#define SCORES_H

#include <string>
#include <vector>
using namespace std;

void saveScore(const string& playerName, int score);
vector<pair<string, int>> loadScores();
void displayScores();

#endif
