#include "../../GameAPI/C/GameAPI/Game.h"
#include "Global/HUD.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void) {
	MOD_REGISTER_OBJ_OVERLOAD_MSV(HUD, ModHUD, HUD_Update, NULL, NULL, HUD_Draw, HUD_Create, HUD_StageLoad , NULL, NULL, NULL);
}

#if RETRO_USE_MOD_LOADER
#  define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id) {
#  if MANIA_USE_PLUS
	LinkGameLogicDLL(info);
#  else
	LinkGameLogicDLL(*info);
#  endif
	globals = Mod.GetGlobals();
	modID = id;
	InitModAPI();
	return true;
}
#endif
