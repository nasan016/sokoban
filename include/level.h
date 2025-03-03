#pragma once
#include <string>
#include <vector>
#include <utility>
#include "player.h"

using Grid = std::vector<std::vector<char>>;
using GoalPositions = std::vector<std::pair<int, int>>;

class Level {
  public:
    Level(std::string_view inFile);
    Grid grid {}; // I have figured out how to populate the grid
    size_t longestRow {};

    void movePlayer();
    bool checkGoals() const;
    void fixGoals();
    // void printStuff() const;

  private:
    Player player; // just a struct
    GoalPositions goals;
};
