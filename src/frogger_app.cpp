#include "frogger_app.h"
#include "level.h"
namespace frogger {
    
FroggerApp::FroggerApp() : level_(Level(3)){
    ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
    level_;
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

  ci::gl::color(ci::Color("seagreen"));
  level_.Display();
}

void FroggerApp::update() {
    level_.AdvanceOneFrame();
}

void FroggerApp::keyDown(ci::app::KeyEvent event) {
    switch (event.getCode()) {
        case ci::app::KeyEvent::KEY_w:
            level_.isMovingForward = true;
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
      level_.isMovingForward = false;
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

