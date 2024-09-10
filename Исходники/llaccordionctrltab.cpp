void LLAccordionCtrlTab::show_hide_scrollbar(const LLRect& child_rect)
{
	if(getChildViewHeight() > child_rect.getHeight() )
		showScrollbar(child_rect);
	else
		hideScrollbar(child_rect);
}