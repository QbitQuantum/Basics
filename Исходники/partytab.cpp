PartyTab::PartyTab(const Widget2 *const widget) :
    // TRANSLATORS: party chat tab name
    ChatTab(widget, _("Party"), "")
{
    setTabColor(&getThemeColor(Theme::PARTY_CHAT_TAB),
        &getThemeColor(Theme::PARTY_CHAT_TAB_OUTLINE));
    setHighlightedTabColor(&getThemeColor(Theme::PARTY_CHAT_TAB_HIGHLIGHTED),
        &getThemeColor(Theme::PARTY_CHAT_TAB_HIGHLIGHTED_OUTLINE));
    setSelectedTabColor(&getThemeColor(Theme::PARTY_CHAT_TAB_SELECTED),
        &getThemeColor(Theme::PARTY_CHAT_TAB_SELECTED_OUTLINE));
}