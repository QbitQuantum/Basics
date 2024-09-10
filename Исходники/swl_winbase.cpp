void TBToolTip::Paint(wal::GC &gc, const crect &paintRect)
{
	gc.SetFillColor(UiGetColor(uiBackground, 0,0, 0xFFFFFF)/*GetColor(IC_BG)*/); //0x80FFFF);
	crect r = ClientRect();
	gc.FillRect(r);
	gc.SetTextColor(UiGetColor(uiColor, 0,0, 0)/*GetColor(IC_TEXT)*/);
	//gc.TextOutF(0,0,text.ptr());
	 DrawStaticText(gc, 2, 1, text.ptr(), GetFont(), false);
}