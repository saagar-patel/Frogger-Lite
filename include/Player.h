#pragma once

#include "cinder/gl/gl.h"

namespace frogger {

using glm::vec2;

class Player {
  public:
    Player(const vec2& position, const int& lives, float radius);
    
    void MoveUp();
    void MoveRight();
    void MoveLeft();
    void MoveDown();
    void StreamMovement(bool l_to_r, float move_speed, float difficulty_scalar);
    
    void DrawPlayer() const;
    
    const vec2 &GetPosition() const;

    void SetPosition(const vec2& vec);

    float GetRadius() const;

    int GetLives() const;

    void SetLives(int lives);

private:
    float kMoveDistance = 10;
    
    float radius_;
    vec2 position_;
    int lives_;
};
}