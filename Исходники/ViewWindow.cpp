bool ViewWindow::open()
    {
    // make window
    if(!ViewPlatformSupport::makeWindow(screen, "EOS Window", 0, 0, width, height, fullscreen, &winData))
        return false;

    //Initialize OpenGL
    if(!this->initGL())
        return false;

    // resize the initial window
    this->resize(this->width, this->height);

    // release context to other modules
    releaseContext();

    return true;
    }