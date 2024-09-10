NavigationPlugin::NavigationPlugin(NPP inst) : SubPlugin(inst) {

    m_hasFocus = false;
    m_activeNav = NULL;

    m_paintDisabled = gPaintI.newPaint();
    gPaintI.setFlags(m_paintDisabled, gPaintI.getFlags(m_paintDisabled) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintDisabled, 0xFFFFFFFF);

    m_paintActive = gPaintI.newPaint();
    gPaintI.setFlags(m_paintActive, gPaintI.getFlags(m_paintActive) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintActive, 0xFFFFFF00);

    //register for key events
    ANPEventFlags flags = kKey_ANPEventFlag;
    NPError err = browser->setvalue(inst, kAcceptEvents_ANPSetValue, &flags);
    if (err != NPERR_NO_ERROR) {
        gLogI.log(kError_ANPLogType, "Error selecting input events.");
    }
}