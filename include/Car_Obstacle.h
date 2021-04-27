#pragma once

#include "cinder/gl/gl.h"

namespace frogger {

    using glm::vec2;

    class Car {
      public:
        Car(const vec2& spawnpoint, float speed);
        void DrawCar(const vec2& spawnpoint);
        void MoveCar(float difficulty_scalar, float speed);
      private:
        ci::Color kPossibleColors[5] = {"darkgray", "firebrick", "goldenrod", "darkblue", "azure"};
        float kVerticalWidth = 50;
        float kHorizontalWidth = 100;
        float kRightWall = 2400;
        float kLeftWall = 0;
        
        float move_speed_;
        vec2 top_left_edge_;
        vec2 bot_right_edge_;
        float direction_coeff_;
        
        float DetermineDirection(const vec2& spawnpoint) const;
        
    };
}