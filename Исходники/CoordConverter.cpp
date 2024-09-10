float CoordConverter::getBaseXValue(const Window& window)
{
    const Window* parent = window.getParent();

    const Rectf parent_rect(parent ?
        parent->getChildContentArea(window.isNonClient()).get() :
        Rectf(Vector2f(0, 0), window.getRootContainerSize())
    );

    const float parent_width = parent_rect.getWidth();
    float baseX = parent_rect.d_min.d_x;

    baseX += asAbsolute(window.getArea().d_min.d_x, parent_width);

    switch(window.getHorizontalAlignment())
    {
        case HA_CENTRE:
            baseX += (parent_width - window.getPixelSize().d_width) * 0.5f;
            break;
        case HA_RIGHT:
            baseX += parent_width - window.getPixelSize().d_width;
            break;
        default:
            break;
    }

    return alignToPixels(baseX);
}