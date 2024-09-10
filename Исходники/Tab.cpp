Tab::Tab(const Widget2 *const widget) :
    gcn::BasicContainer(),
    Widget2(widget),
    gcn::MouseListener(),
    gcn::WidgetListener(),
    mLabel(new Label(this)),
    mTabbedArea(nullptr),
    mTabColor(&getThemeColor(Theme::TAB)),
    mTabOutlineColor(&getThemeColor(Theme::TAB_OUTLINE)),
    mTabHighlightedColor(&getThemeColor(Theme::TAB_HIGHLIGHTED)),
    mTabHighlightedOutlineColor(&getThemeColor(
        Theme::TAB_HIGHLIGHTED_OUTLINE)),
    mTabSelectedColor(&getThemeColor(Theme::TAB_SELECTED)),
    mTabSelectedOutlineColor(&getThemeColor(Theme::TAB_SELECTED_OUTLINE)),
    mFlashColor(&getThemeColor(Theme::TAB_FLASH)),
    mFlashOutlineColor(&getThemeColor(Theme::TAB_FLASH_OUTLINE)),
    mPlayerFlashColor(&getThemeColor(Theme::TAB_PLAYER_FLASH)),
    mPlayerFlashOutlineColor(&getThemeColor(Theme::TAB_PLAYER_FLASH_OUTLINE)),
    mFlash(0),
    mVertexes(new ImageCollection),
    mImage(nullptr),
    mMode(0),
    mRedraw(true),
    mHasMouse(false)
{
    init();
}