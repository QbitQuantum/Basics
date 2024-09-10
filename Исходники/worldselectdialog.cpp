WorldSelectDialog::WorldSelectDialog(Worlds worlds) :
    // TRANSLATORS: world select dialog name
    Window(_("Select World"), Modal_false, nullptr, "world.xml"),
    ActionListener(),
    KeyListener(),
    mWorldListModel(new WorldListModel(worlds)),
    mWorldList(new ListBox(this, mWorldListModel, "")),
    // TRANSLATORS: world dialog button
    mChangeLoginButton(new Button(this, _("Change Login"), "login", this)),
    // TRANSLATORS: world dialog button
    mChooseWorld(new Button(this, _("Choose World"), "world", this))
{
    mWorldList->postInit();
    ScrollArea *const worldsScroll = new ScrollArea(this, mWorldList,
        getOptionBool("showbackground"), "world_background.xml");

    worldsScroll->setHorizontalScrollPolicy(ScrollArea::SHOW_NEVER);

    place(0, 0, worldsScroll, 3, 5).setPadding(2);
    place(1, 5, mChangeLoginButton);
    place(2, 5, mChooseWorld);

    // Make sure the list has enough height
    getLayout().setRowHeight(0, 60);

    reflowLayout(0, 0);

    if (worlds.empty())
    {
        // Disable Ok button
        mChooseWorld->setEnabled(false);
    }
    else
    {
        // Select first server
        mWorldList->setSelected(0);
    }

    addKeyListener(this);

    center();
}