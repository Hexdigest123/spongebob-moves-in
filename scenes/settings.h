#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>

void SettingsScene_Init(void);
void SettingsScene_Update(void);
void SettingsScene_Draw(void);
void SettingsScene_Unload(void);
bool SettingsScene_Finished(void);

#endif
