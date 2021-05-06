#pragma once

#include "cinder/gl/gl.h"

namespace frogger {

  using glm::vec2;

  class Car {
    public:
      /**
       * Constructor for Car object
       * @param spawnpoint the point at which to initially spawn the Car
       * @param speed the initial randomized speed for the Car
       */
      Car(const vec2& spawnpoint, float speed);
      
      /**
       * Draws the car using cinder::gl::drawSolidRect();
       */
      void DrawCar() const;
      
      /**
       * Moves the car in the x-direction in accordance to the speed, direction, and difficulty scalar
       * @param difficulty_scalar the amount by which to scale the speed
       * @param left_to_right represents direction to move car, true = left -> right, false = right -> left
       */
      void MoveCar(float difficulty_scalar, bool left_to_right);

      /**
       * Getter fir the top left corner of the gator
       * @return a vec2 with values representing the point in x and y pixels of the top left corner of the Car
       */
      const vec2 &GetTopLeftEdge() const;

      /**
       * Getter for the bottom right corner of the Car
       * @return a vec2 with values representing the point in x and y pixels of the bottom right corner of the Car
       */
      const vec2 &GetBotRightEdge() const;
      
      /**
       * Places the Car at a specified point, modifies te top_left_edge and bot_right_edge relative to point
       * @param point where to place the center of the Car
       */
      void PlaceCar(const vec2& point);
      
  private:
      std::vector<ci::Color> kPossibleColors{"aqua", "orange", "darkviolet", "deepskyblue",
                                             "darkgray", "steelblue", "red", "lightgreen"};
      float kVerticalWidth = 80;
      float kHorizontalWidth = 125;
      
      ci::Color color_;
      float move_speed_;
      //these two vec2 represents the top_left corner and bottom_right corner of the Car rect
      vec2 top_left_edge_;
      vec2 bot_right_edge_;
  };
}