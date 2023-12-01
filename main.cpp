#include "raylib.h"
#include "raymath.h"

class Character{
private:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};
public:
    Vector2 getWorldPos(){ return worldPos; }
};

int main(){
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D worldMap = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{4.0};

    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height)
    };    


    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;

        if(Vector2Length(direction) != 0.0){
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knightRun;
        } else {
            knight = knightIdle;
        }
        
        // Draw Map
        DrawTextureEx(worldMap, mapPos, 0, 4.0, WHITE);

        // update animation frame        
        runningTime += GetFrameTime();

        if(runningTime >= updateTime){
            frame = ++frame % maxFrames;
            runningTime = 0.f;            
        }

        

        // Draw Knight
        Rectangle spriteSource{frame * (float)knight.width/6.0f, 0, rightLeft * (float)knight.width/6.0f, (float)knight.height};
        Rectangle spriteDest{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, spriteSource, spriteDest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
    UnloadTexture(worldMap);
    UnloadTexture(knightRun);
    UnloadTexture(knightIdle);
    CloseWindow();
}