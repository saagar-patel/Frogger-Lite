#pragma once

#include "cinder/gl/gl.h"
#include "Player.h"

using glm::vec2;

namespace frogger {
class Level {
  public:
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    
    
    explicit Level(int lives);
    
    void Display() const;
    
    void AdvanceOneFrame();
    
    static Player CreatePlayer(const vec2& position, int lives, float radius);
    
    
    
    Player GetPlayer();
    
    void MovePlayer();

  private:
    vec2 kSpawnPoint = vec2(1200, 1950);
    float kDefaultRadius = 30;
    float kRightWall = 2400;
    float kLeftWall = 0;
    float kTopWall = 0;
    float kBottomWall = 2000;
    Player player_;
    
    void DrawPlayer() const;
    
    void ExecuteWallCollision();
    
    void ResetPlayerPosition();
};
}
