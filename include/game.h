#pragma once
#include <string>

#include "level.h"

class Game {
  public:
    Game(std::string_view inFile);
    void run();

  private:
    Level level;
    void render();
};
