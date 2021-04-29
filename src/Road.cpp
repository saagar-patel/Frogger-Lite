#include "Road.h"

#include <utility>
#include <cinder/Rand.h>

namespace frogger {
  using glm::vec2;

    Road::Road(std::vector<vec2> spawnpoints, int num_cars, float min_speed, float max_speed, bool direction) {
        spawnpoints_ = std::move(spawnpoints);
        num_cars_ = num_cars;
        min_speed_ = min_speed;
        max_speed_ = max_speed;
        left_to_right_movement_ = direction;
        road_width_ = spawnpoints_[1].x - spawnpoints_[0].x;
        CreateCarObstacles();
    }
    
    void Road::CreateCarObstacles() {
      float speed = ci::Rand::randFloat(min_speed_, max_speed_ + 1);
      std::vector<Car> temp_cars;
      temp_cars.reserve(num_cars_);
      std::vector<vec2> new_spawnpoints;
      if (left_to_right_movement_) {
        current_spawnpoint_ = spawnpoints_[0];
        destruction_point_ = spawnpoints_[1];
      } else {
        current_spawnpoint_ = spawnpoints_[1];
        destruction_point_ = spawnpoints_[0];
      }
      for (int i = 1; i < num_cars_ + 1; ++i) {
        vec2 sp_point = vec2(0,0);
        if (left_to_right_movement_) {
          sp_point = vec2(current_spawnpoint_.x + ((road_width_/static_cast<float>(num_cars_)) * static_cast<float>(i)), current_spawnpoint_.y);
        } else {
          sp_point = vec2(current_spawnpoint_.x - ((road_width_/static_cast<float>(num_cars_)) * static_cast<float>(i)), current_spawnpoint_.y);
        }
        new_spawnpoints.emplace_back(sp_point);
      }
      
      for (int i = 0; i < num_cars_; ++i) {
        temp_cars.emplace_back(Car(new_spawnpoints[i], speed));
      }
      cars_ = temp_cars;
    }

    const vec2 &Road::GetCurrentSpawnpoint() const {
      return current_spawnpoint_;
    }

    bool Road::isCarReachedEnd(const Car& car) const {
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

    const vec2 &Road::GetDestructionPoint() const {
      return destruction_point_;
    }

    void Road::SetLeftToRightMovement(bool leftToRightMovement) {
      left_to_right_movement_ = leftToRightMovement;
    }

    bool Road::isLeftToRightMovement() const {
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

}