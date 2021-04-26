#include "Player.h"
namespace frogger {
    
using glm::dot;
using glm::length;

Player::Player(const vec2& position, const int& lives, float radius) {
  position_ = position;
  radius_ = radius;
  lives_ = lives;
}

void Player::MoveUp() {
  position_.y = position_.y - kMoveDistance;
}

void Player::MoveRight() {
  position_.x = position_.x + kMoveDistance;
}

void Player::MoveLeft() {
  position_.x = position_.x - kMoveDistance;
}

void Player::MoveDown() {
  position_.y = position_.y + kMoveDistance;
}

void Player::DrawPlayer() const {
  ci::gl::drawSolidCircle(position_, radius_);
}

const vec2 &Player::GetPosition() const {
  return position_;
}

void Player::SetPosition(const vec2& new_position) {
  position_ = new_position;
}

float Player::GetRadius() const {
  return radius_;
}

int Player::GetLives() const {
  return lives_;
}

void Player::SetLives(int lives) {
  lives_ = lives;
}

}