#pragma once

#include "cinder/gl/gl.h"

namespace frogger {
    using glm::vec2;
    
    class Alligator {
      public:
        Alligator(const vec2& spawnpoint, float speed);

        void DrawGator();

        void MoveGator(float difficulty_scalar, bool direction);

        const vec2 &GetTopLeftEdge() const;

        const vec2 &GetBotRightEdge() const;

        void PlaceGator(const vec2& point);
        
      private:
        float kVerticalWidth = 100;
        float kHorizontalWidth = 240;

        ci::Color kColor = "darkgreen";
        float move_speed_;
        vec2 top_left_edge_;
        vec2 bot_right_edge_;
    };
}