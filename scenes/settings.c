#include "settings.h"
#include "scene_manager.h"
#include <raylib.h>

void SettingsScene_Init(void) {}

void SettingsScene_Update(void) { UpdateMusicStream(musicBackground); }

void SettingsScene_Draw(void) {
  DrawTextureEx(textureWallpaper, (Vector2){0, 0}, 0, 1, WHITE);
  // DrawTexturePro(uiTextures, recHomeSrc, , (Vector2){}, 0, WHITE);
  DrawTexturePro(
      textureSettingsBackground,
      (Rectangle){.x = 0,
                  .y = 0,
                  .width = (float)imgSettingsBackground.width,
                  .height = (float)imgSettingsBackground.height},
      (Rectangle){50, 50, GetScreenWidth() - 100, GetScreenHeight() - 100},
      (Vector2){}, 0, WHITE);
}

void SettingsScene_Unload(void) {}

bool SettingsScene_Finished(void) { return false; }
