#include "../../GameAPI/C/GameAPI/Game.h"
#include "HUD.h"

ObjectHUD* HUD;
ModObjectHUD* ModHUD;
EntityPlayer* Player;

void (*Player_State_Transform)(void);

void HUD_Update()
{
    RSDK_THIS(HUD);
    Mod.Super(HUD->classID, SUPER_UPDATE, NULL);

    HUD_HandlePowerupsDisplay();
}

void HUD_Draw()
{
    Mod.Super(HUD->classID, SUPER_DRAW, NULL);
    RSDK_THIS(HUD);

    Vector2 drawPos, itemPos;
    itemPos.x = ModHUD->itemPos.x;
    itemPos.y = ModHUD->itemPos.y;

    // Icon 1
    drawPos.x = itemPos.x;
    drawPos.y = itemPos.y;
    RSDK.DrawSprite(&ModHUD->itemBox1Animator, &drawPos, true);

    // Icon 2
    drawPos.x = itemPos.x + TO_FIXED(18);
    drawPos.y = itemPos.y;
    RSDK.DrawSprite(&ModHUD->itemBox2Animator, &drawPos, true);

    // Icon 3
    drawPos.x = itemPos.x + TO_FIXED(36);
    drawPos.y = itemPos.y;
    RSDK.DrawSprite(&ModHUD->itemBox3Animator, &drawPos, true);
}

void HUD_Create(void* data)
{
    Mod.Super(HUD->classID, SUPER_CREATE, data);
    RSDK_THIS(HUD);

    ModHUD->itemPos.x = TO_FIXED(16);
    ModHUD->itemPos.y = TO_FIXED(60);

    RSDK.SetSpriteAnimation(ModHUD->powerupFrames, 0, &ModHUD->itemBox1Animator, true, 0);
    RSDK.SetSpriteAnimation(ModHUD->powerupFrames, 0, &ModHUD->itemBox2Animator, true, 0);
    RSDK.SetSpriteAnimation(ModHUD->powerupFrames, 0, &ModHUD->itemBox3Animator, true, 0);
}

void HUD_StageLoad()
{
    Mod.Super(HUD->classID, SUPER_STAGELOAD, NULL);
    ModHUD->powerupFrames = RSDK.LoadSpriteAnimation("Global/PowerupDisplay.bin", SCOPE_STAGE);
}

void HUD_HandlePowerupsDisplay(void)
{
    RSDK_THIS(HUD);
    EntityPlayer* leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    if (leader->state != Player_State_Transform && leader->superState < SUPERSTATE_SUPER) {
        if (leader->invincibleTimer > 0) {
            if (leader->invincibleTimer > 180) {
                ModHUD->itemBox1Animator.frameID = 5;
            }
            else {
                if (leader->invincibleTimer & 4)
                    ModHUD->itemBox1Animator.frameID = 0;
                if (leader->invincibleTimer & 8)
                    ModHUD->itemBox1Animator.frameID = 5;
            }
        }
        else
            ModHUD->itemBox1Animator.frameID = 0;
    }
    else {
        if (leader->rings > 0) {
            if (leader->rings > 5) {
                ModHUD->itemBox1Animator.frameID = 7;
            }
            else {
                if (leader->superRingLossTimer & 4)
                    ModHUD->itemBox1Animator.frameID = 0;
                if (leader->superRingLossTimer & 8) {
                    ModHUD->itemBox1Animator.frameID = 7;
                }
            }
        }
        else {
            ModHUD->itemBox1Animator.frameID = 0;
        }
    }

    if (leader->speedShoesTimer > 0) {
        if (leader->speedShoesTimer > 180) {
            ModHUD->itemBox2Animator.frameID = 6;
        }
        else {
            if (leader->speedShoesTimer & 4) {
                ModHUD->itemBox2Animator.frameID = 6;
            }
            if (leader->speedShoesTimer & 8) {
                ModHUD->itemBox2Animator.frameID = 0;
            }
        }
    }
    else {
        ModHUD->itemBox2Animator.frameID = 0;
    }

    if (leader->shield > SHIELD_NONE) {
        switch (leader->shield) {
        default:
        case SHIELD_BLUE: ModHUD->itemBox3Animator.frameID = 1; break;
        case SHIELD_BUBBLE: ModHUD->itemBox3Animator.frameID = 2; break;
        case SHIELD_FIRE: ModHUD->itemBox3Animator.frameID = 3; break;
        case SHIELD_LIGHTNING: ModHUD->itemBox3Animator.frameID = 4; break;
        }
    }
    else {
        ModHUD->itemBox3Animator.frameID = 0;
    }
}