#ifndef BOTTLES_H
#define BOTTLES_H

#include <vector>
using namespace std;

vector<vector<char>> createBottles();
bool isBottleFull(const vector<char>& bottle);
bool isBottleEmpty(const vector<char>& bottle);
void printBottles(const vector<vector<char>>& bottles);

#endif
