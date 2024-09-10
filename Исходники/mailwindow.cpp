MailWindow::MailWindow() :
    // TRANSLATORS: mail window name
    Window(_("Mail"), Modal_false, nullptr, "mail.xml"),
    ActionListener(),
    mMessages(),
    mMessagesMap(),
    mMailModel(new ExtendedNamesModel),
    mListBox(CREATEWIDGETR(ExtendedListBox,
        this, mMailModel, "extendedlistbox.xml")),
    mListScrollArea(new ScrollArea(this, mListBox,
        fromBool(getOptionBool("showlistbackground"), Opaque),
        "mail_listbackground.xml")),
    // TRANSLATORS: mail window button
    mRefreshButton(new Button(this, _("Refresh"), "refresh", this)),
    // TRANSLATORS: mail window button
    mNewButton(new Button(this, _("New"), "new", this)),
    // TRANSLATORS: mail window button
    mDeleteButton(new Button(this, _("Delete"), "delete", this)),
    // TRANSLATORS: mail window button
    mReturnButton(new Button(this, _("Return"), "return", this)),
    // TRANSLATORS: mail window button
    mOpenButton(new Button(this, _("Open"), "open", this))
{
    setWindowName("Mail");
    setCloseButton(true);
    setResizable(true);
    setCloseButton(true);
    setSaveVisible(true);
    setStickyButtonLock(true);

    if (setupWindow)
        setupWindow->registerWindowForReset(this);

    setDefaultSize(310, 180, ImagePosition::CENTER);
    setMinWidth(310);
    setMinHeight(250);
    center();

    mListScrollArea->setHorizontalScrollPolicy(ScrollArea::SHOW_NEVER);

    ContainerPlacer placer;
    placer = getPlacer(0, 0);

    placer(0, 0, mListScrollArea, 4, 5).setPadding(3);
    placer(4, 0, mRefreshButton);
    placer(4, 1, mOpenButton);
    placer(4, 2, mNewButton);
    placer(4, 3, mDeleteButton);
    placer(4, 4, mReturnButton);

    Layout &layout = getLayout();
    layout.setRowHeight(0, LayoutType::SET);

    loadWindowState();
    enableVisibleSound(true);
}