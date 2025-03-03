#pragma once
#include <string>
#include "raylib.h"
#include "level.h"

class Game {
  public:
    Game(std::string_view inFile);
    void run();

  private:
    Level level;
    Texture2D spriteSheet;
    void renderMenu();
    void renderLevel();
};
