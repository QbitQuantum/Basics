ShortcutContainer::ShortcutContainer(Widget2 *const widget) :
    Widget(widget),
    WidgetListener(),
    MouseListener(),
    mBackgroundImg(nullptr),
    mMaxItems(0),
    mBoxWidth(1),
    mBoxHeight(1),
    mGridWidth(1),
    mGridHeight(1),
    mVertexes(new ImageCollection)
{
    mAllowLogic = false;

    addMouseListener(this);
    addWidgetListener(this);

    mForegroundColor = getThemeColor(ThemeColorId::TEXT);
    mForegroundColor2 = getThemeColor(ThemeColorId::TEXT_OUTLINE);

    mBackgroundImg = Theme::getImageFromThemeXml(
        "item_shortcut_background.xml", "background.xml");

    if (mBackgroundImg)
    {
        mBackgroundImg->setAlpha(settings.guiAlpha);
        mBoxHeight = mBackgroundImg->getHeight();
        mBoxWidth = mBackgroundImg->getWidth();
    }
    else
    {
        mBoxHeight = 1;
        mBoxWidth = 1;
    }
}