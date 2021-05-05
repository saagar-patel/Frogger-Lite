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
  for (const Road& road : car_roads_) {
    for (Car car : road.cars_) {
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
  if (!can_move && !game_over) {

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
  for (size_t i = 0; i < car_roads_.size(); ++i) {
    for (size_t j = 0; j < car_roads_[i].cars_.size(); ++j) {
      car_roads_[i].cars_[j].MoveCar(kBaseDifficultyScalar + ((static_cast<float>(score_)/kDifficultyDenominator) * static_cast<float>(level_count_)),
      car_roads_[i].isLeftToRightMovement());
      if (car_roads_[i].isCarReachedEnd(car_roads_[i].cars_[j])) {
        car_roads_[i].cars_[j].PlaceCar(car_roads_[i].GetCurrentSpawnpoint());
      }
    }
  }
  
  for (size_t i = 0; i < gator_streams_.size(); ++i) {
    for (size_t j = 0; j < gator_streams_[i].gators_.size(); ++j) {
      gator_streams_[i].gators_[j].MoveGator(kBaseDifficultyScalar + 
                  ((static_cast<float>(score_)/kDifficultyDenominator) * static_cast<float>(level_count_)),
                  gator_streams_[i].IsLeftToRight());
      if (gator_streams_[i].isGatorReachedEnd(gator_streams_[i].gators_[j])) {
        gator_streams_[i].gators_[j].PlaceGator(gator_streams_[i].GetCurrentSpawnpoint());
      }
    }
  }
  CountCurrentTime();
}

Player Level::CreatePlayer(const vec2 &position, int lives, float radius) {
  Player frog = Player(position, lives, radius);
  return frog;
}

Player Level::GetPlayer() {
  return player_;
}

void Level::MovePlayer() {
  if (isMovingUp) {
    player_.MoveUp();
  } else if (isMovingLeft || isMovingRight) {
    if (isMovingRight && !isMovingLeft) {
      player_.MoveRight();
    }
    if (isMovingLeft && !isMovingRight) {
      player_.MoveLeft();
    }
  } else if (isMovingDown) {
    player_.MoveDown();
  }
  
}
  
void Level::ExecuteWallCollision() {
  if (player_.GetPosition().x + player_.GetRadius() >= kRightWall ||
  player_.GetPosition().x - player_.GetRadius() <= kLeftWall || player_.GetPosition().y + player_.GetRadius() >= kBottomWall ) {
    ResetPlayerPosition();
    DecreaseLives();
  } else if (player_.GetPosition().y - player_.GetRadius() <= kTopWall){
    player_.SetPosition(vec2(player_.GetPosition().x, kTopWall + player_.GetRadius()));
  }
}

void Level::ResetPlayerPosition() {
  if (player_.GetLives() < 1) {
    game_over = true;
  }
  player_.SetPosition(kPlayerSpawnPoint);
  can_move = false;
  isMovingRight = false;
  isMovingLeft = false;
  isMovingUp = false;
  isMovingDown = false;
  current_time_ = 0.0;
}

void Level::DrawLevelObjective(const vec2& level_goal) const {
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedCircle(level_goal, kObjectiveRadius, 4.0f);
  ci::gl::color(ci::Color("yellow"));
  ci::gl::drawSolidCircle(level_goal, kObjectiveRadius);
}

void Level::ExecuteLevelCompletion() {
  ci::Rand::randomize();
  if (distance(player_.GetPosition(), kLevelObjective) < player_.GetRadius() + kObjectiveRadius) {
    player_.SetLives(3);
    ResetPlayerPosition();
    level_count_++;
    score_ += static_cast<int>(100 * (1/(0.1 * CountElapsedTime())));
    UpdateRoadDirections();
    UpdateStreamSettings();
    for (Coin &coin :coins_) {
      coin.SetIsCollected(false);
      coin.SetToRandomPosition();
    }
  }
}

  double Level::CountElapsedTime() {
    end_time_ = std::chrono::steady_clock::now();
    double time_elapsed = std::chrono::duration<double>(end_time_ - start_time_).count();
    start_time_ = std::chrono::steady_clock::now();
    return time_elapsed;
  }

  void Level::DecreaseLives() {
    player_.SetLives(player_.GetLives() - 1);
  }
  
  void Level::PopulateRoads() {
    car_roads_.emplace_back(Road(kR1Spawnpoints, kNumCarsR1, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
    car_roads_.emplace_back(Road(kR2Spawnpoints, kNumCarsR2, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
    car_roads_.emplace_back(Road(kR3Spawnpoints, kNumCarsR3, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
    car_roads_.emplace_back(Road(kR4Spawnpoints, kNumCarsR4, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
    car_roads_.emplace_back(Road(kR5Spawnpoints, kNumCarsR5, kMinSpeed, kMaxSpeed, ci::Rand::randBool()));
  }

  void Level::PopulateStreams() {
    gator_streams_.emplace_back(Stream(kS1Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(), kStream1Top,
                                       kStream1Bot,ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
    gator_streams_.emplace_back(Stream(kS2Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(), kStream2Top,
                                       kStream2Bot, ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
    gator_streams_.emplace_back(Stream(kS3Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(), kStream3Top,
                                       kStream3Bot, ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
    gator_streams_.emplace_back(Stream(kS4Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(), kStream4Top,
                                       kStream4Bot, ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
    gator_streams_.emplace_back(Stream(kS5Spawnpoints, kMinSpeed, kMaxSpeed, ci::Rand::randBool(), kStream5Top,
                                       kStream5Bot, ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed)));
  }
  
  void Level::UpdateRoadDirections() {
    for (size_t i = 0; i < car_roads_.size(); ++i) {
      bool left_to_right_direction = ci::Rand::randBool();
      car_roads_[i].SetLeftToRightMovement(left_to_right_direction);
      if (left_to_right_direction) {
        car_roads_[i].SetCurrentSpawnpoint(car_roads_[i].GetSpawnpoints()[0]);
        car_roads_[i].SetDestructionPoint(car_roads_[i].GetSpawnpoints()[1]);
      } else {
        car_roads_[i].SetCurrentSpawnpoint(car_roads_[i].GetSpawnpoints()[1]);
        car_roads_[i].SetDestructionPoint(car_roads_[i].GetSpawnpoints()[0]);
      }
    }
  }

  void Level::ExecuteCarCollision() {
    for (size_t i = 0; i < car_roads_.size(); ++i) {
      for (size_t j = 0; j < car_roads_[i].cars_.size(); ++j) {
        if (player_.GetPosition().x - player_.GetRadius() <= car_roads_[i].cars_[j].GetBotRightEdge().x &&
            player_.GetPosition().x + player_.GetRadius() >= car_roads_[i].cars_[j].GetTopLeftEdge().x && 
            player_.GetPosition().y + player_.GetRadius() >= car_roads_[i].cars_[j].GetTopLeftEdge().y &&
          player_.GetPosition().y - player_.GetRadius() <= car_roads_[i].cars_[j].GetBotRightEdge().y) {
          ResetPlayerPosition();
          DecreaseLives();
        } 
      }
    }
  }

  void Level::CountCurrentTime() {
    current_time_ =  std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time_).count();
  }

  void Level::MovePlayerInStream() {
    for (size_t i = 0; i < gator_streams_.size(); ++i) {
      if (gator_streams_[i].isPlayerInStream(player_)) {
        float difficulty_scalar = kBaseDiffScalarStream + ((static_cast<float>(score_)/kDifficultDenomStream) * static_cast<float>(level_count_));
        if (gator_streams_[i].IsStreamLeftRight()) {
          player_.SetPosition(vec2(player_.GetPosition().x + (difficulty_scalar * gator_streams_[i].GetPlayerMoveSpeed()), player_.GetPosition().y));
        } else {
          player_.SetPosition(vec2(player_.GetPosition().x - (difficulty_scalar * gator_streams_[i].GetPlayerMoveSpeed()), player_.GetPosition().y));
        }
      }
    } 
  }

  void Level::UpdateStreamSettings() {
    for (size_t i = 0; i < gator_streams_.size(); ++i) {
      bool left_to_right_direction = ci::Rand::randBool();
      gator_streams_[i].SetLeftToRight(left_to_right_direction);
      gator_streams_[i].SetStreamLeftRight(!left_to_right_direction);
      float new_speed = ci::Rand::randFloat(kMinStreamSpeed, kMaxStreamSpeed);
      gator_streams_[i].SetPlayerMoveSpeed(new_speed);
      if (left_to_right_direction) {
        gator_streams_[i].SetCurrentSpawnpoint(gator_streams_[i].GetSpawnpoints()[0]);
        gator_streams_[i].SetResetPoint(gator_streams_[i].GetSpawnpoints()[1]);
      } else {
        gator_streams_[i].SetCurrentSpawnpoint(gator_streams_[i].GetSpawnpoints()[1]);
        gator_streams_[i].SetResetPoint(gator_streams_[i].GetSpawnpoints()[0]);
      }
    }
  }

  void Level::ExecuteGatorCollision() {
    for (size_t i = 0; i < gator_streams_.size(); ++i) {
      for (size_t j = 0; j < gator_streams_[i].gators_.size(); ++j) {
        if (player_.GetPosition().x - player_.GetRadius() <= gator_streams_[i].gators_[j].GetBotRightEdge().x &&
            player_.GetPosition().x + player_.GetRadius() >= gator_streams_[i].gators_[j].GetTopLeftEdge().x &&
            player_.GetPosition().y + player_.GetRadius() >= gator_streams_[i].gators_[j].GetTopLeftEdge().y &&
            player_.GetPosition().y - player_.GetRadius() <= gator_streams_[i].gators_[j].GetBotRightEdge().y) {
          ResetPlayerPosition();
          DecreaseLives();
        }
      }
    }
  }

  void Level::CreateCoins() {
    for (size_t i = 0; i < kNumCoins; ++i) {
      coins_.emplace_back(Coin(kRightWall, kBottomWall, kTopWall + 50, kCoinValue));
    }
  }
}

