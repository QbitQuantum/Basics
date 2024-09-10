GuildChatTab::GuildChatTab(const Widget2 *const widget) :
    // TRANSLATORS: guild chat tab name
    ChatTab(widget, _("Guild"), "")
{
    setTabColor(&getThemeColor(Theme::GUILD_CHAT_TAB),
        &getThemeColor(Theme::GUILD_CHAT_TAB_OUTLINE));
    setHighlightedTabColor(&getThemeColor(Theme::GUILD_CHAT_TAB_HIGHLIGHTED),
        &getThemeColor(Theme::GUILD_CHAT_TAB_HIGHLIGHTED_OUTLINE));
    setSelectedTabColor(&getThemeColor(Theme::GUILD_CHAT_TAB_SELECTED),
        &getThemeColor(Theme::GUILD_CHAT_TAB_SELECTED_OUTLINE));
    mShowOnline = config.getBoolValue("showGuildOnline");
    config.addListener("showGuildOnline", this);
}