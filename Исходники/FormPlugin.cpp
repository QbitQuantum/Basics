FormPlugin::FormPlugin(NPP inst) : SubPlugin(inst) {

    m_hasFocus = false;
    m_activeInput = NULL;

    memset(&m_usernameInput, 0, sizeof(m_usernameInput));
    memset(&m_passwordInput, 0, sizeof(m_passwordInput));

    m_usernameInput.text[0] = '\0';
    m_usernameInput.charPtr = 0;

    m_passwordInput.text[0] = '\0';
    m_passwordInput.charPtr = 0;

    m_paintInput = gPaintI.newPaint();
    gPaintI.setFlags(m_paintInput, gPaintI.getFlags(m_paintInput) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintInput, 0xFFFFFFFF);

    m_paintActive = gPaintI.newPaint();
    gPaintI.setFlags(m_paintActive, gPaintI.getFlags(m_paintActive) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintActive, 0xFFFFFF00);

    m_paintText = gPaintI.newPaint();
    gPaintI.setFlags(m_paintText, gPaintI.getFlags(m_paintText) | kAntiAlias_ANPPaintFlag);
    gPaintI.setColor(m_paintText, 0xFF000000);
    gPaintI.setTextSize(m_paintText, 18);

    ANPTypeface* tf = gTypefaceI.createFromName("serif", kItalic_ANPTypefaceStyle);
    gPaintI.setTypeface(m_paintText, tf);
    gTypefaceI.unref(tf);

    //register for key and visibleRect events
    ANPEventFlags flags = kKey_ANPEventFlag;
    NPError err = browser->setvalue(inst, kAcceptEvents_ANPSetValue, &flags);
    if (err != NPERR_NO_ERROR) {
        gLogI.log(kError_ANPLogType, "Error selecting input events.");
    }
}