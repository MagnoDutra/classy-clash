#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main(){
    const int windowWidth{384};
    const int windowHeight{384};
    const float mapScale{4.0f};
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
        DrawTextureEx(worldMap, mapPos, 0, mapScale, WHITE);

        // check map bounds
        knight.tick(GetFrameTime());
        
        if(knight.getWorldPos().x < 0.f ||
           knight.getWorldPos().y < 0.f ||
           knight.getWorldPos().x + windowWidth > worldMap.width * mapScale ||
           knight.getWorldPos().y + windowHeight > worldMap.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow();
}