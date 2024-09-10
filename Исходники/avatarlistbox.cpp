AvatarListBox::AvatarListBox(const Widget2 *const widget,
                             AvatarListModel *const model) :
    ListBox(widget, model, "avatarlistbox.xml"),
    mImagePadding(mSkin ? mSkin->getOption("imagePadding") : 0),
    mShowGender(config.getBoolValue("showgender")),
    mShowLevel(config.getBoolValue("showlevel"))
{
    instances++;

    if (instances == 1)
    {
        onlineIcon = Theme::getImageFromThemeXml("circle-on.xml", "");
        offlineIcon = Theme::getImageFromThemeXml("circle-off.xml", "");
    }

    setWidth(200);

    config.addListener("showgender", this);
    config.addListener("showlevel", this);

    mForegroundColor = getThemeColor(ThemeColorId::TEXT);
    mForegroundColor2 = getThemeColor(ThemeColorId::TEXT_OUTLINE);
}