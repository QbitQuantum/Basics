void
InterfaceListItem::DrawItem(BView* owner, BRect /*bounds*/, bool complete)
{
	BListView* list = dynamic_cast<BListView*>(owner);

	if (list == NULL)
		return;

	owner->PushState();

	BRect bounds = list->ItemFrame(list->IndexOf(this));

	//rgb_color highColor = list->HighColor();
	rgb_color lowColor = list->LowColor();

	if (IsSelected() || complete) {
		if (IsSelected()) {
			list->SetHighColor(ui_color(B_LIST_SELECTED_BACKGROUND_COLOR));
			list->SetLowColor(list->HighColor());
		} else
			list->SetHighColor(lowColor);

		list->FillRect(bounds);
	}

	BString interfaceState;
	BBitmap* stateIcon(NULL);

	if (fSettings->IsDisabled()) {
		interfaceState << "disabled";
		stateIcon = fIconOffline;
	} else if (!fInterface.HasLink()) {
		interfaceState << "no link";
		stateIcon = fIconOffline;
	} else if ((fSettings->IPAddr(AF_INET).IsEmpty()
		&& fSettings->IPAddr(AF_INET6).IsEmpty())
		&& (fSettings->AutoConfigure(AF_INET)
		|| fSettings->AutoConfigure(AF_INET6))) {
		interfaceState << "connecting" B_UTF8_ELLIPSIS;
		stateIcon = fIconPending;
	} else {
		interfaceState << "connected";
		stateIcon = fIconOnline;
	}

	// Set the initial bounds of item contents
	BPoint iconPt = bounds.LeftTop();
	BPoint namePt = bounds.LeftTop();
	BPoint line2Pt = bounds.LeftTop();
	BPoint line3Pt = bounds.LeftTop();
	BPoint statePt = bounds.RightTop();

	iconPt += BPoint(4, 4);
	statePt += BPoint(0, fFirstlineOffset);
	namePt += BPoint(ICON_SIZE + 12, fFirstlineOffset);
	line2Pt += BPoint(ICON_SIZE + 12, fSecondlineOffset);
	line3Pt += BPoint(ICON_SIZE + 12, fThirdlineOffset);

	statePt -= BPoint(
		be_plain_font->StringWidth(interfaceState.String()) + 4.0f, 0);

	if (fSettings->IsDisabled()) {
		list->SetDrawingMode(B_OP_ALPHA);
		list->SetBlendingMode(B_CONSTANT_ALPHA, B_ALPHA_OVERLAY);
		list->SetHighColor(0, 0, 0, 32);
	} else
		list->SetDrawingMode(B_OP_OVER);

	list->DrawBitmapAsync(fIcon, iconPt);
	list->DrawBitmapAsync(stateIcon, iconPt);

	if (fSettings->IsDisabled()) {
		rgb_color textColor;
		if (IsSelected())
			textColor = ui_color(B_LIST_SELECTED_ITEM_TEXT_COLOR);
		else
			textColor = ui_color(B_LIST_ITEM_TEXT_COLOR);

		if (textColor.red + textColor.green + textColor.blue > 128 * 3)
			list->SetHighColor(tint_color(textColor, B_DARKEN_1_TINT));
		else
			list->SetHighColor(tint_color(textColor, B_LIGHTEN_1_TINT));
	} else {
		if (IsSelected())
			list->SetHighColor(ui_color(B_LIST_SELECTED_ITEM_TEXT_COLOR));
		else
			list->SetHighColor(ui_color(B_LIST_ITEM_TEXT_COLOR));
	}

	list->SetFont(be_bold_font);
	list->DrawString(Name(), namePt);
	list->SetFont(be_plain_font);
	list->DrawString(interfaceState, statePt);
	
	if (!fSettings->IsDisabled()) {
		// Render IPv4 Address
		BString ipv4Str(B_TRANSLATE_COMMENT("IP:", "IPv4 address label"));
		if (fSettings->IPAddr(AF_INET).IsEmpty())
			ipv4Str << " " << B_TRANSLATE("None");
		else
			ipv4Str << " " << BString(fSettings->IP(AF_INET));

		list->DrawString(ipv4Str, line2Pt);
	}
	
	// Render IPv6 Address (if present)
	if (!fSettings->IsDisabled()
		&& !fSettings->IPAddr(AF_INET6).IsEmpty()) {
		BString ipv6Str(B_TRANSLATE_COMMENT("IPv6:", "IPv6 address label"));
		ipv6Str << " " << BString(fSettings->IP(AF_INET6));

		list->DrawString(ipv6Str, line3Pt);
	}

	owner->PopState();
}