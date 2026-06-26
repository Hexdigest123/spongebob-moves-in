#include "scene_manager.h"
#include "../config/ini.h"
#include "intro.h"
#include "menu.h"
#include "settings.h"
#include <math.h>
#include <raylib.h>

static SceneId currScene = SCENE_MENU;
static RenderTexture2D renderTarget;
static float renderScale = 1.0f;
static Vector2 renderOffset = {0, 0};
Font fontSpongebob;
Font fontText;
Music musicBackground;
Sound soundClick;
Image imgSettingsBackground;
Texture2D textureWallpaper;
Texture2D textureSettingsBackground;
Texture2D uiTextures;
Rectangle recBtnContinueSrc;
Rectangle recSettingsSrc;
Rectangle recHomeSrc;
Rectangle recCancelSrc;
Rectangle recConfirmSrc;
Rectangle recDeclneSrc;

static bool requestQuit = false;

void SceneManager_Init(SceneId startScene, Config *cf) {
  fontSpongebob = LoadFontEx("./assets/fonts/spongebob-font.otf", 100, NULL, 0);
  fontText = LoadFontEx("./assets/fonts/roboto.ttf", 100, NULL, 0);
  soundClick = LoadSound("./assets/audio/ui/tap_screen2.wav");
  musicBackground =
      LoadMusicStream("./assets/audio/music/MUSIC_InGame_MultiMix.wav");
  Image imgWallpaper = LoadImage("./assets/ui/sprites/title_wallpaper.png");
  textureWallpaper = LoadTextureFromImage(imgWallpaper);

  imgSettingsBackground = LoadImage("./assets/ui/sprites/StoreBackground.png");
  textureSettingsBackground = LoadTextureFromImage(imgSettingsBackground);

  uiTextures = LoadTexture("assets/ui/sprites/SpongebobUI.png");
  UnloadImage(imgWallpaper);

  recBtnContinueSrc = (Rectangle){716, 1089, 314, 110};
  recSettingsSrc = (Rectangle){1159, 1859, 85, 86};
  recHomeSrc = (Rectangle){972, 1951, 90, 90};
  recCancelSrc = (Rectangle){1484, 1749, 83, 86};
  recConfirmSrc = (Rectangle){1432, 1844, 74, 71};
  recDeclneSrc = (Rectangle){1351, 1857, 67, 65};

  renderTarget = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
  SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_BILINEAR);

  currScene = startScene;
  if (cf->intro) {
    SceneManager_ChangeScene(SCENE_INTRO);
  }
  SceneManager_ChangeScene(currScene);
}

void SceneManager_Update(void) {
  switch (currScene) {
  case SCENE_INTRO:
    IntroScene_Update();
    if (IntroScene_Finished()) {
      ini_write_pair("game", "intro", "false");
      SceneManager_ChangeScene(SCENE_MENU);
    }
    break;
  case SCENE_MENU:
    MenuScene_Update();
    break;
  case SCENE_SETTINGS:
    SettingsScene_Update();
    break;
  default:
    break;
  }
}

void SceneManager_Draw(void) {
  BeginTextureMode(renderTarget);
  ClearBackground(BLACK);

  switch (currScene) {
  case SCENE_INTRO:
    IntroScene_Draw();
    break;
  case SCENE_MENU:
    MenuScene_Draw();
    break;
  case SCENE_SETTINGS:
    SettingsScene_Draw();
    break;
  default:
    break;
  }

  EndTextureMode();

  int winW = GetScreenWidth();
  int winH = GetScreenHeight();
  renderScale = fminf((float)winW / (float)VIRTUAL_WIDTH,
                      (float)winH / (float)VIRTUAL_HEIGHT);
  float drawW = (float)VIRTUAL_WIDTH * renderScale;
  float drawH = (float)VIRTUAL_HEIGHT * renderScale;
  renderOffset.x = ((float)winW - drawW) * 0.5f;
  renderOffset.y = ((float)winH - drawH) * 0.5f;

  ClearBackground(BLACK);

  Rectangle src = {0, 0, (float)VIRTUAL_WIDTH, -(float)VIRTUAL_HEIGHT};
  Rectangle dst = {renderOffset.x, renderOffset.y, drawW, drawH};
  DrawTexturePro(renderTarget.texture, src, dst, (Vector2){0, 0}, 0, WHITE);
}

Vector2 GetVirtualMousePosition(void) {
  Vector2 m = GetMousePosition();
  return (Vector2){(m.x - renderOffset.x) / renderScale,
                   (m.y - renderOffset.y) / renderScale};
}

void SceneManager_ChangeScene(SceneId nextScene) {
  switch (nextScene) {
  case SCENE_INTRO:
    IntroScene_Init();
    currScene = SCENE_INTRO;
    break;
  case SCENE_MENU:
    MenuScene_Init();
    currScene = SCENE_MENU;
    break;
  case SCENE_SETTINGS:
    SettingsScene_Init();
    currScene = SCENE_SETTINGS;
    break;
  default:
    break;
  }
}

void SceneManager_Unload(void) {
  IntroScene_Unload();
  MenuScene_Unload();
  SettingsScene_Unload();
  UnloadRenderTexture(renderTarget);
  UnloadTexture(textureWallpaper);
  UnloadTexture(uiTextures);
  UnloadFont(fontSpongebob);
  UnloadFont(fontText);
  StopMusicStream(musicBackground);
  UnloadMusicStream(musicBackground);
}

void SceneManager_RequestQuit(void) { requestQuit = true; }
bool SceneManager_ShouldQuit(void) { return requestQuit; }
