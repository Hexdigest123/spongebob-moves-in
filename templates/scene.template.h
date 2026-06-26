#ifndef __SCENE_GUARD__
#define __SCENE_GUARD__

#include <stdbool.h>

void __SCENE_SYMBOL__Scene_Init(void);
void __SCENE_SYMBOL__Scene_Update(void);
void __SCENE_SYMBOL__Scene_Draw(void);
void __SCENE_SYMBOL__Scene_Unload(void);
bool __SCENE_SYMBOL__Scene_Finished(void);

#endif
