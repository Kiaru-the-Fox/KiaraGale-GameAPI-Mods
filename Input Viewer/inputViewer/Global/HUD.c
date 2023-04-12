#include "../../GameAPI/C/GameAPI/Game.h"
#include "HUD.h"

ObjectHUD* HUD;
ModObjectHUD* ModHUD;

void HUD_Update()
{
    RSDK_THIS(HUD);
    Mod.Super(HUD->classID, SUPER_UPDATE, NULL);

    HUD_HandleInputViewer();
}

void HUD_Draw()
{
    Mod.Super(HUD->classID, SUPER_DRAW, NULL);
    RSDK_THIS(HUD);

    Vector2 drawPos, inputPos;
    inputPos.x = ModHUD->inputPos.x;
    inputPos.y = ModHUD->inputPos.y;

    // D-pad
    drawPos.x = inputPos.x;
    drawPos.y = inputPos.y - TO_FIXED(6);
    RSDK.DrawSprite(&ModHUD->inputDpadAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputUpAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputDownAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputLeftAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputRightAnimator, &drawPos, true);

    // ABC
    drawPos.x = inputPos.x + TO_FIXED(28);
    drawPos.y = inputPos.y - TO_FIXED(6);
    RSDK.DrawSprite(&ModHUD->inputABCAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputAAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputBAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputCAnimator, &drawPos, true);

    // XYZ
    drawPos.x = inputPos.x + TO_FIXED(28);
    drawPos.y = inputPos.y - TO_FIXED(18);
    RSDK.DrawSprite(&ModHUD->inputXYZAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputXAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputYAnimator, &drawPos, true);
    RSDK.DrawSprite(&ModHUD->inputZAnimator, &drawPos, true);
}

void HUD_Create(void* data)
{
    Mod.Super(HUD->classID, SUPER_CREATE, data);
    RSDK_THIS(HUD);

    ModHUD->inputPos.x = TO_FIXED(16);
    ModHUD->inputPos.y = TO_FIXED(ScreenInfo->size.y - 32);

    // D-Pad
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 0, &ModHUD->inputDpadAnimator, true, 0);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 1, &ModHUD->inputUpAnimator, true, 1);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 1, &ModHUD->inputDownAnimator, true, 2);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 1, &ModHUD->inputLeftAnimator, true, 3);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 1, &ModHUD->inputRightAnimator, true, 4);

    // ABC
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 2, &ModHUD->inputABCAnimator, true, 0);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 3, &ModHUD->inputAAnimator, true, 1);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 3, &ModHUD->inputBAnimator, true, 2);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 3, &ModHUD->inputCAnimator, true, 3);

    // XYZ
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 4, &ModHUD->inputXYZAnimator, true, 0);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 5, &ModHUD->inputXAnimator, true, 1);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 5, &ModHUD->inputYAnimator, true, 2);
    RSDK.SetSpriteAnimation(ModHUD->inputViewFrames, 5, &ModHUD->inputZAnimator, true, 3);
}

void HUD_StageLoad()
{
    Mod.Super(HUD->classID, SUPER_STAGELOAD, NULL);
    ModHUD->inputViewFrames = RSDK.LoadSpriteAnimation("Global/InputView.bin", SCOPE_STAGE);
}

void HUD_HandleInputViewer(void)
{
    RSDK_THIS(HUD);
    EntityPlayer* leader = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
    RSDKControllerState* controller = &ControllerInfo[leader->controllerID];
    RSDKAnalogState* joystick = &AnalogStickInfoL[leader->controllerID];

    if (controller->keyUp.press || controller->keyUp.down || joystick->keyUp.press || joystick->keyUp.down) {
        ModHUD->inputUpAnimator.frameID = 1;
    }
    else {
        ModHUD->inputUpAnimator.frameID = 0;
    }

    if (controller->keyDown.press || controller->keyDown.down || joystick->keyDown.press || joystick->keyDown.down) {
        ModHUD->inputDownAnimator.frameID = 2;
    }
    else {
        ModHUD->inputDownAnimator.frameID = 0;
    }

    if (controller->keyLeft.press || controller->keyLeft.down || joystick->keyLeft.press || joystick->keyLeft.down) {
        ModHUD->inputLeftAnimator.frameID = 3;
    }
    else {
        ModHUD->inputLeftAnimator.frameID = 0;
    }

    if (controller->keyRight.press || controller->keyRight.down || joystick->keyRight.press || joystick->keyRight.down) {
        ModHUD->inputRightAnimator.frameID = 4;
    }
    else {
        ModHUD->inputRightAnimator.frameID = 0;
    }

    if (controller->keyA.press || controller->keyA.down) {
        ModHUD->inputAAnimator.frameID = 1;
    }
    else {
        ModHUD->inputAAnimator.frameID = 0;
    }

    if (controller->keyB.press || controller->keyB.down) {
        ModHUD->inputBAnimator.frameID = 2;
    }
    else {
        ModHUD->inputBAnimator.frameID = 0;
    }

    if (controller->keyC.press || controller->keyC.down) {
        ModHUD->inputCAnimator.frameID = 3;
    }
    else {
        ModHUD->inputCAnimator.frameID = 0;
    }

    if (controller->keyX.press || controller->keyX.down) {
        ModHUD->inputXAnimator.frameID = 1;
    }
    else {
        ModHUD->inputXAnimator.frameID = 0;
    }

    if (controller->keyY.press || controller->keyY.down) {
        ModHUD->inputYAnimator.frameID = 2;
    }
    else {
        ModHUD->inputYAnimator.frameID = 0;
    }

    if (controller->keyZ.press || controller->keyZ.down) {
        ModHUD->inputZAnimator.frameID = 3;
    }
    else {
        ModHUD->inputZAnimator.frameID = 0;
    }
}