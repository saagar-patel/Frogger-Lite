#pragma once

#include "cinder/gl/gl.h"
#include "Player.h"
#include "Car_Obstacle.h"
#include "Road.h"
#include "stream.h"
#include "coin.h"

using glm::vec2;

namespace frogger {

class Level {
  public:
    int score_;
    unsigned level_count_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
    std::chrono::time_point<std::chrono::steady_clock> end_time_;
    double current_time_;
    
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    
    bool can_move = false;
    
    bool game_over = false;
    
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
    float kDifficultyDenominator = 5000.0f;
    float kMinStreamSpeed = 10;
    float kMaxStreamSpeed = 20;
    float kBaseDiffScalarStream = 0.2f;
    float kDifficultDenomStream = 6000.0f;
    std::vector<vec2> kS1Spawnpoints = {vec2(-200, 352), vec2(2500, 352)};
    std::vector<vec2> kS2Spawnpoints = {vec2(-200, 496), vec2(2500, 496)};
    std::vector<vec2> kS3Spawnpoints = {vec2(-200, 640), vec2(2500, 640)};
    std::vector<vec2> kS4Spawnpoints = {vec2(-200, 784), vec2(2500, 784)};
    std::vector<vec2> kS5Spawnpoints = {vec2(-200, 928), vec2(2500, 928)};
    float kStream1Top = 280;
    float kStream2Top = 424;
    float kStream3Top = 568;
    float kStream4Top = 712;
    float kStream5Top = 856;
    float kStream1Bot = 424;
    float kStream2Bot = 568;
    float kStream3Bot = 712;
    float kStream4Bot = 856;
    float kStream5Bot = 1000;
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
    size_t kNumCoins = 1;
    int kCoinValue = 50;
    
    std::vector<Road> car_roads_;
    std::vector<Stream> gator_streams_;
    std::vector<Coin> coins_;
    Player player_;
    
    void ExecuteWallCollision();
    
    void ExecuteLevelCompletion();
    
    void ExecuteCarCollision();
    
    void ExecuteGatorCollision();
    
    void DrawLevelObjective(const vec2& level_goal) const;
    
    double CountElapsedTime();
    
    void CountCurrentTime();

    void DecreaseLives();
    
    void ResetPlayerPosition();
    
    void PopulateRoads();
    
    void PopulateStreams();
    
    void CreateCoins();
    
    void UpdateRoadDirections();
    
    void UpdateStreamSettings();
    
    void MovePlayerInStream();
};
}
