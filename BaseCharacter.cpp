#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(){

}

void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec(){
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
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

    if(Vector2Length(velocity) != 0.0){
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    } else {
        texture = idle;
    }

    velocity = {};

    // draw the character
    Rectangle spriteSource{frame * (float)width, 0, rightLeft * width, height};
    Rectangle spriteDest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, spriteSource, spriteDest, Vector2{}, 0.f, WHITE);
}