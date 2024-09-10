IntRect ScrollbarThemeMock::trackRect(const ScrollbarThemeClient& scrollbar, bool)
{
    return scrollbar.frameRect();
}