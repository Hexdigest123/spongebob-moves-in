#include "scene_manager.h"
#include "../config/ini.h"
#include "intro.h"
#include "menu.h"

static SceneId currScene = SCENE_MENU;

void SceneManager_Init(SceneId startScene, Config *cf) {
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
  default:
    break;
  }
}

void SceneManager_Draw(void) {
  switch (currScene) {
  case SCENE_INTRO:
    IntroScene_Draw();
    break;
  case SCENE_MENU:
    MenuScene_Draw();
    break;
  default:
    break;
  }
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
  default:
    break;
  }
}

void SceneManager_Unload(void) { IntroScene_Unload(); }
