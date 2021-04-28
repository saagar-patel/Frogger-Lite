#pragma once

#include "cinder/gl/gl.h"
#include "Car_Obstacle.h"

namespace frogger {

    using glm::vec2;
    
    class Road {

    public:
        Road(std::vector<vec2> spawnpoints, int num_cars, float min_speed, float max_speed);
        
        void MoveCarsOnRoad(int score, int level, float road_width);
        
        const std::vector<vec2> &GetSpawnpoints() const;

        void SetSpawnpoints(const std::vector<vec2> &spawnpoints);

        const std::vector<Car> &GetCars() const;

        void SetCars(const std::vector<Car> &cars);

        int GetNumCars() const;

        void SetNumCars(int numCars);

        float GetMinSpeed() const;

        void SetMinSpeed(float minSpeed);

        float GetMaxSpeed() const;

        void SetMaxSpeed(float maxSpeed);
        
        const vec2 &GetCurrentSpawnpoint() const;

        void SetCurrentSpawnpoint(const vec2 &currentSpawnpoint);

    private:
        float kDifficultDenom = 2000;
        std::vector<vec2> spawnpoints_;
        vec2 current_spawnpoint_;
        vec2 destruction_point_;
        bool left_to_right_movement_;
        std::vector<Car> cars_;
        int num_cars_;
        float min_speed_;
        float max_speed_;

        void CreateCarObstacles();
        void DetermineDirection();
        bool EvaluateCarRelease(Car car, float road_width);
    };
}