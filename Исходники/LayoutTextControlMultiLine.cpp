LayoutUnit LayoutTextControlMultiLine::preferredContentLogicalWidth(float charWidth) const
{
    int factor = toHTMLTextAreaElement(node())->cols();
    return static_cast<LayoutUnit>(ceilf(charWidth * factor)) + scrollbarThickness();
}