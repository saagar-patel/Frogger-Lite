#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "level.h"
#include "cinder/Font.h"

namespace frogger {
class FroggerApp : public ci::app::App {
  public:
    FroggerApp();
    
    /**
     * Setup function for cinder
     */
    void setup() override;
    
    /**
     * Draw function for cinder
     */
    void draw() override;
    
    /**
     * Update function for cinder
     */
    void update() override;
    
    /**
     * Handler for when a key is pressed down
     * @param event which specific key is pressed
     */
    void keyDown(ci::app::KeyEvent event) override;
    
    /**
     * Handler for when a key is released
     * @param event which key is released
     */
    void keyUp(ci::app::KeyEvent event) override;
    
  private:
    int kWindowSizeX = 2400;
    int kWindowSizeY = 2000;
    int kTopMargin = 150;
    
    ci::gl::Texture2dRef background_; // stores the background image used in the game
    Level level_; //level object that has the main game logic
    
};
}