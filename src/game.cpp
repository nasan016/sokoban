#include "../include/game.h"
#include <iostream>
#include "raylib.h"

enum class State {
  MENU,
  LEVEL_SELECT,
  PLAY,
};

Game::Game(std::string_view inFile) :
  level(inFile) {
    InitWindow(500, 500, "Sokoban");
    spriteSheet = LoadTexture("game_sprites.png");
  }

void Game::run() {

  while (!WindowShouldClose()) {
    level.movePlayer();  

    BeginDrawing();
      ClearBackground(BLACK);
      renderLevel();
    EndDrawing();
  }
  //UnloadTexture(spriteSheet);
  CloseWindow();
}

Game::~Game() {
  UnloadTexture(spriteSheet);
  CloseWindow();
}

void Game::renderLevel() {
  const int spriteWidth { 8 };
  const int spriteHeight { 8 };
  int selectSprite { -1 };

  const int scale = 30;
  const int gridWidth = level.longestRow * scale;
  const int gridHeight = level.grid.size() * scale;

  const int offsetX = (500 - gridWidth) / 2;
  const int offsetY = (500 - gridHeight) / 2;

  for (size_t i = 0; i < level.grid.size(); ++i) {
    for (size_t j = 0; j < level.grid[i].size(); ++j) {
      if (level.grid[i][j] == ' ') continue;

      if (level.grid[i][j] == 'G') selectSprite = 3;
      if (level.grid[i][j] == 'X') selectSprite = 2;
      if (level.grid[i][j] == 'B') selectSprite = 1;
      if (level.grid[i][j] == 'P') selectSprite = 0;

      Rectangle sourceRect = { 
        static_cast<float>(selectSprite * spriteWidth), 
        0, 
        spriteWidth, 
        spriteHeight 
      };

      Rectangle destRect = {
        static_cast<float>(offsetX + j * scale), 
        static_cast<float>(offsetY + i * scale), 
        scale, 
        scale
      };

      DrawTexturePro(spriteSheet, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
    }
  }
}
