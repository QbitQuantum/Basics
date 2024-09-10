//! draws the element and its children
void CGUICheckBox::draw()
{
	if (!IsVisible)
		return;

	IGUISkin* skin = Environment->getSkin();
	if (skin)
	{
		video::IVideoDriver* driver = Environment->getVideoDriver();
		core::rect<s32> frameRect(AbsoluteRect);

		// draw background
		if (Background)
		{
			video::SColor bgColor = skin->getColor(gui::EGDC_3D_FACE);
			driver->draw2DRectangle(bgColor, frameRect, &AbsoluteClippingRect);
		}

		// draw the border
		if (Border)
		{
			skin->draw3DSunkenPane(this, 0, true, false, frameRect, &AbsoluteClippingRect);
			frameRect.UpperLeftCorner.X += skin->getSize(EGDS_TEXT_DISTANCE_X);
			frameRect.LowerRightCorner.X -= skin->getSize(EGDS_TEXT_DISTANCE_X);
		}

		const s32 height = skin->getSize(EGDS_CHECK_BOX_WIDTH);

		// the rectangle around the "checked" area.
		core::rect<s32> checkRect(frameRect.UpperLeftCorner.X,
					((frameRect.getHeight() - height) / 2) + frameRect.UpperLeftCorner.Y,
					0, 0);

		checkRect.LowerRightCorner.X = checkRect.UpperLeftCorner.X + height;
		checkRect.LowerRightCorner.Y = checkRect.UpperLeftCorner.Y + height;

		EGUI_DEFAULT_COLOR col = EGDC_GRAY_EDITABLE;
		if ( isEnabled() )
			col = Pressed ? EGDC_FOCUSED_EDITABLE : EGDC_EDITABLE;
		skin->draw3DSunkenPane(this, skin->getColor(col),
			false, true, checkRect, &AbsoluteClippingRect);

		// the checked icon
		if (Checked)
		{
			skin->drawIcon(this, EGDI_CHECK_BOX_CHECKED, checkRect.getCenter(),
				CheckTime, os::Timer::getTime(), false, &AbsoluteClippingRect);
		}

		// associated text
		if (Text.size())
		{
			checkRect = frameRect;
			checkRect.UpperLeftCorner.X += height + 5;

			IGUIFont* font = skin->getFont();
			if (font)
			{
				font->draw(Text.c_str(), checkRect,
						skin->getColor(isEnabled() ? EGDC_BUTTON_TEXT : EGDC_GRAY_TEXT), false, true, &AbsoluteClippingRect);
			}
		}
	}
	IGUIElement::draw();
}