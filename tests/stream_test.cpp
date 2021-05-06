#include <stream.h>

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include "cinder/gl/gl.h"

using glm::vec2;
using frogger::Stream;
using frogger::Alligator;
using frogger::Player;

TEST_CASE("Test isGatorReachedEnd") {
  std::vector<vec2> spawnpoints{vec2(100, 100), vec2(300, 100)};
  Stream stream = Stream(spawnpoints, 5, 6, true, 50, 150, 10);
  SECTION("Gator reached end") {
    stream.GetGators()[0].PlaceGator(vec2(500, 100));
    REQUIRE(stream.IsGatorReachedEnd(stream.GetGators()[0]));
  }
  SECTION("Gator has not reached end") {
    stream.GetGators()[0].PlaceGator(vec2(200, 100));
    REQUIRE(!stream.IsGatorReachedEnd(stream.GetGators()[0]));
  }
  SECTION("Gator is through end point but has not reached end") {
    stream.GetGators()[0].PlaceGator(vec2(300, 100));
    REQUIRE(!stream.IsGatorReachedEnd(stream.GetGators()[0]));
  }
}

TEST_CASE("Test IsPlayerInStream") {
  Player player = Player(vec2(0,0), 3, 10);
  std::vector<vec2> spawnpoints{vec2(100, 100), vec2(300, 100)};
  Stream stream = Stream(spawnpoints, 5, 6, true, 100, 300, 10);
  SECTION("Player is in stream") {
    player.SetPosition(vec2(100, 200));
    REQUIRE(stream.isPlayerInStream(player));
  }
  SECTION("Player is barely in stream from bottom") {
    player.SetPosition(vec2(100, 309));
    REQUIRE(!stream.isPlayerInStream(player));
  }
  SECTION("Player is barely in stream from top") {
    player.SetPosition(vec2(100, 91));
    REQUIRE(stream.isPlayerInStream(player));
  }
  SECTION("Player is not in stream") {
    player.SetPosition(vec2(100, 400));
    REQUIRE(!stream.isPlayerInStream(player));
  }
}
