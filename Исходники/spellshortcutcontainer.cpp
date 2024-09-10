void SpellShortcutContainer::setSkin(const Widget2 *const widget,
                                     Skin *const skin)
{
    ShortcutContainer::setSkin(widget, skin);
    mForegroundColor = getThemeColor(ThemeColorId::TEXT, 255U);
    mForegroundColor2 = getThemeColor(ThemeColorId::TEXT_OUTLINE, 255U);
}