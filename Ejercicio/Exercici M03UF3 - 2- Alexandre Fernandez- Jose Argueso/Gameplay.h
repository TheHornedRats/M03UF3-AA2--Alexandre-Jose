#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
using namespace std;

void initializeBottles(vector<vector<char>>& bottles);
bool checkGameOver(const vector<vector<char>>& bottles, int movesLeft);
void playGame();

#endif
