#pragma once

#include "cinder/gl/gl.h"
#include "player.h"

namespace frogger {
    using glm::vec2;

    class Coin {
      public:
        Coin(float max_x_size, float max_y_size, float margin, int value);
        
        void SetToRandomPosition();

        bool IsCollected() const;

        void SetIsCollected(bool collected);

        int GetValue() const;

        void DrawCoin() const;
        
        bool CheckCoinCollision(const Player& player);
        
    private:
        ci::Color kColor = "goldenrod";
        float kXRadius = 24;
        float kYRadius = 30;
        vec2 position_;
        float max_x_; //max position in the x direction that the coin can spawn
        float max_y_; //min position in the y direction that the coin can spawn
        float margin_; //margin from the walls to define a spawning window for the car
        int value_; //contribution to the score
        bool collected_; //bool to see if this coin has been claimed or not
    };
}