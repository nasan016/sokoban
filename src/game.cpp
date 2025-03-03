#include "../include/game.h"
#include <iostream>
#include "raylib.h"

enum class STATE {
  MENU,
  LEVEL_SELECT,
  PLAY,
};

STATE CURRENT_STATE { STATE::MENU };

const int WIDTH = 500;
const int HEIGHT = 500;

Game::Game(std::string_view inFile) :
  level(inFile) {
    InitWindow(WIDTH, HEIGHT, "Sokoban");
    spriteSheet = LoadTexture("game_sprites.png");
  }

void Game::run() {
  while (!WindowShouldClose()) {
    level.movePlayer();  

    BeginDrawing();

      ClearBackground(BLACK);
      
      switch (CURRENT_STATE) {
        case STATE::MENU:
          renderMenu();
          break;

        case STATE::LEVEL_SELECT:
          break;

        case STATE::PLAY:
          renderLevel();
          break;
      }

    EndDrawing();
  }
  CloseWindow();
}

void Game::renderMenu() {
  const char* title { "Sokoban!" };
  const char* subString { "Press Enter" };

  const int titleSize { 40 };
  const int subStringSize { 25 };

  int titleWidth = MeasureText(title, titleSize);
  int subStringWidth = MeasureText(subString, subStringSize);

  int xTitle = (WIDTH - titleWidth) / 2;
  int yTitle = (HEIGHT - titleSize) / 2;
  int xSub = (WIDTH - subStringWidth) / 2;
  int ySub = (HEIGHT - subStringSize + 60) / 2;

  DrawText(title, xTitle, yTitle, titleSize, RAYWHITE);
  DrawText(subString, xSub, ySub, subStringSize, RAYWHITE);

  if (IsKeyPressed(KEY_ENTER)) CURRENT_STATE = STATE::PLAY; 
}

void Game::renderLevel() {
  const int spriteDimensions{ 8 };
  int selectSprite { -1 };

  const int scale = 35;
  const int gridWidth = level.longestRow * scale;
  const int gridHeight = level.grid.size() * scale;

  const int offsetX = (WIDTH - gridWidth) / 2;
  const int offsetY = (HEIGHT - gridHeight) / 2;

  for (size_t i = 0; i < level.grid.size(); ++i) {
    for (size_t j = 0; j < level.grid[i].size(); ++j) {
      if (level.grid[i][j] == ' ') continue;

      if (level.grid[i][j] == 'G') selectSprite = 3;
      if (level.grid[i][j] == 'X') selectSprite = 2;
      if (level.grid[i][j] == 'B') selectSprite = 1;
      if (level.grid[i][j] == 'P') selectSprite = 0;

      Rectangle sourceRect = { 
        static_cast<float>(selectSprite * spriteDimensions), 
        0, 
        spriteDimensions, 
        spriteDimensions 
      };

      Rectangle destRect = {
        static_cast<float>(offsetX + j * scale), 
        static_cast<float>(offsetY + i * scale), 
        scale, 
        scale
      };

      DrawTexturePro(spriteSheet, sourceRect, destRect, { 0, 0 }, 0, WHITE);
    }
  }
}
