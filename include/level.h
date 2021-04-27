#pragma once

#include "cinder/gl/gl.h"
#include "Player.h"
#include "Car_Obstacle.h"


using glm::vec2;

namespace frogger {
class Level {
  public:
    int score_;
    unsigned level_count_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
    std::chrono::time_point<std::chrono::steady_clock> end_time_;
    
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
    vec2 kLevelObjective = vec2(1200, 200);
    float kDefaultRadius = 30;
    float kObjectiveRadius = 20;
    float kRightWall = 2400;
    float kLeftWall = 0;
    float kTopWall = 150;
    float kBottomWall = 2000;
    
    std::vector<Car> road_one_;
    std::vector<Car> road_two_;
    std::vector<Car> road_three_;
    
    Player player_;
    
    void ExecuteWallCollision();
    
    void ExecuteLevelCompletion();
    
    void DrawLevelObjective(const vec2& level_goal) const;
    
    double CountElapsedTime();
    
//    void CreateCarObstacles();

    void DecreaseLives();
    
    void ResetPlayerPosition();
};
}
