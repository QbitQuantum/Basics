void ItemShortcutContainer::setSkin(const Widget2 *const widget,
                                    Skin *const skin)
{
    ShortcutContainer::setSkin(widget, skin);
    mEquipedColor = getThemeColor(ThemeColorId::ITEM_EQUIPPED, 255U);
    mEquipedColor2 = getThemeColor(ThemeColorId::ITEM_EQUIPPED_OUTLINE, 255U);
    mUnEquipedColor = getThemeColor(ThemeColorId::ITEM_NOT_EQUIPPED, 255U);
    mUnEquipedColor2 = getThemeColor(ThemeColorId::ITEM_NOT_EQUIPPED_OUTLINE,
        255U);
    mForegroundColor = getThemeColor(ThemeColorId::TEXT, 255U);
    mForegroundColor2 = getThemeColor(ThemeColorId::TEXT_OUTLINE, 255U);
    if (mSkin != nullptr)
    {
        mKeyOffsetX = mSkin->getOption("keyOffsetX", 2);
        mKeyOffsetY = mSkin->getOption("keyOffsetY", 2);
    }
}