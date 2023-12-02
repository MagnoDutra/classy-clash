#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight){
    width = texture.width/maxFrames;
    height = texture.height;

    screenPos = {
        static_cast<float>(winWidth)/2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight)/2.0f - scale * (0.5f * height)
    };    
}

void Character::tick(float deltaTime){
    worldPosLastFrame = worldPos;

    Vector2 direction{};
    if(IsKeyDown(KEY_A)) direction.x -= 1.0;
    if(IsKeyDown(KEY_D)) direction.x += 1.0;
    if(IsKeyDown(KEY_W)) direction.y -= 1.0;
    if(IsKeyDown(KEY_S)) direction.y += 1.0;

    if(Vector2Length(direction) != 0.0){
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), SPEED));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    } else {
        texture = idle;
    }

    runningTime += deltaTime;

    if(runningTime >= updateTime){
        frame = ++frame % maxFrames;
        runningTime = 0.f;            
    }

    Rectangle spriteSource{frame * (float)width, 0, rightLeft * width, height};
    Rectangle spriteDest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, spriteSource, spriteDest, Vector2{}, 0.f, WHITE);        
}

void Character::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle Character::getCollisionRec(){
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}