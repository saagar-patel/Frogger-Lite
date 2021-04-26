#include "level.h"

namespace frogger {
    
Level::Level(int lives) : player_(CreatePlayer(kSpawnPoint, lives, kDefaultRadius)) {
  player_;
  player_.SetPosition(kSpawnPoint);
}

void Level::Display() const {
  DrawPlayer();
}

void Level::AdvanceOneFrame() {
  MovePlayer();
  ExecuteWallCollision();
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

void Level::DrawPlayer() const{
  ci::gl::drawSolidCircle(player_.GetPosition(), player_.GetRadius());
}

}

