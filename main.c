#include "config/ini.h"
#include "raylib.h"
#include "video/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  configuration config;
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

  Font spongebobFont =
      LoadFontEx("./assets/fonts/spongebob-font.otf", 100, NULL, 0);
  Font textFont = LoadFontEx("./assets/fonts/roboto.ttf", 100, NULL, 0);
  MediaStream mStreamIntro =
      LoadMediaEx("./assets/video/general/1_intro.m4v", MEDIA_LOAD_AV);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (IsKeyPressed(KEY_F11)) {
      ToggleFullscreen();
    }

    Vector2 vec = {.x = 100, .y = 100};
    Vector2 vec2 = {.x = 0, .y = 0};

    DrawTextEx(spongebobFont, "Hello, raylib!", vec, 100, 10, BLACK);
    DrawTextEx(textFont, "Hello, raylib!", vec2, 100, 10, BLACK);

    Rectangle source = {0, 0, mStreamIntro.videoTexture.width,
                        mStreamIntro.videoTexture.height};

    Rectangle dest = {0, 0, GetScreenWidth(), GetScreenHeight()};

    if (GetMediaState(mStreamIntro) != MEDIA_STATE_STOPPED) {
      UpdateMedia(&mStreamIntro);
      DrawTexturePro(mStreamIntro.videoTexture, source, dest, (Vector2){0, 0},
                     0.0f, WHITE);
    }

    EndDrawing();
  }

  UnloadFont(spongebobFont);
  UnloadFont(textFont);
  UnloadMedia(&mStreamIntro);
  CloseAudioDevice();
  CloseWindow();
  free((char *)config.version);
  free((char *)config.name);
  return 0;
}
