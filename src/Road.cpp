#include "Road.h"

#include <utility>
#include <cinder/Rand.h>

namespace frogger {
  using glm::vec2;

    Road::Road(std::vector<vec2> spawnpoints, int num_cars, float min_speed, float max_speed) {
        spawnpoints_ = std::move(spawnpoints);
        num_cars_ = num_cars;
        min_speed_ = min_speed;
        max_speed_ = max_speed;
        CreateCarObstacles();
        DetermineDirection();
    }

    const std::vector<vec2> &Road::GetSpawnpoints() const {
      return spawnpoints_;
    }

    void Road::SetSpawnpoints(const std::vector<vec2> &spawnpoints) {
      spawnpoints_ = spawnpoints;
    }

    const std::vector<Car> &Road::GetCars() const {
      return cars_;
    }

    void Road::SetCars(const std::vector<Car> &cars) {
      cars_ = cars;
    }

    int Road::GetNumCars() const {
      return num_cars_;
    }

    void Road::SetNumCars(int numCars) {
      num_cars_ = numCars;
    }

    float Road::GetMinSpeed() const {
      return min_speed_;
    }

    void Road::SetMinSpeed(float minSpeed) {
      min_speed_ = minSpeed;
    }

    float Road::GetMaxSpeed() const {
      return max_speed_;
    }

    void Road::SetMaxSpeed(float maxSpeed) {
      max_speed_ = maxSpeed;
    }

    void Road::CreateCarObstacles() {
//      auto speed = static_cast<float>(ci::Rand::randInt(min_speed_, max_speed_ + 1)); //causes conversion error, figure this out
      int spawn_index = ci::Rand::randInt(0, spawnpoints_.size());
      current_spawnpoint_ = spawnpoints_[spawn_index];
      if (spawn_index == 0) {
        destruction_point_ = spawnpoints_[1];
      } else {
        destruction_point_ = spawnpoints_[0];
      }
      std::vector<Car> temp_cars;
      for (int i = 0; i < num_cars_; ++i) {
        cars_.emplace_back(Car(current_spawnpoint_, 3)); //none of the cars move, can be many locations
      }
    }

    const vec2 &Road::GetCurrentSpawnpoint() const {
      return current_spawnpoint_;
    }

    void Road::SetCurrentSpawnpoint(const vec2 &currentSpawnpoint) {
      current_spawnpoint_ = currentSpawnpoint;
    }

    void Road::DetermineDirection() {
      if (cars_[0].GetDirectionCoeff() == -1) {
        left_to_right_movement_ = false;
      } else {
        left_to_right_movement_ = true;
      }
    }

    void Road::MoveCarsOnRoad(int score, int level, float road_width) {
      float difficulty = 1 + ((static_cast<float>(level + score))/kDifficultDenom);
      cars_[0].MoveCar(difficulty);
      size_t car_counter = 1;
      
      
      //determine when to release the next car using numCars
      //when a car reaches the end, pop front, emplace back the car
      
      
      //TODO: Implement this to move cars
      //TODO: Figure out how to use the destruction point
      //TODO: Figure out how to determine when you release the next car (use num_cars, width of road, collision
      //TODO: with that roadmarker to release the next car
    }

    bool Road::EvaluateCarRelease(Car car, float road_width) {
      if (left_to_right_movement_) {
        if (car.GetBotRightEdge().x >= road_width/num_cars_) {
          return true;
        }
      } else {
        if (car.GetTopLeftEdge().x <= (num_cars_ - 1) * (road_width/num_cars_)) {
          return true;
        }
      }
      return false;
    }
}