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
    /**
     * Constructor for the level object, takes no params
     */
    explicit Level();
    
    /**
     * Display method used by frogger_app
     * Handles drawing player, cars, alligators, coins, level objective, borders
     */
    void Display() const;
    
    /**
     * AdvanceOneFrame method used by frogger_app handles all visual updates and serves as makeshift game loop
     * Handles car movement, player movement, alligator movement, collision, level updates
     */
    void AdvanceOneFrame();
    
    /**
     * Creates the player object that exists in the level
     * @param position the position to start the player
     * @param lives num lives for player
     * @param radius the radius of the player piece
     * @return a player object
     */
    static Player CreatePlayer(const vec2& position, int lives, float radius);
    
    /**
     * Getter for Player object in Level
     * @return an object of type Player representing the current playable object
     */
    Player GetPlayer();
    
    /**
     * Handles WASD movement of the player object
     */
    void MovePlayer();

    /**
     * Resets the position of the player to the spawnpoint
     */
    void ResetPlayerPosition();

    /**
     * Getter for the current score of the game
     * @return an int representing the score
     */
    int GetScore() const;

    /**
     * Getter for the current level
     * @return unsigned representing the level
     */
    unsigned int GetLevelCount() const;

    /**
     * Sets the boolean representing if the player is in the state of moving up or not
     * @param isMovingUp true = moving up, false = not moving up
     */
    void SetIsMovingUp(bool isMovingUp);

    /**
     * Sets the boolean representing if the player is in the state of moving down or not
     * @param isMovingDown true = moving down, false = not moving down
     */
    void SetIsMovingDown(bool isMovingDown);

    /**
     * Sets the boolean representing if the player is in the state of moving right not
     * @param isMovingDown true = moving right, false = not moving right
     */
    void SetIsMovingRight(bool isMovingRight);

    /**
     * Sets the boolean representing if the player is in the state of moving down or not
     * @param isMovingDown true = moving left, false = not moving left
     */
    void SetIsMovingLeft(bool isMovingLeft);

    /**
     * Getter for the boolean representing the state of if the player can move at all or not
     * @return boolean, true = can move, false = cannot move
     */
    bool IsCanMove() const;

    /**
     * Getter for the boolean representing the state of if the game is over or not
     * @return boolean, true == game over, false = game not over
     */
    bool IsGameOver() const;

    /**
     * Setter for the boolean representing if the player can move
     * @param canMove true = makes player movable, false = makes the player immobile
     */
    void SetCanMove(bool canMove);

    /**
     * Returns the current time elapsed on the level
     * @return a double representing the time since the level started
     */
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
    
    /**
     * Checks if the player object collides with the wall
     * Changes state of the level accordingly to collision 
     */
    void ExecuteWallCollision();
    
    /**
     * Checks if the player collides with the level objective
     * Changes state of the level and player accordingly to collision
     */
    void ExecuteLevelCompletion();
    
    /**
     * Checks if the players collides with a car
     * Changes the state of the level and player as well depending on collision
     */
    void ExecuteCarCollision();
    
    /**
     * Checks if the players collides with a Alligator
     * Changes the state of the level and player as well depending on collision
     */
    void ExecuteGatorCollision();
    
    /**
     * Draws level objective using cinder::gl::drawSolidCircle
     * @param level_goal the position at which to place the level objective
     */
    void DrawLevelObjective(const vec2& level_goal) const;
    
    /**
     * Compute Elapsed Time for each level
     * @return a double representing time spent on the level, used in score calculation
     */
    double ComputeElapsedTime();
    
    /**
     * Computes the current time, used to modify current_time_
     */
    void ComputeCurrentTime();

    /**
     * Decreases the life count by 1
     */
    void DecreaseLives();
    
    /**
     * Places cars on road according to level specifications and road specifications
     */
    void PopulateRoads();
    
    /**
     * Places alligators in stream according to level and stream specifications
     */
    void PopulateStreams();
    
    /**
     * Creates coins and adds them to the member list containing all coins belonging to the level
     */
    void CreateCoins();
    
    /**
     * Updates the direction that cars go on each road randomly
     */
    void UpdateRoadDirections();
    
    /**
     * Updates the direction that alligators go as well as the direction of the current in each stream randomly
     */
    void UpdateStreamSettings();
    
    /**
     * Moves the player object according to the stream current of the stream it is in
     */
    void MovePlayerInStream();
};

}
