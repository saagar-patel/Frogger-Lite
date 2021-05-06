#include "road.h"

#include <utility>
#include <cinder/Rand.h>

namespace frogger {
    
using glm::vec2;  

Road::Road(std::vector<vec2> spawnpoints, int num_cars, float min_speed, float max_speed, bool left_to_right) {
    spawnpoints_ = std::move(spawnpoints);
    num_cars_ = num_cars;
    min_speed_ = min_speed;
    max_speed_ = max_speed;
    left_to_right_movement_ = left_to_right;
    road_width_ = spawnpoints_[1].x - spawnpoints_[0].x;
    CreateCarObstacles();
}

void Road::CreateCarObstacles() {
  float speed = ci::Rand::randFloat(min_speed_, max_speed_ + 1);
  if (left_to_right_movement_) {
    current_spawnpoint_ = spawnpoints_[0];
    destruction_point_ = spawnpoints_[1];
  } else {
    current_spawnpoint_ = spawnpoints_[1];
    destruction_point_ = spawnpoints_[0];
  }
  for (int i = 1; i < num_cars_ + 1; ++i) {
    if (left_to_right_movement_) {
      cars_.emplace_back(Car(vec2(current_spawnpoint_.x + ((road_width_/static_cast<float>(num_cars_)) 
      * static_cast<float>(i)), current_spawnpoint_.y),speed));
    } else {
      cars_.emplace_back(Car(vec2(current_spawnpoint_.x - ((road_width_/static_cast<float>(num_cars_)) 
      * static_cast<float>(i)), current_spawnpoint_.y),speed));
    }
  }
}

const vec2 &Road::GetCurrentSpawnpoint() const {
  return current_spawnpoint_;
}

bool Road::IsCarReachedEnd(const Car& car) const {
  if (left_to_right_movement_) {
    if (car.GetTopLeftEdge().x >= destruction_point_.x) {
      return true;
    }
  } else if (!left_to_right_movement_) {
    if (car.GetBotRightEdge().x <= destruction_point_.x) {
      return true;
    }
  }
  return false;
}

void Road::SetLeftToRightMovement(bool leftToRightMovement) {
  left_to_right_movement_ = leftToRightMovement;
}

bool Road::IsLeftToRightMovement() const {
  return left_to_right_movement_;
}

void Road::SetCurrentSpawnpoint(const vec2 &currentSpawnpoint) {
  current_spawnpoint_ = currentSpawnpoint;
}

void Road::SetDestructionPoint(const vec2 &destructionPoint) {
  destruction_point_ = destructionPoint;
}

const std::vector<vec2> &Road::GetSpawnpoints() const {
  return spawnpoints_;
}

std::vector<Car> &Road::GetCars() {
  return cars_;
}

}