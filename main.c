#include "config/ini.h"
#include "raylib.h"
#include "video/player.h"
#include <stdlib.h>
#include <string.h>

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

typedef struct {
  const char *version;
  const char *name;
  int width;
  int height;
  int fps;
  bool fullscreen;
  int volume;
} configuration;

static int LoadConfigurationHandler(void *config, const char *section,
                                    const char *name, const char *value) {
  configuration *pconfig = (configuration *)config;

  if (MATCH("general", "version")) {
    pconfig->version = strdup(value);
  } else if (MATCH("general", "name")) {
    pconfig->name = strdup(value);
  } else if (MATCH("graphics", "width")) {
    pconfig->width = atoi(value);
  } else if (MATCH("graphics", "height")) {
    pconfig->height = atoi(value);
  } else if (MATCH("graphics", "fps")) {
    pconfig->fps = atoi(value);
  } else if (MATCH("graphics", "fullscreen")) {
    pconfig->fullscreen = (strcmp(value, "true") == 0);
  } else {
    return 0; /* unknown section/name, error */
  }
  return 1;
}

int main(void) {

  configuration config;

  if (ini_parse("config.ini", LoadConfigurationHandler, &config) < 0) {
    printf("Can't load 'config.ini'\n");
    return 1;
  }

  SetTargetFPS(config.fps);
  InitWindow(config.width, config.height, config.name);
  InitAudioDevice();

  Font spongebobFont =
      LoadFontEx("./assets/fonts/spongebob-font.otf", 100, NULL, 0);
  Font textFont = LoadFontEx("./assets/fonts/roboto.ttf", 100, NULL, 0);
  MediaStream mStreamIntro =
      LoadMediaEx("./assets/video/general/1_intro.m4v", MEDIA_LOAD_AV);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

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
  return 0;
}
