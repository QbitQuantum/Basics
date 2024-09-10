void
BTextControl::Draw(BRect updateRect)
{
	bool enabled = IsEnabled();
	bool active = fText->IsFocus() && Window()->IsActive();

	BRect rect = fText->Frame();
	rect.InsetBy(-2, -2);

	if (be_control_look != NULL) {
		rgb_color base = ui_color(B_PANEL_BACKGROUND_COLOR);
		uint32 flags = 0;
		if (!enabled)
			flags |= BControlLook::B_DISABLED;
		if (active)
			flags |= BControlLook::B_FOCUSED;
		be_control_look->DrawTextControlBorder(this, rect, updateRect, base,
			flags);

		rect = Bounds();
		rect.right = fDivider - kLabelInputSpacing;
//		rect.right = fText->Frame().left - 2;
//		rect.right -= 3;//be_control_look->DefaultLabelSpacing();
		be_control_look->DrawLabel(this, Label(), rect, updateRect,
			base, flags, BAlignment(fLabelAlign, B_ALIGN_MIDDLE));

		return;
	}

	// outer bevel

	rgb_color noTint = ui_color(B_PANEL_BACKGROUND_COLOR);
	rgb_color lighten1 = tint_color(noTint, B_LIGHTEN_1_TINT);
	rgb_color lighten2 = tint_color(noTint, B_LIGHTEN_2_TINT);
	rgb_color lightenMax = tint_color(noTint, B_LIGHTEN_MAX_TINT);
	rgb_color darken1 = tint_color(noTint, B_DARKEN_1_TINT);
	rgb_color darken2 = tint_color(noTint, B_DARKEN_2_TINT);
	rgb_color darken4 = tint_color(noTint, B_DARKEN_4_TINT);
	rgb_color navigationColor = ui_color(B_KEYBOARD_NAVIGATION_COLOR);

	if (enabled)
		SetHighColor(darken1);
	else
		SetHighColor(noTint);

	StrokeLine(rect.LeftBottom(), rect.LeftTop());
	StrokeLine(rect.RightTop());

	if (enabled)
		SetHighColor(lighten2);
	else
		SetHighColor(lighten1);

	StrokeLine(BPoint(rect.left + 1.0f, rect.bottom), rect.RightBottom());
	StrokeLine(BPoint(rect.right, rect.top + 1.0f), rect.RightBottom());

	// inner bevel

	rect.InsetBy(1.0f, 1.0f);

	if (active) {
		SetHighColor(navigationColor);
		StrokeRect(rect);
	} else {
		if (enabled)
			SetHighColor(darken4);
		else
			SetHighColor(darken2);

		StrokeLine(rect.LeftTop(), rect.LeftBottom());
		StrokeLine(rect.LeftTop(), rect.RightTop());

		SetHighColor(noTint);
		StrokeLine(BPoint(rect.left + 1.0f, rect.bottom), rect.RightBottom());
		StrokeLine(BPoint(rect.right, rect.top + 1.0f));
	}

	// label

	if (Label()) {
		_ValidateLayoutData();
		font_height& fontHeight = fLayoutData->font_info;

		float y = Bounds().top + (Bounds().Height() + 1 - fontHeight.ascent
			- fontHeight.descent) / 2 + fontHeight.ascent;
		float x;

		float labelWidth = StringWidth(Label());
		switch (fLabelAlign) {
			case B_ALIGN_RIGHT:
				x = fDivider - labelWidth - kLabelInputSpacing;
				break;

			case B_ALIGN_CENTER:
				x = fDivider - labelWidth / 2.0;
				break;

			default:
				x = 0.0;
				break;
		}

		BRect labelArea(x, Bounds().top, x + labelWidth, Bounds().bottom);
		if (x < fDivider && updateRect.Intersects(labelArea)) {
			labelArea.right = fText->Frame().left - kLabelInputSpacing;

			BRegion clipRegion(labelArea);
			ConstrainClippingRegion(&clipRegion);
			SetHighColor(IsEnabled() ? ui_color(B_CONTROL_TEXT_COLOR)
				: tint_color(noTint, B_DISABLED_LABEL_TINT));
			DrawString(Label(), BPoint(x, y));
		}
	}
}