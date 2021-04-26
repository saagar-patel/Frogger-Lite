#pragma once

#include "cinder/gl/gl.h"

namespace frogger {

    using glm::vec2;

    class Car {
      public:
        Car(const vec2& spawnpoint, float speed);
        void DrawCar(const Car& car, const vec2& spawnpoint, const ci::Color& color);
        void MoveCar(const Car& car, float speed);
      private:
        std::string kPossibleColors[5] = {"darkgray", "firebrick", "goldenrod", "darkblue", "azure"};
        float kVerticalWidth = 50;
        float kHorizontalWidth = 100;
        float move_speed_;
        vec2 top_left_wall_;
        vec2 bot_right_wall_;
        
        
    };
}