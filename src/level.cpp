#include "level.h"
#include <chrono>

namespace frogger {

using glm::distance;
    
Level::Level(int lives) : player_(CreatePlayer(kSpawnPoint, lives, kDefaultRadius)) {
  score_ = 0;
  level_count_ = 0;
  ExecuteLevelCompletion();
  player_.SetPosition(kSpawnPoint);
  start_time_ = std::chrono::steady_clock::now();
}

void Level::Display() const {
  DrawLevelObjective(kLevelObjective);
  player_.DrawPlayer();
}

void Level::AdvanceOneFrame() {
  MovePlayer();
  ExecuteWallCollision();
  ExecuteLevelCompletion();
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
  player_.GetPosition().x - player_.GetRadius() <= kLeftWall) {
    ResetPlayerPosition();
  } else if (player_.GetPosition().y + player_.GetRadius() >= kBottomWall ||
             player_.GetPosition().y - player_.GetRadius() <= kTopWall){
    ResetPlayerPosition();
  }
}

void Level::ResetPlayerPosition() {
    player_.SetPosition(kSpawnPoint);
    player_.SetLives(player_.GetLives() - 1);
}

void Level::DrawLevelObjective(const vec2& level_goal) const {
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedCircle(level_goal, kObjectiveRadius, 4.0f);
  ci::gl::color(ci::Color("yellow"));
  ci::gl::drawSolidCircle(level_goal, kObjectiveRadius);
}

void Level::ExecuteLevelCompletion() {
  if (distance(player_.GetPosition(), kLevelObjective) < player_.GetRadius() + kObjectiveRadius) {
    ResetPlayerPosition();
    level_count_++;
    score_ += static_cast<int>(100 * (1/(0.1 * CountElapsedTime())));
  }
}

  double Level::CountElapsedTime() {
    end_time_ = std::chrono::steady_clock::now();
    double time_elapsed = std::chrono::duration<double>(end_time_ - start_time_).count();
    start_time_ = std::chrono::steady_clock::now();
    return time_elapsed;
  }

  void Level::DecreaseLives() {
    
  }

}

