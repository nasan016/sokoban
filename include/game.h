#pragma once
#include <string>
#include "raylib.h"
#include "level.h"

class Game {
  public:
    Game(std::string_view inFile);
    ~Game();
    void run();

  private:
    Level level;
    Texture2D spriteSheet;
    void renderLevel();
};
