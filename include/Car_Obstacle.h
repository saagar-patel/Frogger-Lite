#pragma once

#include "cinder/gl/gl.h"

namespace frogger {

    using glm::vec2;

    class Car {
      public:
        
        Car(const vec2& spawnpoint, float speed);
        
        void DrawCar();
        
        void MoveCar(float difficulty_scalar, bool direction);

        const vec2 &GetTopLeftEdge() const;

        const vec2 &GetBotRightEdge() const;
        
        void PlaceCar(const vec2& point);


    private:
        std::vector<ci::Color> kPossibleColors{"aqua", "orangered", "darkviolet", "khaki", "darkgray", "steelblue",
                                         "peachpuff", "lightgreen"};
        float kVerticalWidth = 80;
        float kHorizontalWidth = 125;
        
        ci::Color color_;
        float move_speed_;
        vec2 top_left_edge_;
        vec2 bot_right_edge_;
        
    };
}