#include "menu.h"
#include "scene_manager.h"
#include <raylib.h>
#include <stdio.h>

static Font spongebobFont;
static Font textFont;
static Music bgMusic;
static Texture2D wallpaperTexture;
static Texture2D uiTextures;
float continueButtonScale = 1;
const static Rectangle continueButtonSrc = (Rectangle){716, 1089, 314, 110};
const static Rectangle settingsSrc = (Rectangle){1159, 1859, 85, 86};
const static Rectangle homeSrc = (Rectangle){972, 1951, 90, 90};
const Rectangle homeButtonPos = {.x = 50, .y = 50, .width = 100, .height = 100};
const Rectangle settingButtonPos = {
    .x = 1750, .y = 50, .width = 100, .height = 100};
const Rectangle continueButtonPos = {
    .x = 650, .y = 800, .width = 600, .height = 200};

void MenuScene_Init(void) {
  spongebobFont = LoadFontEx("./assets/fonts/spongebob-font.otf", 100, NULL, 0);
  textFont = LoadFontEx("./assets/fonts/roboto.ttf", 100, NULL, 0);

  bgMusic = LoadMusicStream("./assets/audio/music/MUSIC_InGame_MultiMix.wav");
  bgMusic.looping = true;
  SetMusicVolume(bgMusic, 0.2);
  PlayMusicStream(bgMusic);
  float bgMusicTimePlayed = GetMusicTimePlayed(bgMusic);
  float bgMusicTimeLength = GetMusicTimeLength(bgMusic);
  if (bgMusicTimePlayed + 300 < bgMusicTimeLength) {
    SeekMusicStream(bgMusic, bgMusicTimePlayed + 300);
  }

  Image imgWallpaper = LoadImage("./assets/ui/sprites/title_wallpaper.png");
  wallpaperTexture = LoadTextureFromImage(imgWallpaper);
  uiTextures = LoadTexture("assets/ui/sprites/SpongebobUI.png");

  UnloadImage(imgWallpaper);
}

void MenuScene_Draw(void) {
  Vector2 mousePosition = GetMousePosition();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(
          mousePosition,
          (Rectangle){.x = 50, .y = 50, .width = 100, .height = 100})) {
    SceneManager_RequestQuit();
  }

  DrawTextureEx(wallpaperTexture, (Vector2){0, 0}, 0, 1, WHITE);
  DrawTexturePro(uiTextures, homeSrc, homeButtonPos, (Vector2){}, 0, WHITE);
  DrawTexturePro(uiTextures, settingsSrc, settingButtonPos, (Vector2){}, 0,
                 WHITE);
  DrawTexturePro(uiTextures, continueButtonSrc, continueButtonPos, (Vector2){},
                 continueButtonScale, WHITE);

  DrawTextPro(spongebobFont, "Continue", (Vector2){.x = 755, .y = 860},
              (Vector2){}, continueButtonScale, 100, 1, GetColor(0xE9AB30FF));
}

void MenuScene_Update(void) {

  Vector2 mousePosition = GetMousePosition();
  bool continueHovered =
      CheckCollisionPointRec(mousePosition, continueButtonPos);

  float targetScale = continueHovered ? 1.25f : 1.0f;

  float speed = 10.0f;
  float t = speed * GetFrameTime();
  if (t > 1.0f)
    t = 1.0f;

  continueButtonScale += (targetScale - continueButtonScale) * t;
  UpdateMusicStream(bgMusic);
}

void MenuScene_Unload(void) {
  UnloadTexture(wallpaperTexture);
  UnloadTexture(uiTextures);
  UnloadFont(spongebobFont);
  UnloadFont(textFont);
  StopMusicStream(bgMusic);
  UnloadMusicStream(bgMusic);
}

bool MenuScene_Finished(void) { return false; }
