#include "config/ini.h"
#include "raylib.h"
#include "scenes/scene_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  Config config;
  int monitor;

  if (ini_parse("config.ini", LoadConfigurationHandler, &config) < 0) {
    printf("Can't load 'config.ini'\n");
    return 1;
  }

  SetTargetFPS(config.fps);
  if (config.fullscreen) {
    monitor = GetCurrentMonitor();
    ToggleFullscreen();
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor),
               config.name);
  } else {
    InitWindow(config.width, config.height, config.name);
  }
  InitAudioDevice();

  SceneManager_Init(SCENE_MENU, &config);

  while (!WindowShouldClose() && !SceneManager_ShouldQuit()) {
    SceneManager_Update();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (IsKeyPressed(KEY_F11)) {
      config.fullscreen = !config.fullscreen;
      ini_write_pair("graphics", "fullscreen",
                     config.fullscreen ? "true" : "false");
      ToggleFullscreen();
    }

    SceneManager_Draw();

    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  SceneManager_Unload();

  free((char *)config.version);
  free((char *)config.name);
  config.version = NULL;
  config.name = NULL;

  return 0;
}
