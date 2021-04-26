#include "Car_Obstacle.h"

namespace frogger {
    
using glm::vec2;

Car::Car(const vec2& spawnpoint, float speed) {
  top_left_wall_ = vec2(spawnpoint.x - kHorizontalWidth/2, spawnpoint.y - kVerticalWidth/2);
  bot_right_wall_ = vec2(spawnpoint.x + kHorizontalWidth/2, spawnpoint.y + kVerticalWidth/2);
  move_speed_ = speed;
}

void Car::DrawCar(const Car &car, const vec2 &spawnpoint, const ci::Color &color) {
  //TODO: Figure out metrics for drawing this shit
}

void Car::MoveCar(const Car &car, float speed) {
  //Get Car animation to work somehow
}

}


