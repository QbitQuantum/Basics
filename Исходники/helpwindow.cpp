HelpWindow::HelpWindow() :
    // TRANSLATORS: help window name
    Window(_("Help"), Modal_false, nullptr, "help.xml"),
    LinkHandler(),
    ActionListener(),
    // TRANSLATORS: help window. button.
    mDYKButton(new Button(this, _("Did you know..."), "DYK",
        BUTTON_SKIN, this)),
    mBrowserBox(new StaticBrowserBox(this, Opaque_true,
        "browserbox.xml")),
    mScrollArea(new ScrollArea(this, mBrowserBox,
        Opaque_true, "help_background.xml")),
    mTagFileMap()
{
    setMinWidth(300);
    setMinHeight(220);
    setContentSize(455, 350);
    setWindowName("Help");
    setCloseButton(true);
    setResizable(true);
    setStickyButtonLock(true);

    if (setupWindow != nullptr)
        setupWindow->registerWindowForReset(this);

    setDefaultSize(500, 400, ImagePosition::CENTER, 0, 0);

    mBrowserBox->setOpaque(Opaque_false);

    mBrowserBox->setLinkHandler(this);
    if (gui != nullptr)
        mBrowserBox->setFont(gui->getHelpFont());
    mBrowserBox->setProcessVars(true);
    mBrowserBox->setEnableImages(true);
    mBrowserBox->setEnableKeys(true);
    mBrowserBox->setEnableTabs(true);

    place(4, 3, mDYKButton, 1, 1);
    place(0, 0, mScrollArea, 5, 3).setPadding(3);

    Layout &layout = getLayout();
    layout.setRowHeight(0, LayoutType::SET);

    loadWindowState();
    loadTags();
    enableVisibleSound(true);
    widgetResized(Event(nullptr));
}