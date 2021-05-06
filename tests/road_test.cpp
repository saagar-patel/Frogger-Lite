#include <road.h>

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include "cinder/gl/gl.h"

using glm::vec2;
using frogger::Road;
using frogger::Car;

TEST_CASE("Test isCarReachedEnd") {
  std::vector<vec2> spawnpoints{vec2(100, 100), vec2(300, 100)};
  Road road = Road(spawnpoints, 1, 5, 6, true);
  SECTION("Car has reached end") {
    road.GetCars()[0].PlaceCar(vec2(100, 100));
    REQUIRE(road.GetCurrentSpawnpoint() == vec2(100, 100)); //change this to is car reached end
  }
}
