#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width/maxFrames;
    height = texture.height;
}

void Enemy::tick(float deltaTime){
    worldPosLastFrame = worldPos;
    runningTime += deltaTime;

    if(runningTime >= updateTime){
        frame = ++frame % maxFrames;
        runningTime = 0.f;            
    }

    Rectangle spriteSource{frame * (float)width, 0, rightLeft * width, height};
    Rectangle spriteDest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, spriteSource, spriteDest, Vector2{}, 0.f, WHITE);
}