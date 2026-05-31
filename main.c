#include "raylib.h"

int main(void) {

  InitWindow(1920, 1080, "SpongeBob Moves In!");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello raylib!", 190, 200, 30, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
