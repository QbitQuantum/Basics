static inline LayoutUnit resolveLengthAttributeForSVG(const Length& length, float scale, float maxSize, RenderView* renderView)
{
    return static_cast<LayoutUnit>(valueForLength(length, maxSize, renderView) * (length.isFixed() ? scale : 1));
}