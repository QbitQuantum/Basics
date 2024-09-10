void LLAccordionCtrl::show_hide_scrollbar(S32 width, S32 height)
{
	calcRecuiredHeight();
	if(getRecuiredHeight() > height )
		showScrollbar(width,height);
	else
		hideScrollbar(width,height);
}