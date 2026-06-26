#include "../config/ini.h"
#include <raylib.h>

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#define VIRTUAL_WIDTH 1920
#define VIRTUAL_HEIGHT 1080

typedef enum SceneId {
  SCENE_INTRO,
  SCENE_MENU,
  SCENE_SETTINGS,
} SceneId;

extern Font fontSpongebob;
extern Font fontText;
extern Music musicBackground;
extern Sound soundClick;
extern Image imgSettingsBackground;
extern Texture2D textureWallpaper;
extern Texture2D uiTextures;
extern Texture2D textureSettingsBackground;
extern Rectangle recBtnContinueSrc;
extern Rectangle recSettingsSrc;
extern Rectangle recHomeSrc;
extern Rectangle recCancelSrc;
extern Rectangle recConfirmSrc;
extern Rectangle recDeclneSrc;

void SceneManager_Init(SceneId startScene, Config *cf);
void SceneManager_Update(void);
void SceneManager_Draw(void);
void SceneManager_ChangeScene(SceneId nextScene);
void SceneManager_Unload(void);
void SceneManager_RequestQuit(void);
bool SceneManager_ShouldQuit(void);

Vector2 GetVirtualMousePosition(void);

#endif
