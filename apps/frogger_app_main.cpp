#include "frogger_app.h"

using frogger::FroggerApp;

void prepareSettings(FroggerApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(FroggerApp, ci::app::RendererGl, prepareSettings);