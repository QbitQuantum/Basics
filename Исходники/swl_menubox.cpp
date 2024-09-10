void MenuBar::DrawItem(GC &gc, int n)
{
	if (n<0 || n>=list.count()) return;
	
	UiCondList ucl;
	if (n == select && InFocus()) ucl.Set(uiCurrentItem, true);
		
	int color_text = UiGetColor(uiColor, uiItem, &ucl, 0x0);
	int color_bg = UiGetColor(uiBackground, uiItem, &ucl, 0xFFFFFF);

	gc.Set(GetFont());
	crect itemRect = ItemRect(n);

	gc.SetFillColor(color_bg);
	if (n == select && InFocus()) gc.FillRect(itemRect);	

	if (n == select) {
		DrawBorder(gc, itemRect, UiGetColor(uiCurrentItemFrame, uiItem, &ucl, 0xFFFFFF));
	}

	gc.SetTextColor( color_text );
	
	const unicode_t *text = list[n].text.ptr();
	cpoint tsize = gc.GetTextExtents(text);
	int x = itemRect.left + (itemRect.Width()-tsize.x)/2;
	int y = itemRect.top + (itemRect.Height()-tsize.y)/2;
	
#ifdef _WIN32	
	gc.TextOut(x,y,text);
#else	
	gc.TextOutF(x,y,text);
#endif	
}