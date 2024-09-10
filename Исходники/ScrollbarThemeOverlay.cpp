IntRect ScrollbarThemeOverlay::trackRect(const ScrollbarThemeClient& scrollbar, bool)
{
    IntRect rect = scrollbar.frameRect();
    if (scrollbar.orientation() == HorizontalScrollbar)
        rect.inflateX(-m_scrollbarMargin);
    else
        rect.inflateY(-m_scrollbarMargin);
    return rect;
}