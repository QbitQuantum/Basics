EquipmentWindow::EquipmentWindow(Equipment *const equipment,
                                 Being *const being,
                                 const bool foring):
    // TRANSLATORS: equipment window name
    Window(_("Equipment"), false, nullptr, "equipment.xml"),
    gcn::ActionListener(),
    mEquipment(equipment),
    mItemPopup(new ItemPopup),
    mPlayerBox(new PlayerBox("equipment_playerbox.xml",
        "equipment_selectedplayerbox.xml")),
    // TRANSLATORS: equipment window button
    mUnequip(new Button(this, _("Unequip"), "unequip", this)),
    mSelected(-1),
    mForing(foring),
    mImageSet(nullptr),
    mBeing(being),
    mBoxes(),
    mHighlightColor(getThemeColor(Theme::HIGHLIGHT)),
    mBorderColor(getThemeColor(Theme::BORDER)),
    mLabelsColor(getThemeColor(Theme::LABEL)),
    mLabelsColor2(getThemeColor(Theme::LABEL_OUTLINE)),
    mSlotBackground(),
    mSlotHighlightedBackground(),
    mVertexes(new ImageCollection),
    mItemPadding(getOption("itemPadding")),
    mBoxSize(getOption("boxSize")),
    mButtonPadding(getOption("buttonPadding", 5)),
    mMinX(180),
    mMinY(345),
    mMaxX(0),
    mMaxY(0)
{
    if (setupWindow)
        setupWindow->registerWindowForReset(this);

    if (!mBoxSize)
        mBoxSize = 36;

    // Control that shows the Player
    mPlayerBox->setDimension(gcn::Rectangle(50, 80, 74, 168));
    mPlayerBox->setPlayer(being);

    if (foring)
        setWindowName("Being equipment");
    else
        setWindowName("Equipment");

    setCloseButton(true);
    setSaveVisible(true);
    setStickyButtonLock(true);

    mBoxes.reserve(BOX_COUNT);
    for (int f = 0; f < BOX_COUNT; f ++)
        mBoxes.push_back(nullptr);

    fillBoxes();
    recalcSize();

    loadWindowState();

    const gcn::Rectangle &area = getChildrenArea();
    mUnequip->setPosition(area.width  - mUnequip->getWidth() - mButtonPadding,
        area.height - mUnequip->getHeight() - mButtonPadding);
    mUnequip->setEnabled(false);

    ImageRect rect;
    Theme::instance()->loadRect(rect, "equipment_background.xml", "", 0, 1);
    mSlotBackground = rect.grid[0];
    mSlotHighlightedBackground = rect.grid[1];
    add(mPlayerBox);
    add(mUnequip);
    enableVisibleSound(true);
}