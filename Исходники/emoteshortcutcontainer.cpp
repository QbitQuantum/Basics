EmoteShortcutContainer::EmoteShortcutContainer():
    ShortcutContainer(),
    mEmoteImg(),
    mEmotePopup(new TextPopup),
    mForegroundColor2(getThemeColor(Theme::TEXT_OUTLINE)),
    mEmoteClicked(false),
    mEmoteMoved(0)
{
    addMouseListener(this);
    addWidgetListener(this);

    mBackgroundImg = Theme::getImageFromThemeXml(
        "item_shortcut_background.xml", "background.xml");

    if (mBackgroundImg)
        mBackgroundImg->setAlpha(Client::getGuiAlpha());

    // Setup emote sprites
    for (int i = 0; i <= EmoteDB::getLast(); i++)
    {
        const EmoteSprite *const sprite = EmoteDB::getSprite(i, true);
        if (sprite && sprite->sprite)
            mEmoteImg.push_back(sprite);
    }

    mMaxItems = MAX_ITEMS;

    if (mBackgroundImg)
    {
        mBoxHeight = mBackgroundImg->getHeight();
        mBoxWidth = mBackgroundImg->getWidth();
    }
    else
    {
        mBoxHeight = 1;
        mBoxWidth = 1;
    }
    mForegroundColor = getThemeColor(Theme::TEXT);
}