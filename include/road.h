#pragma once

#include "cinder/gl/gl.h"
#include "car.h"

namespace frogger {

    using glm::vec2;
    
    class Road {

    public:
        /**
         * Constructor for road object
         * @param spawnpoints a vector containing vec2 with two possible spawnpoints, reset_point and spawnpoint are
         * chose from this
         * @param num_cars number of cars on road
         * @param min_speed the min base speed of the cars
         * @param max_speed the max base speed of the cars
         * @param left_to_right boolean to represent direction of car movement on road
         */
        Road(std::vector<vec2> spawnpoints, int num_cars, float min_speed, float max_speed, bool left_to_right);

        /**
         * Determine if a car has reached a reset point
         * @param car check if this car has reached the reset point
         * @return boolean, true = car has reached end, false = car has not reached end
         */
        bool IsCarReachedEnd(const Car& car) const;
        
        /**
         * Getter for the current spawnpoint
         * @return vec2 for the current spawnpoint
         */
        const vec2 &GetCurrentSpawnpoint() const;

        /**
         * Setter for the bool representing movement direction
         * @param leftToRightMovement true = left -> right, false = right -> left
         */
        void SetLeftToRightMovement(bool leftToRightMovement);

        /**
         * Getter for the bool representing movement direction
         * @return bool, true = left->right, false = right -> left
         */
        bool IsLeftToRightMovement() const;

        /**
         * Setter for the current spawnpoint
         * @param currentSpawnpoint vec2 with coordinates for the new spawnpoint
         */
        void SetCurrentSpawnpoint(const vec2 &currentSpawnpoint);

        /**
         * Setter for the destruction point
         * @param destructionPoint vec2 representing new coordinates of the spawn point
         */
        void SetDestructionPoint(const vec2 &destructionPoint);

        /**
         * Getter for the vector of all possible spawnpoints and reset points for this road
         * @return a vector containing vec2s representing the coordinates of the spawnpoints
         */
        const std::vector<vec2> &GetSpawnpoints() const;

        /**
         * Getter for the vector storing all the Cars that belong to this road
         * @return vector of Car objects
         */
        std::vector<Car> &GetCars();
        
    private:
        std::vector<Car> cars_;
        float road_width_;//x-direction width of road
        std::vector<vec2> spawnpoints_;
        vec2 current_spawnpoint_; //point which cars are reset to
        vec2 destruction_point_; //point at which cars are reset
        bool left_to_right_movement_;
        int num_cars_;
        float min_speed_;//min base speed limit of this road
        float max_speed_;//max base speed limit of this road

        /**
         * Creates all the Car objects belonging to this road according to the member variables of this Road object
         */
        void CreateCarObstacles();
    };
}