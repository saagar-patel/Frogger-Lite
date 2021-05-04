#pragma once

#include "cinder/gl/gl.h"
#include "alligator.h"
#include "Player.h"

namespace frogger {
    using glm::vec2;
    class Stream {
      public:
        Stream(std::vector<vec2> spawnpoints, float min_speed, float max_speed,
               bool direction, float top_bound, float bot_bound, float player_move_speed);
        
        bool isGatorReachedEnd(const Alligator& gator) const;
        
        bool isPlayerInStream(const Player &player) const;

        bool isLeftToRight() const;

        void SetLeftToRight(bool leftToRight);

        const vec2 &GetCurrentSpawnpoint() const;

        void SetCurrentSpawnpoint(const vec2 &currentSpawnpoint);

        const vec2 &GetResetPoint() const;

        void SetResetPoint(const vec2 &resetPoint);

        void SetPlayerMoveSpeed(float playerMoveSpeed);

        float GetPlayerMoveSpeed() const;

        const std::vector<vec2> &GetSpawnpoints() const;

        std::vector<Alligator> gators_;
      private:
        int kNumGators = 2;
        float player_move_speed_;
        bool left_to_right_;
        std::vector<vec2> spawnpoints_;
        float min_speed_;
        float max_speed_;
        float stream_width;
        float top_bound_;
        float bot_bound_;
        vec2 current_spawnpoint_;
        vec2 reset_point;
        
        void CreateGatorObstacles();
    };
}