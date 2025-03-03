#include "../include/game.h"
#include "raylib.h"

Game::Game(std::string_view inFile) :
  level(inFile) {}

void Game::run() {
  InitWindow(500, 500, "Sokoban");

  while (!WindowShouldClose()) {
    level.movePlayer();  

    BeginDrawing();
      ClearBackground(BLACK);
      render();
    EndDrawing();
  }
}

void Game::render() {
  int scale = 20;
  int gridWidth = level.longestRow * scale;
  int gridHeight = level.grid.size() * scale;

  int offsetX = (500 - gridWidth) / 2;
  int offsetY = (500 - gridHeight) / 2;

  for (size_t i = 0; i < level.grid.size(); ++i) {
    for (size_t j = 0; j < level.grid[i].size(); ++j) {
      Color color {};
      if (level.grid[i][j] == 'X') color = RAYWHITE;
      if (level.grid[i][j] == 'G') color = RED;
      if (level.grid[i][j] == 'B') color = BLUE;
      if (level.grid[i][j] == 'P') color = PINK;

      DrawRectangle(offsetX + j * scale, offsetY + i * scale, scale, scale, color);
    }
  }
}
