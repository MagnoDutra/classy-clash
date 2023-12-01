#include "Character.h"
#include "raymath.h"

Character::Character(){
    width = (float)texture.width/(float)maxFrames;
    height = (float)texture.height;
}

void Character::setScreenPos(int windowWidth, int windowHeight){
    screenPos = {
        (float)windowWidth/2.0f - 4.0f * (0.5f * width),
        (float)windowHeight/2.0f - 4.0f * (0.5f * height)
    };
}

void Character::tick(float deltaTime){
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
        Rectangle spriteDest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
        DrawTexturePro(texture, spriteSource, spriteDest, Vector2{}, 0.f, WHITE);        
}