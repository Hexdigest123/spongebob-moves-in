#include "../config/ini.h"

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

typedef enum SceneId {
  SCENE_INTRO,
  SCENE_MENU,
} SceneId;

void SceneManager_Init(SceneId startScene, Config *cf);
void SceneManager_Update(void);
void SceneManager_Draw(void);
void SceneManager_ChangeScene(SceneId nextScene);
void SceneManager_Unload(void);

#endif
