#include "frogger_app.h"
#include "level.h"
namespace frogger {
    
FroggerApp::FroggerApp() : level_(Level(3)){
    ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
    level_;
}

void FroggerApp::draw() {
    ci::Color background_color("black");
    ci::gl::clear(background_color);
    
    level_.Display();
}

void FroggerApp::update() {
    level_.AdvanceOneFrame();
}

void FroggerApp::keyDown(ci::app::KeyEvent event) {
    switch (event.getCode()) {
        case ci::app::KeyEvent::KEY_w:
            level_.GetPlayer().MoveUp();
            ci::gl::drawStringCentered("Pressed W", vec2(1000, 1000), ci::Color("pink"));
            break;

        case ci::app::KeyEvent::KEY_a:
            level_.GetPlayer().MoveLeft();
            break;

        case ci::app::KeyEvent::KEY_s:
            level_.GetPlayer().MoveDown();
            break;

        case ci::app::KeyEvent::KEY_d:
            level_.GetPlayer().MoveRight();
            break;
    }
}

}

