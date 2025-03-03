#include "../include/level.h"
#include <algorithm>
#include <utility>
#include <iostream>
#include <sstream>
#include <fstream>
#include "raylib.h"

const std::vector<std::pair<int, int>> DIRECTIONS = {
  {0, 1},
  {0, -1},
  {1, 0},
  {-1, 0}
};

static Grid populateGrid(const std::vector<std::string>& vecStrings);
static Player findPlayerStart(const std::vector<std::string>& vecStrings);
static GoalPositions findGoalPositions(const Grid& grid);
void rtrim(std::string& s);

Level::Level(std::string_view inFile) {
  std::cout << "Initialized" << std::endl;
  std::ifstream file(inFile);
  std::vector<std::string> vecString {};

  if (!file.is_open()) {
    std::cerr << "Error: File not found.\n";
    return;
  }

  std::string line {};

  while (std::getline(file, line)) {
    rtrim(line);
    longestRow = std::max(line.size(), longestRow);
    vecString.push_back(line);
  }

  // populate some important stuff
  grid = populateGrid(vecString);
  player = findPlayerStart(vecString);
  goals = findGoalPositions(grid);
}

void Level::movePlayer() {

  int oldX, oldY;

  int fix = 262;
  int idx { -1 };

  if (IsKeyPressed(KEY_RIGHT)) idx = KEY_RIGHT;
  if (IsKeyPressed(KEY_LEFT)) idx = KEY_LEFT;
  if (IsKeyPressed(KEY_DOWN)) idx = KEY_DOWN;
  if (IsKeyPressed(KEY_UP)) idx = KEY_UP;

  if (idx == -1) return;
   
  std::pair<int, int> updatePos = DIRECTIONS[idx - fix];
  int updateX { updatePos.first };
  int updateY { updatePos.second };

  if (grid[player.x + updateX][player.y + updateY] == 'B') {
    oldX = player.x;
    oldY = player.y;

    int tempX = player.x + (updateX * 2);
    int tempY = player.y + (updateY * 2);

    if (grid[tempX][tempY] == 'X' || grid[tempX][tempY] == 'B') {
      return;
    }

    player.x += updateX;
    player.y += updateY;

    grid[player.x][player.y] = 'P';
    grid[tempX][tempY] = 'B';
    grid[oldX][oldY] = ' ';

  } else if (grid[player.x + updateX][player.y + updateY] != 'X') { // check if wall
    oldX = player.x;
    oldY = player.y;
    player.x += updateX;
    player.y += updateY;

    grid[player.x][player.y] = 'P';
    grid[oldX][oldY] = ' ';
  }
  
  fixGoals();
}

bool Level::checkGoals() const {
  for (const auto& coord : goals) {
    if (grid[coord.first][coord.second] != 'B') {
      return false;
    }
  }
  return true;
}

void Level::fixGoals() {
  for (const auto& coord : goals) {
    if (grid[coord.first][coord.second] != 'G' &&
        grid[coord.first][coord.second] != 'B' &&
        grid[coord.first][coord.second] != 'P') // the price goes up if its USD
      grid[coord.first][coord.second] = 'G';
  }
}

/*
void Level::printStuff() const {
  for (const auto& vec : grid) {
    for (char c : vec) {
      std::cout << c;
    }
    std::cout << '\n';
  }
}
*/

/*
 * Construct a vector of chars
 */
static Grid populateGrid(const std::vector<std::string>& vecStrings) {
  Grid grid {};

  for (const auto& s : vecStrings) {
    std::vector<char> sToVect {};
    for (char c : s) {
      sToVect.push_back(c);
    }
    grid.push_back(sToVect);
  }

  return grid;
};

/*
 * Find the starting position of the player in the given level
 */
static Player findPlayerStart(const std::vector<std::string>& vecStrings) {
  for (size_t i = 0; i < vecStrings.size(); ++i) {
    for (size_t j = 0; j < vecStrings[i].size(); ++j) {
      if ((vecStrings[i]).at(j) == 'P') {
        return {static_cast<int>(i), static_cast<int>(j)};
      }
    }
  }
  return {-1, -1};
};

static GoalPositions findGoalPositions(const Grid& grid) {
  GoalPositions goals {};

  for (size_t i = 0; i < grid.size(); ++i) {
    std::pair<int, int> temp {};
    for (size_t j = 0; j < grid[i].size(); ++j) {
      if (grid[i][j] == 'G') {
        temp.first = i;
        temp.second = j;
        goals.push_back(temp);
      }
    }
  }
  return goals;
}

/*
 * remove excess whitespace off a string.
 */
void rtrim(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
  }).base(), s.end());
}
