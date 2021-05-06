#pragma once

#include "cinder/gl/gl.h"

namespace frogger {
    using glm::vec2;
    
    class Alligator {
      public:
        /**
         * Constructor for Alligator object
         * @param spawnpoint the place at which to initially spawn the alligator
         * @param speed the initial randomized speed for the alligator
         */
        Alligator(const vec2& spawnpoint, float speed);

        /**
         * Draws the alligator using cinder::gl::drawSolidRect();
         */
        void DrawGator() const;

        /**
         * Moves the alligator in the x-direction in accordance to the speed with direction and difficulty factored in
         * @param difficulty_scalar the amount by which to scale the speed
         * @param left_to_right represents the direction to move the gator,
         * if true then left -> right, else right -> left
         */
        void MoveGator(float difficulty_scalar, bool left_to_right);

        /**
         * Getter for the top left corner of the gator
         * @return a vec2 with two value representing the point in pixels of the top left corner of the alligator
         */
        const vec2 &GetTopLeftEdge() const;

        /**
         * Getter for the bot right corner of the gator
         * @return a vec2 with two values representing the point in pixels of the bot right corner of the gator
         */
        const vec2 &GetBotRightEdge() const;

        /**
         * Places the gator at a specified point, modifies top_left_edge, and bot_right_edge
         * @param point the point at which to place the center of the alligator
         */
        void PlaceGator(const vec2& point);
        
      private:
        float kVerticalWidth = 100;
        float kHorizontalWidth = 240;

        ci::Color kColor = "darkgreen";
        float move_speed_;
        //these two vec2 represents the top_left corner and bottom_right corner of the alligator rect
        vec2 top_left_edge_;
        vec2 bot_right_edge_;
    };
}