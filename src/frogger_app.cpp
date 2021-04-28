#include "frogger_app.h"
#include "level.h"
#include "cinder/Font.h"

namespace frogger {
    
FroggerApp::FroggerApp() : level_(Level()){
    ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
}

void FroggerApp::setup() {
  auto img = ci::loadImage((loadAsset("../assets/background-complete.png")));
  background = ci::gl::Texture2d::create(img);
}

void FroggerApp::draw() {
  ci::Color bg_color("white");
  ci::gl::clear(bg_color);

  ci::gl::color(ci::Color("white"));
  ci::gl::draw(background, ci::Rectf(vec2(0,0), vec2(kWindowSizeX, kWindowSizeY)));

  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, kTopMargin - 8), vec2(kWindowSizeX, kTopMargin)));

  ci::gl::drawStringCentered(
          "Level: " + std::to_string(level_.level_count_),
          glm::vec2((kWindowSizeX / 10) * 3, kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));

  ci::gl::drawStringCentered(
          "Score: " + std::to_string(level_.score_),
          glm::vec2(kWindowSizeX / 10, kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));

  ci::gl::drawStringCentered(
          "Lives: " + std::to_string(level_.GetPlayer().GetLives()),
          glm::vec2(8 * (kWindowSizeX / 10), kTopMargin/4),
          ci::Color("black"),
          ci::Font("Consolas", 100));
  
  ci::gl::color(ci::Color("pink"));
  level_.Display();
}

void FroggerApp::update() {
    level_.AdvanceOneFrame();
}

void FroggerApp::keyDown(ci::app::KeyEvent event) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_w:
        level_.isMovingUp = true;
        break;

      case ci::app::KeyEvent::KEY_a:
        level_.isMovingLeft = true;
        break;

      case ci::app::KeyEvent::KEY_s:
        level_.isMovingDown = true;
        break;

      case ci::app::KeyEvent::KEY_d:
        level_.isMovingRight = true;
        break;
    }
}

void FroggerApp::keyUp(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_w:
      level_.isMovingUp = false;
      break;

    case ci::app::KeyEvent::KEY_a:
      level_.isMovingLeft = false;
      break;

    case ci::app::KeyEvent::KEY_s:
      level_.isMovingDown = false;
      break;

    case ci::app::KeyEvent::KEY_d:
      level_.isMovingRight = false;
      break;
  }
}
}

