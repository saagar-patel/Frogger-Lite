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
}


void Level::Display() const {
  DrawLevelObjective(kLevelObjective);
  player_.DrawPlayer();
  for (const Road& road : car_roads_) {
    for (Car car : road.cars_) {
      car.DrawCar();
    }
  }
  if (!can_move && !game_over) {
    ci::gl::drawStringCentered("Press Spacebar to enable movement.",
                               vec2(1200, 700),
                               ci::Color("Black"),
                               ci::Font("Consolas", 120));
  }
  
  
  
  ci::gl::drawStringCentered(std::to_string(ci::Rand::randInt(0, 7)),
                             vec2(900, 400),
                             ci::Color("purple"),
                             ci::Font("Consolas", 100));
  ci::gl::drawStringCentered(std::to_string(car_roads_[2].isLeftToRightMovement()),
                             vec2(900, 500),
                             ci::Color("purple"),
                             ci::Font("Consolas", 100));
  ci::gl::drawStringCentered(std::to_string(can_move),
                             vec2(900, 600),
                             ci::Color("white"),
                             ci::Font("Consolas", 100));
}

void Level::AdvanceOneFrame() {
  MovePlayer();
  ExecuteWallCollision();
  ExecuteLevelCompletion();
  ExecuteCarCollision();
  for (size_t i = 0; i < car_roads_.size(); ++i) {
    for (size_t j = 0; j < car_roads_[i].cars_.size(); ++j) {
      car_roads_[i].cars_[j].MoveCar(kBaseDifficultyScalar +
      ((static_cast<float>(score_ * level_count_))/kDifficultyDenominator),
      car_roads_[i].isLeftToRightMovement());
      if (car_roads_[i].isCarReachedEnd(car_roads_[i].cars_[j])) {
        car_roads_[i].cars_[j].PlaceCar(car_roads_[i].GetCurrentSpawnpoint());
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
  if (player_.GetLives() <= 1) {
    game_over = true;
    can_move = false;
    isMovingRight = false;
    isMovingLeft = false;
    isMovingUp = false;
    isMovingDown = false;
  } else {
    can_move = false;
    player_.SetPosition(kPlayerSpawnPoint);
    isMovingRight = false;
    isMovingLeft = false;
    isMovingUp = false;
    isMovingDown = false;
    current_time_ = 0.0;
  }
  
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
    ResetPlayerPosition();
    player_.SetLives(3);
    level_count_++;
    score_ += static_cast<int>(100 * (1/(0.1 * CountElapsedTime())));
    UpdateRoadDirections();
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


}

