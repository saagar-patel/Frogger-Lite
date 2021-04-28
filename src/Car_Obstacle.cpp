#include "Car_Obstacle.h"
#include "cinder/Rand.h"

namespace frogger {
    
using glm::vec2;

Car::Car(const vec2& spawnpoint, float speed) {
  top_left_edge_ = vec2(spawnpoint.x - kHorizontalWidth / 2, spawnpoint.y - kVerticalWidth / 2);
  bot_right_edge_ = vec2(spawnpoint.x + kHorizontalWidth / 2, spawnpoint.y + kVerticalWidth / 2);
  move_speed_ = speed;
  direction_coeff_ = DetermineDirection(spawnpoint);
}

void Car::DrawCar(const vec2 &spawnpoint) {
  ci::gl::color(ci::Color(kPossibleColors[ci::Rand::randUint(4)]));
  ci::gl::drawSolidRect(ci::Rectf(top_left_edge_, bot_right_edge_));
}

void Car::MoveCar(float difficulty_scalar) {
  top_left_edge_.x += (direction_coeff_ * difficulty_scalar) * move_speed_;
  bot_right_edge_.x += (direction_coeff_ * difficulty_scalar) * move_speed_;
}

float Car::DetermineDirection(const vec2& spawnpoint) const {
  if (kRightWall - spawnpoint.x >= kLeftWall + spawnpoint.x) { // spawn is on right side
    return -1.0f;
  } else { //spawn is on left side
    return 1.0f;
  }
}

const vec2 &Car::GetTopLeftEdge() const {
  return top_left_edge_;
}

const vec2 &Car::GetBotRightEdge() const {
  return bot_right_edge_;
}

float Car::GetDirectionCoeff() const {
  return direction_coeff_;
}

}


