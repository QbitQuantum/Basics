void
TabDecorator::_UpdateFont(DesktopSettings& settings)
{
	ServerFont font;
	if (fTopTab->look == B_FLOATING_WINDOW_LOOK
		|| fTopTab->look == kLeftTitledWindowLook) {
		settings.GetDefaultPlainFont(font);
		if (fTopTab->look == kLeftTitledWindowLook)
			font.SetRotation(90.0f);
	} else
		settings.GetDefaultBoldFont(font);

	font.SetFlags(B_FORCE_ANTIALIASING);
	font.SetSpacing(B_STRING_SPACING);
	fDrawState.SetFont(font);
}