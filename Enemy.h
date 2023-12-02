#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter {
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* character){ target = character; }
private:
    Character* target{};
};
