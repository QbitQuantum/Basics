AntialiasingSettingsView::AntialiasingSettingsView(const char* name)
	: BView(name, 0)
{
	// collect the current system settings
	if (get_subpixel_antialiasing(&fCurrentSubpixelAntialiasing) != B_OK)
		fCurrentSubpixelAntialiasing = false;
	fSavedSubpixelAntialiasing = fCurrentSubpixelAntialiasing;

	if (get_hinting_mode(&fCurrentHinting) != B_OK)
		fCurrentHinting = HINTING_MODE_ON;
	fSavedHinting = fCurrentHinting;

	if (get_average_weight(&fCurrentAverageWeight) != B_OK)
		fCurrentAverageWeight = 100;
	fSavedAverageWeight = fCurrentAverageWeight;

	// create the controls

	// antialiasing menu
	_BuildAntialiasingMenu();
	fAntialiasingMenuField = new BMenuField("antialiasing",
		B_TRANSLATE("Antialiasing type:"), fAntialiasingMenu, NULL);

	// "average weight" in subpixel filtering
	fAverageWeightControl = new BSlider("averageWeightControl",
		B_TRANSLATE("Reduce colored edges filter strength:"),
		new BMessage(kMsgSetAverageWeight), 0, 255, B_HORIZONTAL);
	fAverageWeightControl->SetLimitLabels(B_TRANSLATE("Off"),
		B_TRANSLATE("Strong"));
	fAverageWeightControl->SetHashMarks(B_HASH_MARKS_BOTTOM);
	fAverageWeightControl->SetHashMarkCount(255 / 15);
	fAverageWeightControl->SetEnabled(false);

	// hinting menu
	_BuildHintingMenu();
	fHintingMenuField = new BMenuField("hinting", B_TRANSLATE("Glyph hinting:"),
		fHintingMenu, NULL);

#ifdef DISABLE_HINTING_CONTROL
	fHintingMenuField->SetEnabled(false);
#endif

#ifndef FT_CONFIG_OPTION_SUBPIXEL_RENDERING
	// subpixelAntialiasingDisabledLabel
	BFont infoFont(*be_plain_font);
	infoFont.SetFace(B_ITALIC_FACE);
	rgb_color infoColor = tint_color(ui_color(B_PANEL_BACKGROUND_COLOR),
		B_DARKEN_4_TINT);
	// TODO: Replace with layout friendly constructor once available.
	BRect textBounds = Bounds();
	BTextView* subpixelAntialiasingDisabledLabel = new BTextView(
		textBounds, "unavailable label", textBounds, &infoFont, &infoColor,
		B_FOLLOW_NONE, B_WILL_DRAW | B_SUPPORTS_LAYOUT);
	subpixelAntialiasingDisabledLabel->SetText(B_TRANSLATE(
		"Subpixel based anti-aliasing in combination with glyph hinting is not "
		"available in this build of Haiku to avoid possible patent issues. To "
		"enable this feature, you have to build Haiku yourself and enable "
		"certain options in the libfreetype configuration header."));
	subpixelAntialiasingDisabledLabel->SetViewColor(
		ui_color(B_PANEL_BACKGROUND_COLOR));
	subpixelAntialiasingDisabledLabel->MakeEditable(false);
	subpixelAntialiasingDisabledLabel->MakeSelectable(false);
#endif // !FT_CONFIG_OPTION_SUBPIXEL_RENDERING

	SetLayout(new BGroupLayout(B_VERTICAL));

	// controls pane
	AddChild(BGridLayoutBuilder(10, 10)
		.Add(fHintingMenuField->CreateLabelLayoutItem(), 0, 0)
		.Add(fHintingMenuField->CreateMenuBarLayoutItem(), 1, 0)

		.Add(fAntialiasingMenuField->CreateLabelLayoutItem(), 0, 1)
		.Add(fAntialiasingMenuField->CreateMenuBarLayoutItem(), 1, 1)

		.Add(fAverageWeightControl, 0, 2, 2)

#ifndef FT_CONFIG_OPTION_SUBPIXEL_RENDERING
		// hinting+subpixel unavailable info
		.Add(subpixelAntialiasingDisabledLabel, 0, 3, 2)
#else
		.Add(BSpaceLayoutItem::CreateGlue(), 0, 3, 2)
#endif

		.SetInsets(10, 10, 10, 10)
	);

	_SetCurrentAntialiasing();
	_SetCurrentHinting();
	_SetCurrentAverageWeight();
}