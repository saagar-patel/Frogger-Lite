#pragma once

#include "cinder/gl/gl.h"
#include "Car_Obstacle.h"

namespace frogger {

    using glm::vec2;
    
    class Road {

    public:
        Road(std::vector<vec2> spawnpoints, int num_cars, float min_speed, float max_speed, bool direction);

        bool isCarReachedEnd(const Car& car) const;
        
        const vec2 &GetCurrentSpawnpoint() const;
        
        const vec2 &GetDestructionPoint() const;

        void SetLeftToRightMovement(bool leftToRightMovement);

        bool isLeftToRightMovement() const;

        void SetCurrentSpawnpoint(const vec2 &currentSpawnpoint);

        void SetDestructionPoint(const vec2 &destructionPoint);

        const std::vector<vec2> &GetSpawnpoints() const;

        std::vector<Car> cars_;

        
    private:
        float kDifficultDenom = 2000;
        
        float road_width_;
        std::vector<vec2> spawnpoints_;
        vec2 current_spawnpoint_;
        vec2 destruction_point_;
        bool left_to_right_movement_;
        int num_cars_;
        float min_speed_;
        float max_speed_;

        void CreateCarObstacles();
        
        
    };
}