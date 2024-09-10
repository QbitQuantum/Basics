void CharsetListWin::DrawItem(wal::GC &gc, int n, crect rect)
{
	if (cList && n >= 0 && n < cCount)
	{
		bool frame = false;
		
		UiCondList ucl;
		if ((n % 2)==0) ucl.Set(uiOdd, true);
		if (n == this->GetCurrent()) ucl.Set(uiCurrentItem, true);
		
		unsigned bg = UiGetColor(uiBackground, uiItem, &ucl, 0xFFFFFF);
		unsigned textColor = UiGetColor(uiColor, uiItem, &ucl, 0);
		unsigned frameColor = UiGetColor(uiFrameColor, uiItem, &ucl, 0);;

		if (n == this->GetCurrent())
			frame = true;
			
		gc.SetFillColor(bg);
		gc.FillRect(rect);
		gc.Set(GetFont());

		int x = 0;
		const unicode_t *txt = 0;

		gc.SetTextColor(textColor);
		gc.TextOutF(rect.left+10, rect.top+2, utf8_to_unicode(cList[n]->name).ptr());
		gc.TextOutF(rect.left+10+15*fontW, rect.top+2, utf8_to_unicode(cList[n]->comment).ptr() );
	} else {
		gc.SetFillColor(UiGetColor(uiBackground, uiItem, 0, 0xFFFFFF));
		gc.FillRect(rect);
	}
}