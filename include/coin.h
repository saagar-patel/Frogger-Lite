#pragma once

#include "cinder/gl/gl.h"
#include "Player.h"

namespace frogger {
    using glm::vec2;

    class Coin {
      public:
        Coin(float max_x_size, float max_y_size, float margin, int value);

        const vec2 &GetPosition() const;

        void SetPosition(const vec2 &position);
        
        void SetToRandomPosition();

        bool IsCollected() const;

        void SetIsCollected(bool collected);

        int GetValue() const;

        void DrawCoin();
        
        bool CheckCoinCollision(const Player& player);
        
    private:
        ci::Color kColor = "goldenrod";
        float kXRadius = 24;
        float kYRadius = 30;
        vec2 position_;
        float max_x_;
        float max_y_;
        float margin_;
        int value_;
        bool collected_;
    };
}