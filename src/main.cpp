#include "../include/game.h"
#include "raylib.h"

int main() {
  Game game { Game("test.txt") };
  game.run();

  return 0;
}
