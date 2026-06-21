#include "menu.h"
#include "scene_manager.h"
#include <raylib.h>

float continueButtonScale = 1;
const Rectangle homeButtonPos = {.x = 50, .y = 50, .width = 100, .height = 100};
const Rectangle settingButtonPos = {
    .x = 1750, .y = 50, .width = 100, .height = 100};
const Rectangle continueButtonPos = {
    .x = 650, .y = 800, .width = 600, .height = 200};

void MenuScene_Init(void) {
  musicBackground.looping = true;
  SetMusicVolume(musicBackground, 0.2);
  PlayMusicStream(musicBackground);
  float bgMusicTimePlayed = GetMusicTimePlayed(musicBackground);
  float bgMusicTimeLength = GetMusicTimeLength(musicBackground);
  if (bgMusicTimePlayed + 300 < bgMusicTimeLength) {
    SeekMusicStream(musicBackground, bgMusicTimePlayed + 300);
  }
}

void MenuScene_Draw(void) {
  DrawTextureEx(textureWallpaper, (Vector2){0, 0}, 0, 1, WHITE);
  DrawTexturePro(uiTextures, recHomeSrc, homeButtonPos, (Vector2){}, 0, WHITE);
  DrawTexturePro(uiTextures, recSettingsSrc, settingButtonPos, (Vector2){}, 0,
                 WHITE);
  DrawTexturePro(uiTextures, recBtnContinueSrc, continueButtonPos, (Vector2){},
                 continueButtonScale, WHITE);

  DrawTextPro(fontSpongebob, "Continue", (Vector2){.x = 755, .y = 860},
              (Vector2){}, continueButtonScale, 100, 1, GetColor(0xE9AB30FF));
}

void MenuScene_Update(void) {

  Vector2 mousePosition = GetVirtualMousePosition();
  bool continueHovered =
      CheckCollisionPointRec(mousePosition, continueButtonPos);

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(mousePosition, homeButtonPos)) {
    SceneManager_RequestQuit();
  }
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(mousePosition, settingButtonPos)) {
    PlaySound(soundClick);
    SceneManager_ChangeScene(SCENE_SETTINGS);
  }

  float targetScale = continueHovered ? 1.25f : 1.0f;

  float speed = 10.0f;
  float t = speed * GetFrameTime();
  if (t > 1.0f)
    t = 1.0f;

  continueButtonScale += (targetScale - continueButtonScale) * t;
  UpdateMusicStream(musicBackground);
}

void MenuScene_Unload(void) {}

bool MenuScene_Finished(void) { return false; }
