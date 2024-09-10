//----------------------------------------------------------------------------//
void FalagardTreeView::onLookNFeelAssigned()
{
    const WidgetLookFeel& wlf = getLookNFeel();
    d_subtreeExpanderImagery = &wlf.getImagerySection("SubtreeExpander");
    d_subtreeCollapserImagery = &wlf.getImagerySection("SubtreeCollapser");

    Sizef open_size = getImagerySize(*d_subtreeExpanderImagery);
    Sizef close_size = getImagerySize(*d_subtreeCollapserImagery);
    d_subtreeExpanderImagerySize = Sizef(
        (open_size.d_width + close_size.d_width) / 2.0f + getView()->getSubtreeExpanderMargin(),
        (open_size.d_height + close_size.d_height) / 2.0f + getView()->getSubtreeExpanderMargin());
}