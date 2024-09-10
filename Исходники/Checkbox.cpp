    mCaption(),
    mPadding(0),
    mImagePadding(0),
    mImageSize(9),
    mSpacing(2),
    mHasMouse(false),
    mDrawBox(true)
{
    setCaption(caption);
    mAllowLogic = false;

    setFocusable(true);
    addMouseListener(this);
    addKeyListener(this);

    mForegroundColor2 = getThemeColor(Theme::CHECKBOX_OUTLINE);
    if (instances == 0)
    {
        if (theme)
        {
            mSkin = theme->load("checkbox.xml", "");
            updateAlpha();
        }
    }

    instances++;

    if (!eventId.empty())
        setActionEventId(eventId);

    if (listener)