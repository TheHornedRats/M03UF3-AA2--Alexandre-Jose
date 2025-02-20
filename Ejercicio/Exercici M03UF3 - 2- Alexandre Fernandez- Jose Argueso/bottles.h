#ifndef BOTTLES_H
#define BOTTLES_H

#include <vector>

#define NUM_BOTTLES 6
#define MAX_LIQUIDS 3

std::vector<std::vector<char>> createBottles();
bool isBottleFull(const std::vector<char>& bottle);
bool isBottleEmpty(const std::vector<char>& bottle);
void printBottles(const std::vector<std::vector<char>>& bottles);
bool pourLiquid(std::vector<std::vector<char>>& bottles, int from, int to);
void initializeBottles(std::vector<std::vector<char>>& bottles);

#endif
