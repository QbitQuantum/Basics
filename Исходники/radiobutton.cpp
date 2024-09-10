RadioButton::RadioButton(const Widget2 *const widget,
                         const std::string &caption, const std::string &group,
                         const bool marked):
    gcn::RadioButton(caption, group, marked),
    Widget2(widget),
    mHasMouse(false),
    mPadding(0),
    mImagePadding(0),
    mImageSize(9),
    mSpacing(2),
    mForegroundColor2(getThemeColor(Theme::RADIOBUTTON_OUTLINE))
{
    mForegroundColor = getThemeColor(Theme::RADIOBUTTON);
    if (instances == 0)
    {
        if (Theme::instance())
        {
            mSkin = Theme::instance()->load("radio.xml", "");
            updateAlpha();
        }
    }

    instances++;

    if (mSkin)
    {
        mPadding = mSkin->getPadding();
        mImagePadding = mSkin->getOption("imagePadding");
        mImageSize = mSkin->getOption("imageSize");
        mSpacing = mSkin->getOption("spacing");
    }

    adjustSize();
}