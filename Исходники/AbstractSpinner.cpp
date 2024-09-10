void
BAbstractSpinner::_DrawTextView(BRect updateRect)
{
	BRect rect = fTextView->Frame();
	rect.InsetBy(-kFrameMargin, -kFrameMargin);
	if (!rect.IsValid() || !rect.Intersects(updateRect))
		return;

	rgb_color base = ui_color(B_PANEL_BACKGROUND_COLOR);
	uint32 flags = 0;
	if (!IsEnabled())
		flags |= BControlLook::B_DISABLED;

	if (fTextView->IsFocus() && Window()->IsActive())
		flags |= BControlLook::B_FOCUSED;

	be_control_look->DrawTextControlBorder(this, rect, updateRect, base,
		flags);
}