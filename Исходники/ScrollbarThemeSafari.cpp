IntRect ScrollbarThemeSafari::trackRect(Scrollbar& scrollbar, bool painting)
{
    if (painting || !hasButtons(scrollbar))
        return scrollbar.frameRect();
    
    IntRect result;
    int thickness = scrollbarThickness(scrollbar.controlSize());
    if (scrollbar.orientation() == HorizontalScrollbar) 
        return IntRect(scrollbar.x() + cButtonLength[scrollbar.controlSize()], scrollbar.y(), scrollbar.width() - 2 * cButtonLength[scrollbar.controlSize()], thickness);
    return IntRect(scrollbar.x(), scrollbar.y() + cButtonLength[scrollbar.controlSize()], thickness, scrollbar.height() - 2 * cButtonLength[scrollbar.controlSize()]);
}