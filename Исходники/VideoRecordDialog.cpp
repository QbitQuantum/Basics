void VideoRecordDialog::makeGUI() {
    pane()->addCheckBox("Record GUI (Surface2D)", &m_captureGUI);

    pane()->addLabel(GuiText("Video", shared_ptr<GFont>(), 12));
    GuiPane* moviePane = pane()->addPane("", GuiTheme::ORNATE_PANE_STYLE);

    GuiLabel* label = NULL;
    GuiDropDownList* formatList = moviePane->addDropDownList("Format", m_formatList, &m_templateIndex);

    const float width = 300.0f;
    // Increase caption size to line up with the motion blur box
    const float captionSize = 90.0f;

    formatList->setWidth(width);
    formatList->setCaptionWidth(captionSize);

    moviePane->addNumberBox("Quality", &m_quality, "", GuiTheme::LOG_SLIDER, 0.1f, 25.0f);
    
    if (false) {
        // For future expansion
        GuiCheckBox*  motionCheck = moviePane->addCheckBox("Motion Blur",  &m_enableMotionBlur);
        m_framesBox = moviePane->addNumberBox("", &m_motionBlurFrames, "frames", GuiTheme::LINEAR_SLIDER, 2, 20);
        m_framesBox->setUnitsSize(46);
        m_framesBox->moveRightOf(motionCheck);
        m_framesBox->setWidth(210);
    }

    GuiNumberBox<float>* recordBox   = moviePane->addNumberBox("Record as if",      &m_recordFPS, "fps", GuiTheme::NO_SLIDER, 1.0f, 120.0f, 0.1f);
    recordBox->setCaptionWidth(captionSize);

    GuiNumberBox<float>* playbackBox = moviePane->addNumberBox("Playback at",    &m_playbackFPS, "fps", GuiTheme::NO_SLIDER, 1.0f, 120.0f, 0.1f);
    playbackBox->setCaptionWidth(captionSize);

    const OSWindow* window = OSWindow::current();
    int w = window->width() / 2;
    int h = window->height() / 2;
    moviePane->addCheckBox(format("Half-size (%d x %d)", w, h), &m_halfSize);

    if (false) {
        // For future expansion
        moviePane->addCheckBox("Show cursor", &m_showCursor);
    }

    label = moviePane->addLabel("Hot key:");
    label->setWidth(captionSize);
    moviePane->addLabel(m_hotKeyString)->moveRightOf(label);

    // Add record on the same line as previous hotkey box
    m_recordButton = moviePane->addButton("Record Now (" + m_hotKeyString + ")");
    m_recordButton->moveBy(moviePane->rect().width() - m_recordButton->rect().width() - 5, -27);
    moviePane->pack();
    moviePane->setWidth(pane()->rect().width());

    ///////////////////////////////////////////////////////////////////////////////////
    pane()->addLabel(GuiText("Screenshot", shared_ptr<GFont>(), 12));
    GuiPane* ssPane = pane()->addPane("", GuiTheme::ORNATE_PANE_STYLE);

    m_ssFormatList.append("JPG", "PNG", "BMP", "TGA");
    GuiDropDownList* ssFormatList = ssPane->addDropDownList("Format", m_ssFormatList, &m_ssFormatIndex);
    m_ssFormatIndex = 0;

    ssFormatList->setWidth(width);
    ssFormatList->setCaptionWidth(captionSize);

    label = ssPane->addLabel("Hot key:");
    label->setWidth(captionSize);
    ssPane->addLabel(m_ssHotKeyString)->moveRightOf(label);

    ssPane->pack();
    ssPane->setWidth(pane()->rect().width());

    ///////////////////////////////////////////////////////////////////////////////////

    pack();
    setRect(Rect2D::xywh(rect().x0(), rect().y0(), rect().width() + 5, rect().height() + 2));
}