void
BackupListItem::DrawItem(BView* owner, BRect /*bounds*/, bool complete)
{
	BListView* list = dynamic_cast<BListView*>(owner);

	if (list == NULL)
		return;

	owner->PushState();

	BRect bounds = list->ItemFrame(list->IndexOf(this));

	rgb_color textColor = ui_color(B_LIST_ITEM_TEXT_COLOR);
	rgb_color backgroundColor = ui_color(B_LIST_BACKGROUND_COLOR);

	if (fIndex % 2)
		backgroundColor = (rgb_color){ 247, 247, 247, 255 };

	// draw background
	list->SetDrawingMode(B_OP_OVER);
	list->SetHighColor(backgroundColor);
	list->FillRect(bounds);

	// set proper colors for "normal" items
	list->SetHighColor(textColor);
	list->SetLowColor(backgroundColor);

	// Set up points for things in BListItem
	BPoint checkboxPt = bounds.LeftTop();
	BPoint namePt = bounds.LeftTop();
	BPoint descriptionPt = bounds.LeftTop();
	BPoint sizePt = bounds.RightTop();
	namePt += BPoint(16 + 8, fFirstlineOffset);
	sizePt += BPoint(0, fFirstlineOffset);
	descriptionPt += BPoint(16 + 8, fSecondlineOffset);
	checkboxPt += BPoint(4, 2);

	list->SetFont(be_bold_font);
	list->DrawString(fName.String(), namePt);

	char sizeText[512];
	size_to_string(fSize, sizeText, 512);
	BString sizeString(sizeText);

	list->SetFont(be_plain_font);
	sizePt -= BPoint(
		be_plain_font->StringWidth(sizeString.String()) + 4.0f, 0);

	list->DrawString(sizeString.String(), sizePt);

	if (textColor.red + textColor.green + textColor.blue > 128 * 3)
		list->SetHighColor(tint_color(textColor, B_DARKEN_1_TINT));
	else
		list->SetHighColor(tint_color(textColor, B_LIGHTEN_1_TINT));

	list->SetFontSize(11);
	list->SetHighColor(ui_color(B_LIST_SELECTED_ITEM_TEXT_COLOR));
	list->DrawString(fDescription.String(), descriptionPt);

	if (!fEnabled) {
		fEnabled = new BCheckBox(BRect(0, 0, 16, 16), fName.String(),
			fName.String(), new BMessage(kMsgUpdateSelection));
		list->AddChild(fEnabled);
		// First run, set default value
		fEnabled->SetValue(gLocationMap[fIndex].defaultValue
			? B_CONTROL_ON : B_CONTROL_OFF);
	}

	fEnabled->SetHighColor(textColor);
	fEnabled->SetLowColor(backgroundColor);
	fEnabled->MoveTo(checkboxPt.x, checkboxPt.y);

	owner->PopState();
}