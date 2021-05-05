#include "level.h"
#include <chrono>
#include <cinder/Rand.h>
#include <Windows.h>

namespace frogger {

using glm::distance;
    
Level::Level() : player_(CreatePlayer(kPlayerSpawnPoint, kLives, kDefaultRadius)) {
  score_ = 0;
  level_count_ = 0;
  ExecuteLevelCompletion();
  player_.SetPosition(kPlayerSpawnPoint);
  start_time_ = std::chrono::steady_clock::now();
  current_time_ = 0;
  PopulateRoads();
  PopulateStreams();
  CreateCoins();
}

void Level::Display() const {
  DrawLevelObjective(kLevelObjective);
  player_.DrawPlayer();
  for (Road road : car_roads_) {
    for (Car &car : road.GetCars()) {
      car.DrawCar();
    }
  }
  for (const Stream& stream : gator_streams_) {
    for (Alligator gator : stream.gators_) {
      gator.DrawGator();
    }
  }
  for (Coin coin : coins_) {
    if(!coin.IsCollected()) {
      coin.DrawCoin();
    }
  }
  if (!can_move_ && !game_over_) {
    ci::gl::drawStringCentered("Press Spacebar to enable movement.",
                               vec2(1200, 450),
                               ci::Color("White"),
                               ci::Font("Consolas", 120));
  }
}

void Level::AdvanceOneFrame() {
  MovePlayer();
  MovePlayerInStream();
  ExecuteWallCollision();
  ExecuteLevelCompletion();
  ExecuteCarCollision();
  ExecuteGatorCollision();
  for (Coin &coin : coins_) {
    if (!coin.IsCollected()) {
      if (coin.CheckCoinCollision(player_)) {
        coin.SetIsCollected(true);
        score_ += coin.GetValue();
      }
    }
  }
  for (auto & car_road : car_roads_) {
    for (auto & car : car_road.GetCars()) {
      car.MoveCar(kBaseDifficultyScalar +
      ((static_cast<float>(score_)/kDifficultyDenominator) * static_cast<float>(level_count_)/2),
                  car_road.IsLeftToRightMovement());
      if (car_road.IsCarReachedEnd(car)) {
        car.PlaceCar(car_road.GetCurrentSpawnpoint());
      }
    }
  }
  for (auto & gator_stream : gator_streams_) {
    for (auto & gator : gator_stream.gators_) {
      gator.MoveGator(kBaseDifficultyScalar +
                                        ((static_cast<float>(score_)/kDifficultyDenominator)
                                        * static_cast<float>(level_count_)/2),
                                        gator_stream.IsLeftToRight());
      if (gator_stream.isGatorReachedEnd(gator)) {
        gator.PlaceGator(gator_stream.GetCurrentSpawnpoint());
      }
    }
  }
  ComputeCurrentTime();
}

Player Level::CreatePlayer(const vec2 &position, int lives, float radius) {
  Player frog = Player(position, lives, radius);
  return frog;
}

void Level::MovePlayer() {
  if (isMovingUp_) {
    player_.MoveUp();
  } else if (isMovingLeft_ || isMovingRight_) {
    if (isMovingRight_ && !isMovingLeft_) {
      player_.MoveRight();
    }
    if (isMovingLeft_ && !isMovingRight_) {
      player_.MoveLeft();
    }
  } else if (isMovingDown_) {
    player_.MoveDown();
  }
}

void Level::MovePlayerInStream() {
  for (auto & gator_stream : gator_streams_) {
    if (gator_stream.isPlayerInStream(player_)) {
      float difficulty_scalar = kBaseDiffScalarStream + ((static_cast<float>(score_)/kDifficultDenomStream)
                                * static_cast<float>(level_count_)/2);
      if (gator_stream.IsStreamLeftRight()) {
        player_.SetPosition(vec2(player_.GetPosition().x
                                 + (difficulty_scalar * gator_stream.GetPlayerMoveSpeed()), player_.GetPosition().y));
      } else {
        player_.SetPosition(vec2(player_.GetPosition().x
                                 - (difficulty_scalar * gator_stream.GetPlayerMoveSpeed()), player_.GetPosition().y));
      }
    }
  }
}

void Level::ExecuteWallCollision() {
  if (player_.GetPosition().x + player_.GetRadius() >= kRightWall ||
  player_.GetPosition().x - player_.GetRadius() <= kLeftWall ||
  player_.GetPosition().y + player_.GetRadius() >= kBottomWall ) {
    ResetPlayerPosition();
    DecreaseLives();
  } else if (player_.GetPosition().y - player_.GetRadius() <= kTopWall){
    player_.SetPosition(vec2(player_.GetPosition().x, kTopWall + player_.GetRadius()));
  }
}

void Level::ExecuteCarCollision() {
  for (auto & car_road : car_roads_) {
    for (auto & car : car_road.GetCars()) {
      if (player_.GetPosition().x - player_.GetRadius() <= car.GetBotRightEdge().x &&
          player_.GetPosition().x + player_.GetRadius() >= car.GetTopLeftEdge().x &&
          player_.GetPosition().y + player_.GetRadius() >= car.GetTopLeftEdge().y &&
          player_.GetPosition().y - player_.GetRadius() <= car.GetBotRightEdge().y) {
        ResetPlayerPosition();
        DecreaseLives();
      }
    }
  }
}

void Level::ExecuteGatorCollision() {
  for (auto & gator_stream : gator_streams_) {
    for (auto & gator : gator_stream.gators_) {
      if (player_.GetPosition().x - player_.GetRadius() <= gator.GetBotRightEdge().x &&
          player_.GetPosition().x + player_.GetRadius() >= gator.GetTopLeftEdge().x &&
          player_.GetPosition().y + player_.GetRadius() >= gator.GetTopLeftEdge().y &&
          player_.GetPosition().y - player_.GetRadius() <= gator.GetBotRightEdge().y) {
        ResetPlayerPosition();
        DecreaseLives();
      }
    }
  }
}

void Level::ResetPlayerPosition() {
  if (player_.GetLives() < 1) {
    game_over_ = true;
  }
  player_.SetPosition(kPlayerSpawnPoint);
  can_move_ = false;
  isMovingRight_ = false;
  isMovingLeft_ = false;
  isMovingUp_ = false;
  isMovingDown_ = false;
  current_time_ = 0.0;
}

void Level::DrawLevelObjective(const vec2& level_goal) const {
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedCircle(level_goal, kObjectiveRadius, 4.0f);
  ci::gl::color(ci::Color("yellow"));
  ci::gl::drawSolidCircle(level_goal, kObjectiveRadius);
}

void Level::DecreaseLives() {
  player_.SetLives(player_.GetLives() - 1);
}

void Level::ExecuteLevelCompletion() {
  ci::Rand::randomize();
  if (distance(player_.GetPosition(), kLevelObjective) < player_.GetRadius() + kObjectiveRadius) {
    player_.SetLives(3);
    ResetPlayerPosition();
    level_count_++;
    score_ += static_cast<int>(100 * (1/(0.1 * ComputeElapsedTime())));
    UpdateRoadDirections();
    UpdateStreamSettings();
    for (Coin &coin :coins_) {
      coin.SetIsCollected(false);
      coin.SetToRandomPosition();
    }
  }
}

double Level::ComputeElapsedTime() {
  end_time_ = std::chrono::steady_clock::now();
  double time_elapsed = std::chrono::duration<double>(end_time_ - start_time_).count();
  start_time_ = std::chrono::steady_clock::now();
  return time_elapsed;
}

void Level::ComputeCurrentTime() {
  current_time_ =  std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time_).count();
}

void Level::PopulateRoads() {
  car_roads_.emplace_back(Road(kR1Spawnpoints, kNumCarsR1, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
  car_roads_.emplace_back(Road(kR2Spawnpoints, kNumCarsR2, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
  car_roads_.emplace_back(Road(kR3Spawnpoints, kNumCarsR3, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
  car_roads_.emplace_back(Road(kR4Spawnpoints, kNumCarsR4, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
  car_roads_.emplace_back(Road(kR5Spawnpoints, kNumCarsR5, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
}

void Level::PopulateStreams() {
  gator_streams_.emplace_back(Stream(kS1Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(),
                                     kStream1Top, kStream1Bot,
                                     ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
  gator_streams_.emplace_back(Stream(kS2Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(),
                                     kStream2Top, kStream2Bot,
                                     ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
  gator_streams_.emplace_back(Stream(kS3Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(),
                                     kStream3Top, kStream3Bot,
                                     ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
  gator_streams_.emplace_back(Stream(kS4Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(),
                                     kStream4Top, kStream4Bot,
                                     ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
  gator_streams_.emplace_back(Stream(kS5Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(),
                                     kStream5Top, kStream5Bot, 
                                     ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
}

void Level::CreateCoins() {
  for (size_t i = 0; i < kNumCoins; ++i) {
    coins_.emplace_back(Coin(kRightWall, kBottomWall, kCoinSpawnMargin, kCoinValue));
  }
}

void Level::UpdateRoadDirections() {
  for (auto & car_road : car_roads_) {
    bool left_to_right_direction = ci::Rand::randBool();
    car_road.SetLeftToRightMovement(left_to_right_direction);
    if (left_to_right_direction) {
      car_road.SetCurrentSpawnpoint(car_road.GetSpawnpoints()[0]);
      car_road.SetDestructionPoint(car_road.GetSpawnpoints()[1]);
    } else {
      car_road.SetCurrentSpawnpoint(car_road.GetSpawnpoints()[1]);
      car_road.SetDestructionPoint(car_road.GetSpawnpoints()[0]);
    }
  }
}

void Level::UpdateStreamSettings() {
  for (auto & gator_stream : gator_streams_) {
    bool left_to_right_direction = ci::Rand::randBool();
    gator_stream.SetLeftToRight(left_to_right_direction);
    gator_stream.SetStreamLeftRight(!left_to_right_direction);
    float new_speed = ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed);
    gator_stream.SetPlayerMoveSpeed(new_speed);
    if (left_to_right_direction) {
      gator_stream.SetCurrentSpawnpoint(gator_stream.GetSpawnpoints()[0]);
      gator_stream.SetResetPoint(gator_stream.GetSpawnpoints()[1]);
    } else {
      gator_stream.SetCurrentSpawnpoint(gator_stream.GetSpawnpoints()[1]);
      gator_stream.SetResetPoint(gator_stream.GetSpawnpoints()[0]);
    }
  }
}

Player Level::GetPlayer() {
  return player_;
}

int Level::GetScore() const {
  return score_;
}

unsigned int Level::GetLevelCount() const {
  return level_count_;
}

void Level::SetIsMovingUp(bool isMovingUp) {
  isMovingUp_ = isMovingUp;
}

void Level::SetIsMovingDown(bool isMovingDown) {
  isMovingDown_ = isMovingDown;
}

void Level::SetIsMovingRight(bool isMovingRight) {
  isMovingRight_ = isMovingRight;
}

void Level::SetIsMovingLeft(bool isMovingLeft) {
  isMovingLeft_ = isMovingLeft;
}

bool Level::IsCanMove() const {
  return can_move_;
}

bool Level::IsGameOver() const {
  return game_over_;
}

void Level::SetCanMove(bool canMove) {
  can_move_ = canMove;
}

double Level::GetCurrentTimeCount() const {
  return current_time_;
}

}

