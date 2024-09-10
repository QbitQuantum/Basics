void MMSWindowManager::onThemeChanged(string themeName, bool fade_in) {
    // get access to the layer
    MMSFBLayer *layer = mmsfbmanager.getGraphicsLayer();
    this->anim_saved_screen = NULL;

    if (fade_in) {
        // create a temporary window to save the screen
        // so we can have a nice animation while switching the theme
        if (layer) {
            MMSFBSurfacePixelFormat pixelformat;
            layer->getPixelFormat(&pixelformat);
            int w, h;
            layer->getResolution(&w, &h);
            layer->createWindow(&this->anim_saved_screen, 0, 0, w, h,
                                pixelformat, isAlphaPixelFormat(pixelformat), 0);
        }
    }

    if (this->anim_saved_screen) {
        // get a screenshot
        this->anim_saved_screen->getScreenshot();

        // show the saved screen
        this->anim_saved_screen->raiseToTop();
        this->anim_saved_screen->setOpacity(255);
        this->anim_saved_screen->show();
    }

    // the theme has changed, inform all windows
    for (unsigned int i = 0; i < this->windows.size(); i++) {
        this->windows.at(i)->themeChanged(themeName);
    }

    if (this->anim_saved_screen) {
        // do the animation
        this->pulser.setMaxOffset(255,MMSPULSER_SEQ_LINEAR);
        this->pulser.setStepsPerSecond(255);
        this->pulser.start(false);
    }
}