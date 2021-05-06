#pragma once

#include "cinder/gl/gl.h"
#include "player.h"

namespace frogger {
  using glm::vec2;

  class Coin {
    public:
      /**
       * Constructor or the Coin object
       * @param max_x_size the max x location for the coin to be spawned
       * @param max_y_size the max y location for the coin to be spawned
       * @param margin how far from the edge the coin should be spawned
       * @param value score contribution when collected
       */
      Coin(float max_x_size, float max_y_size, float margin, int value);
      
      /**
       * Sets coin to a random position depending on member variables
       */
      void SetToRandomPosition();

      /**
       * Boolean to see if the coin has been collected
       * @return true if collected, false if not
       */
      bool IsCollected() const;

      /**
       * Sets the value of the collected boolean
       * @param collected represents the collection state of the coin, true if collected, false if not
       */
      void SetIsCollected(bool collected);

      /**
       * Getter for the value of the coin
       * @return int representing the value contribution to the score when collected
       */
      int GetValue() const;

      /**
       * Draws the coin using cinder::gl::drawSolidCircle();
       */
      void DrawCoin() const;
      
      /**
       * Checks if the provided player has collided with the coin object on the game map
       * @param player the player for which to check the collision
       * @return true if player is colliding, false if not
       */
      bool CheckCoinCollision(const Player& player);

      /**
       * Getter for the position of the coin
       * @return a vec2 representing the current position of the coin in x and y coordinates
       */
      const vec2 &GetPosition() const;

      /**
       * Setter for the position of the coin
       * @param position a vec2 to represent the new position of the coin
       */
      void SetPosition(const vec2 &position);

  private:
      ci::Color kColor = "goldenrod";
      float kXRadius = 24; //radius in x direction
      float kYRadius = 30; //radius in y direction
      vec2 position_;
      float max_x_; //max position in the x direction that the coin can spawn
      float max_y_; //min position in the y direction that the coin can spawn
      float margin_; //margin from the walls to define a spawning window for the car
      int value_; //contribution to the score
      bool collected_; //bool to see if this coin has been claimed or not
  };
}