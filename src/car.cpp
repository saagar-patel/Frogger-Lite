#include "car.h"
#include "cinder/Rand.h"

namespace frogger {
    
using glm::vec2;

Car::Car(const vec2& spawnpoint, float speed) {
  top_left_edge_ = vec2(spawnpoint.x - kHorizontalWidth / 2, spawnpoint.y - kVerticalWidth / 2);
  bot_right_edge_ = vec2(spawnpoint.x + kHorizontalWidth / 2, spawnpoint.y + kVerticalWidth / 2);
  move_speed_ = speed;
  color_ = ci::Color(kPossibleColors[ci::Rand::randUint(8)]);
}

void Car::DrawCar() {
  ci::gl::color(color_);
  ci::gl::drawSolidRect(ci::Rectf(top_left_edge_, bot_right_edge_));
}

void Car::MoveCar(float difficulty_scalar, bool direction) {
  if (direction) {
    top_left_edge_.x += difficulty_scalar * move_speed_;
    bot_right_edge_.x += difficulty_scalar * move_speed_;
  } else {
    top_left_edge_.x += (-1.0f * difficulty_scalar * move_speed_);
    bot_right_edge_.x += (-1.0f * difficulty_scalar * move_speed_);
  }
}

const vec2 &Car::GetTopLeftEdge() const {
  return top_left_edge_;
}

const vec2 &Car::GetBotRightEdge() const {
  return bot_right_edge_;
}

void Car::PlaceCar(const vec2& point) {
  top_left_edge_ = vec2(point.x - kHorizontalWidth / 2, point.y - kVerticalWidth / 2);
  bot_right_edge_ = vec2(point.x + kHorizontalWidth / 2, point.y + kVerticalWidth / 2);
}

}


