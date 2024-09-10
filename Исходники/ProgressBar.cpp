ProgressBar::ProgressBar(const Widget2 *const widget, float progress,
                         const int width, const int height,
                         const int color):
    gcn::Widget(),
    Widget2(widget),
    gcn::WidgetListener(),
    mSkin(nullptr),
    mProgress(progress),
    mProgressToGo(progress),
    mSmoothProgress(true),
    mProgressPalette(color),
    mColor(Theme::getProgressColor(color >= 0 ? color : 0, mProgress)),
    mColorToGo(mColor),
    mSmoothColorChange(true),
    mText(),
    mVertexes(new ImageCollection),
    mRedraw(true),
    mPadding(2),
    mFillPadding(3),
    mOutlineColor(getThemeColor(Theme::OUTLINE))
{
    // The progress value is directly set at load time:
    if (mProgress > 1.0f || mProgress < 0.0f)
        mProgress = 1.0f;

    mForegroundColor = getThemeColor(Theme::PROGRESS_BAR);
    addWidgetListener(this);
    setSize(width, height);

    if (Theme::instance())
    {
        mSkin = Theme::instance()->load("progressbar.xml", "");
        setPadding(mSkin->getPadding());
        mFillPadding = mSkin->getOption("fillPadding");
        setHeight(2 * mPadding + getFont()->getHeight() + 2);
    }

    mInstances++;
}