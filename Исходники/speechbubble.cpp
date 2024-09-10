void SpeechBubble::setText(const std::string &text, const bool showName)
{
    if (text == mText && (mCaption->getWidth() <= mSpeechBox->getWidth()))
        return;

    mSpeechBox->setForegroundColorAll(getThemeColor(ThemeColorId::BUBBLE_TEXT),
        getThemeColor(ThemeColorId::BUBBLE_TEXT_OUTLINE));

    int width = mCaption->getWidth();
    mSpeechBox->clearRows();
    mSpeechBox->addRow(text);
    mSpeechBox->setWidth(mSpeechBox->getDataWidth());

    const int speechWidth = mSpeechBox->getWidth();
    const int nameHeight = showName ? mCaption->getHeight() + mSpacing : 0;

    if (width < speechWidth)
        width = speechWidth;

    setContentSize(width, getFont()->getHeight() + nameHeight);
    mCaption->setPosition(0, 0);
    mSpeechBox->setPosition(0, nameHeight);
}