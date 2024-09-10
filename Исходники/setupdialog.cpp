Setup::Setup():
    Window(_("Setup"))
{
    setWindowName("Setup");
    saveVisibility(false);
    setCloseButton(true);
    int width = 340 + 2 * getPadding();
    int height = 340 + 2 * getPadding() + getTitleBarHeight();

    static const char *buttonNames[] = {
        N_("Reset Windows"), N_("Cancel"), N_("Apply"), 0
    };

    mPanel = new TabbedArea();
    mPanel->setDimension(gcn::Rectangle(5, 5, width - 10, height - 40));

    mTabs.push_back(new Setup_Video());
    mTabs.push_back(new Setup_Audio());
    mTabs.push_back(new Setup_Input());
    mTabs.push_back(new Setup_Colors());

    for (std::list<SetupTabContainer*>::iterator i = mTabs.begin(),
         i_end = mTabs.end(); i != i_end; ++i)
    {
        SetupTabContainer *tab = *i;
        mPanel->addTab(tab->getName(), tab);
    }

    place(0, 0, mPanel, 7, 6).setPadding(2);

    for (int i = 0; buttonNames[i] != NULL; ++i)
    {
        Button *btn = new Button(gettext(buttonNames[i]), buttonNames[i], this);
        place(i + 4, 6, btn);

        // Store this button, as it needs to be enabled/disabled
        if (!strcmp(buttonNames[i], N_("Reset Windows")))
            mResetWindows = btn;
    }

    setDefaultSize(width, height, ImageRect::CENTER);

    Layout &layout = getLayout();
    layout.setRowHeight(0, Layout::AUTO_SET);

    loadWindowState();
}