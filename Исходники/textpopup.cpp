TextPopup::TextPopup():
    Popup("TextPopup", "textpopup.xml"),
    mText1(new Label(this)),
    mText2(new Label(this)),
    mText3(new Label(this))
{
    const int fontHeight = getFont()->getHeight();

    mText1->setPosition(0, 0);
    mText2->setPosition(0, fontHeight);
    mText3->setPosition(0, 2 * fontHeight);
    mText1->setForegroundColorAll(getThemeColor(Theme::POPUP),
        getThemeColor(Theme::POPUP_OUTLINE));
    mText2->setForegroundColorAll(getThemeColor(Theme::POPUP),
        getThemeColor(Theme::POPUP_OUTLINE));
    mText3->setForegroundColorAll(getThemeColor(Theme::POPUP),
        getThemeColor(Theme::POPUP_OUTLINE));

    add(mText1);
    add(mText2);
    add(mText3);
    addMouseListener(this);
}