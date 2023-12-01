#include "raylib.h"
#include "raymath.h"

class Character{
private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};
    const float SPEED{4.f};
public:
    Vector2 getWorldPos(){ return worldPos; }
    void setScreenPos(int windowWidth, int windowHeight);
    void tick(float deltaTime);
};

void Character::setScreenPos(int windowWidth, int windowHeight){
    screenPos = {
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)texture.width/6.0f),
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)texture.height)
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

        Rectangle spriteSource{frame * (float)texture.width/6.0f, 0, rightLeft * (float)texture.width/6.0f, (float)texture.height};
        Rectangle spriteDest{screenPos.x, screenPos.y, 4.0f * (float)texture.width/6.0f, 4.0f * (float)texture.height};
        DrawTexturePro(texture, spriteSource, spriteDest, Vector2{}, 0.f, WHITE);        
}

int main(){
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D worldMap = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw Map
        DrawTextureEx(worldMap, mapPos, 0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow();
}