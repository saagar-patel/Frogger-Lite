#pragma once

#include "cinder/gl/gl.h"
#include "car.h"

namespace frogger {

    using glm::vec2;
    
    class Road {

    public:
        Road(std::vector<vec2> spawnpoints, int num_cars, float min_speed, float max_speed, bool direction);

        bool IsCarReachedEnd(const Car& car) const;
        
        const vec2 &GetCurrentSpawnpoint() const;

        void SetLeftToRightMovement(bool leftToRightMovement);

        bool IsLeftToRightMovement() const;

        void SetCurrentSpawnpoint(const vec2 &currentSpawnpoint);

        void SetDestructionPoint(const vec2 &destructionPoint);

        const std::vector<vec2> &GetSpawnpoints() const;

        std::vector<Car> &GetCars();
        
    private:
        std::vector<Car> cars_;
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