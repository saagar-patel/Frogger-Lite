#pragma once

#include "cinder/gl/gl.h"
#include "player.h"
#include "car.h"
#include "road.h"
#include "stream.h"
#include "coin.h"

using glm::vec2;

namespace frogger {

class Level {
  public:
    explicit Level();
    
    void Display() const;
    
    void AdvanceOneFrame();
    
    static Player CreatePlayer(const vec2& position, int lives, float radius);
    
    Player GetPlayer();
    
    void MovePlayer();

    void ResetPlayerPosition();

    int GetScore() const;

    unsigned int GetLevelCount() const;

    void SetIsMovingUp(bool isMovingUp);

    void SetIsMovingDown(bool isMovingDown);

    void SetIsMovingRight(bool isMovingRight);

    void SetIsMovingLeft(bool isMovingLeft);

    bool IsCanMove() const;

    bool IsGameOver() const;

    void SetCanMove(bool canMove);

    double GetCurrentTimeCount() const;

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
    //number of cars per level T: kNumCarsRT
    int kNumCarsR1 = 6;
    int kNumCarsR2 = 2;
    int kNumCarsR3 = 5;
    int kNumCarsR4 = 4;
    int kNumCarsR5 = 3;
    float kDefaultRadius = 30;
    float kObjectiveRadius = 20;
    //wall positions for level
    float kRightWall = 2400;
    float kLeftWall = 0;
    float kTopWall = 150;
    float kBottomWall = 2000;
    //number of lives that the Player has
    int kLives = 3;
    size_t kNumCoins = 1;
    int kCoinValue = 50; //score gained per coin obtained
    float kCoinSpawnMargin = 200;

    //booleans determining current movement of Player
    bool isMovingUp_ = false;
    bool isMovingDown_ = false;
    bool isMovingRight_ = false;
    bool isMovingLeft_ = false;
    //members tracking time related info for level
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
    std::chrono::time_point<std::chrono::steady_clock> end_time_;
    double current_time_;
    bool can_move_ = false;
    bool game_over_ = false;
    int score_;
    unsigned level_count_;
    std::vector<Road> car_roads_; //stores all the roads in the level
    std::vector<Stream> gator_streams_; //stores all streams in the level
    std::vector<Coin> coins_; //stores all coins on level
    Player player_;
    
    void ExecuteWallCollision();
    
    void ExecuteLevelCompletion();
    
    void ExecuteCarCollision();
    
    void ExecuteGatorCollision();
    
    void DrawLevelObjective(const vec2& level_goal) const;
    
    double ComputeElapsedTime();
    
    void ComputeCurrentTime();

    void DecreaseLives();
    
    void PopulateRoads();
    
    void PopulateStreams();
    
    void CreateCoins();
    
    void UpdateRoadDirections();
    
    void UpdateStreamSettings();
    
    void MovePlayerInStream();
};

}
