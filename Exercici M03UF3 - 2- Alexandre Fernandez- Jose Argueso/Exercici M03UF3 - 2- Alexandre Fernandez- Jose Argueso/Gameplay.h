#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
using namespace std;

void initializeBottles(vector<vector<char>>& bottles);
bool isValidMove(int target, int source, vector<vector<char>>& bottles);
void makeMove(int target, int source, vector<vector<char>>& bottles, int& score, int& movesLeft);
bool checkGameOver(const vector<vector<char>>& bottles, int movesLeft);
void playGame();

#endif
