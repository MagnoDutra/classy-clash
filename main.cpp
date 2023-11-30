#include "raylib.h"

int main(){
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D worldMap = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 worldMapPos{0.0, 0.0};
        DrawTextureEx(worldMap, worldMapPos, 0, 4.0, WHITE);
        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow();
}