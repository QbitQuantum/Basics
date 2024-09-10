VideoPlugin::VideoPlugin(NPP inst, const char * path) : SurfaceSubPlugin(inst) {

    // initialize the drawing surface
    m_surface = NULL;

    //register for touch events
    ANPEventFlags flags = kTouch_ANPEventFlag;
    NPError err = browser->setvalue(inst, kAcceptEvents_ANPSetValue, &flags);
    if (err != NPERR_NO_ERROR) {
        gLogI.log(kError_ANPLogType, "Error selecting input events.");
    }

    if (path != NULL) {
        strcpy(mFilepath, path);
    }
}