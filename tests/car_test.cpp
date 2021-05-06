#include <road.h>

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include "cinder/gl/gl.h"

using glm::vec2;
using frogger::Car;
//car width = 80
//car length = 125
TEST_CASE("Test MoveCar") {
  Car car =Car(vec2(0,0), 10);
  SECTION("Test car moving left") {
    car.MoveCar(1, true);
    REQUIRE(car.GetBotRightEdge() == vec2(72.5,40));
    REQUIRE(car.GetTopLeftEdge() == vec2(-52.5,-40));
  }
  SECTION("Test car moving right") {
    car.MoveCar(1, false);
    REQUIRE(car.GetBotRightEdge() == vec2(52.5,40));
    REQUIRE(car.GetTopLeftEdge() == vec2(-72.5,-40));
  }
}

TEST_CASE("Test PlaceCar") {
  Car car =Car(vec2(0,0), 10);
  car.PlaceCar(vec2(100,100));
  REQUIRE(car.GetTopLeftEdge() == vec2(37.5,60));
  REQUIRE(car.GetBotRightEdge() == vec2(162.5,140));
}