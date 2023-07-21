#include "../../GameAPI/C/GameAPI/Game.h"
#include "Global/Player.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void) {
	Player_HandleAirFriction = Mod.GetPublicFunction(NULL, "Player_HandleAirFriction");
	Player_State_Air = Mod.GetPublicFunction(NULL, "Player_State_Air");
	Player_State_TailsFlight = Mod.GetPublicFunction(NULL, "Player_State_TailsFlight");
	Mod.RegisterStateHook(Player_State_TailsFlight, Player_State_TailsFlight_Hook, false);
	MOD_REGISTER_OBJECT_HOOK(Player);
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
