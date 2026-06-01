#include "intro.h"
#include "../video/player.h"
#include "scene_manager.h"
#include <raylib.h>

static MediaStream introMedia;
static bool introLoaded;
static bool isFinished;

void IntroScene_Init(void) {
  introMedia = LoadMediaEx("./assets/video/general/1_intro.m4v", MEDIA_LOAD_AV);
  introLoaded = IsMediaValid(introMedia);
  SetAudioStreamVolume(introMedia.audioStream, 0.5f);
  isFinished = false;

  if (!introLoaded) {
    SceneManager_ChangeScene(SCENE_MENU);
  }
}

void IntroScene_Update(void) {
  if (!introLoaded) {
    return;
  }

  UpdateMedia(&introMedia);

  if (GetMediaState(introMedia) == MEDIA_STATE_STOPPED) {
    isFinished = true;
  }
}

void IntroScene_Draw(void) {
  if (!introLoaded) {
    return;
  }

  Rectangle source = {0, 0, (float)introMedia.videoTexture.width,
                      (float)introMedia.videoTexture.height};
  Rectangle dest = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};

  DrawTexturePro(introMedia.videoTexture, source, dest, (Vector2){0, 0}, 0.0f,
                 WHITE);
}

void IntroScene_Unload(void) {
  if (!introLoaded) {
    return;
  }

  UnloadMedia(&introMedia);
  introMedia = (MediaStream){0};
  introLoaded = false;
}

bool IntroScene_Finished(void) { return isFinished; }
