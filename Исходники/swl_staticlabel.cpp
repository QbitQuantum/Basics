	void StaticLabel::Paint(GC& gc, const crect& paintRect)
	{
		crect rect = ClientRect();
		gc.SetFillColor(UiGetColor(uiBackground, uiClassStaticLabel, 0, 0xFFFFFF)/*GetColor(0)*/);
		gc.FillRect(rect); 
		gc.Set(GetFont());
		text.DrawItem(gc, 0, 0, 
			UiGetColor(uiColor, uiClassStaticLabel, 0, 0), 
			UiGetColor(uiHotkeyColor, uiClassStaticLabel, 0, 0));
	}