#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

int main(){
    const int windowWidth{384};
    const int windowHeight{384};
    const float mapScale{4.0f};
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D worldMap = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight{windowWidth, windowHeight};

    // Draw props
    Prop propList[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    goblin.setTarget(&knight);

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
    };

    Enemy* enemys[]{
        &goblin,
        &slime
    };

    for(auto enemy : enemys){
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw Map
        DrawTextureEx(worldMap, mapPos, 0, mapScale, WHITE);

        for (auto prop : propList)
        {
            prop.render(knight.getWorldPos());
        }
        
        if(!knight.getAlive()){
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }else{
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        for(auto enemy : enemys){
            enemy->tick(GetFrameTime());
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            for(auto enemy : enemys){
                bool isCollided = CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec());
                if(isCollided) { enemy->setAlive(false); }
            }
        }
        // check map bounds
        knight.tick(GetFrameTime());
        
        if(knight.getWorldPos().x < 0.f ||
           knight.getWorldPos().y < 0.f ||
           knight.getWorldPos().x + windowWidth > worldMap.width * mapScale ||
           knight.getWorldPos().y + windowHeight > worldMap.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : propList)
        {
            bool isColliding = CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec());
            if(isColliding){
                knight.undoMovement();
            }
        }
        

        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow();
}