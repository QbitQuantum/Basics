SpellPopup::SpellPopup():
    Popup("SpellPopup", "spellpopup.xml"),
    mItemName(new Label(this)),
    mItemComment(new Label(this))
{
    mItemName->setFont(boldFont);
    mItemName->setForegroundColorAll(getThemeColor(Theme::POPUP),
        getThemeColor(Theme::POPUP_OUTLINE));
    mItemComment->setForegroundColorAll(getThemeColor(Theme::POPUP),
        getThemeColor(Theme::POPUP_OUTLINE));

    add(mItemName);
    add(mItemComment);

    addMouseListener(this);
}