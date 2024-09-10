void CGUITabControl::selectTab(core::position2d<s32> p)
{
	IGUISkin* skin = Environment->getSkin();
	IGUIFont* font = skin->getFont();

	core::rect<s32> frameRect(AbsoluteRect);

	s32 tabheight = skin->getSize(gui::EGDS_BUTTON_HEIGHT);
	frameRect.UpperLeftCorner.Y += 2;
	frameRect.LowerRightCorner.Y = frameRect.UpperLeftCorner.Y + tabheight;
	s32 pos = frameRect.UpperLeftCorner.X + 2;

	for (u32 i=0; i<Tabs.size(); ++i)
	{
		// get Text
		const wchar_t* text = 0;
		if (Tabs[i])
			text = Tabs[i]->getText();

		// get text length
		s32 len = 20;
		if (font)
			len += font->getDimension(text).Width;

		frameRect.UpperLeftCorner.X = pos;
		frameRect.LowerRightCorner.X = frameRect.UpperLeftCorner.X + len;
		pos += len;

		if (frameRect.isPointInside(p))
		{
			setActiveTab(i);
			return;
		}
	}
}