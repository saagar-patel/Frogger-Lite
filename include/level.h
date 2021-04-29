#pragma once

#include "cinder/gl/gl.h"
#include "Player.h"
#include "Car_Obstacle.h"
#include "Road.h"


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
    
    explicit Level();
    
    void Display() const;
    
    void AdvanceOneFrame();
    
    static Player CreatePlayer(const vec2& position, int lives, float radius);
    
    Player GetPlayer();
    
    void MovePlayer();

  private:
    vec2 kPlayerSpawnPoint = vec2(1200, 1930);
    vec2 kLevelObjective = vec2(1200, 200);
    std::vector<vec2> kR1Spawnpoints = {vec2(-100, 1785), vec2(2400, 1785)};
    std::vector<vec2> kR2Spawnpoints = {vec2(-100, 1640), vec2(2400, 1640)};
    std::vector<vec2> kR3Spawnpoints = {vec2(-100, 1500), vec2(2400, 1500)};
    std::vector<vec2> kR4Spawnpoints = {vec2(-100, 1360), vec2(2400, 1360)};
    std::vector<vec2> kR5Spawnpoints = {vec2(-100, 1220), vec2(2400, 1220)};
    float kMinSpeed = 5;
    float kMaxSpeed = 15;
    float kBaseDifficultyScalar = 0.1f;
    float kDifficultyDenominator = 4000.0f;
    int kNumCarsR1 = 6;
    int kNumCarsR2 = 2;
    int kNumCarsR3 = 5;
    int kNumCarsR4 = 4;
    int kNumCarsR5 = 3;
    float kDefaultRadius = 30;
    float kObjectiveRadius = 20;
    float kRightWall = 2400;
    float kLeftWall = 0;
    float kTopWall = 150;
    float kBottomWall = 2000;
    int kLives = 3;
    
    std::vector<Road> car_roads_;
//    std::vector<>
    Player player_;
    
    void ExecuteWallCollision();
    
    void ExecuteLevelCompletion();
    
    void DrawLevelObjective(const vec2& level_goal) const;
    
    double CountElapsedTime();

    void DecreaseLives();
    
    void ResetPlayerPosition();
    
    void PopulateRoads();
    
    void UpdateRoadDirections();
};
}
