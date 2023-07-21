#include "../../GameAPI/C/GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;
void (*Player_HandleAirFriction)(void);
void (*Player_State_Air)(void);
void (*Player_State_TailsFlight)(void);

bool32 Player_State_TailsFlight_Hook(bool32 skippedState)
{
    RSDK_THIS(Player);
    RSDKControllerState* controller = &ControllerInfo[self->controllerID];
    if (controller->keyDown.down && self->jumpPress) {
        self->state = Player_State_FlightCancel;
        return false;
    }
    return false;
}

void Player_State_FlightCancel(void)
{
    RSDK_THIS(Player);

    RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
    self->state = Player_State_Air;
}