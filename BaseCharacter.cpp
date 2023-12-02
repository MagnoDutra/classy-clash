#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(){

}

void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec(){
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime){
    worldPosLastFrame = worldPos;

    // update animation
    runningTime += deltaTime;

    if(runningTime >= updateTime){
        frame = ++frame % maxFrames;
        runningTime = 0.f;            
    }

    // draw the character
    Rectangle spriteSource{frame * (float)width, 0, rightLeft * width, height};
    Rectangle spriteDest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, spriteSource, spriteDest, Vector2{}, 0.f, WHITE);
}