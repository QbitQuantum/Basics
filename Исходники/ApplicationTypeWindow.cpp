ApplicationTypeWindow::ApplicationTypeWindow(BPoint position,
	const BEntry& entry)
	:
	BWindow(BRect(0.0f, 0.0f, 250.0f, 340.0f).OffsetBySelf(position),
		B_TRANSLATE("Application type"), B_TITLED_WINDOW,
		B_NOT_ZOOMABLE | B_ASYNCHRONOUS_CONTROLS |
			B_FRAME_EVENTS | B_AUTO_UPDATE_SIZE_LIMITS),
	fChangedProperties(0)
{
	float padding = be_control_look->DefaultItemSpacing();
	BAlignment labelAlignment = be_control_look->DefaultLabelAlignment();

	BMenuBar* menuBar = new BMenuBar((char*)NULL);
	menuBar->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT, B_ALIGN_TOP));

	BMenu* menu = new BMenu(B_TRANSLATE("File"));
	fSaveMenuItem = new BMenuItem(B_TRANSLATE("Save"),
		new BMessage(kMsgSave), 'S');
	fSaveMenuItem->SetEnabled(false);
	menu->AddItem(fSaveMenuItem);
	BMenuItem* item;
	menu->AddItem(item = new BMenuItem(
		B_TRANSLATE("Save into resource file" B_UTF8_ELLIPSIS), NULL));
	item->SetEnabled(false);

	menu->AddSeparatorItem();
	menu->AddItem(new BMenuItem(B_TRANSLATE("Close"),
		new BMessage(B_QUIT_REQUESTED), 'W', B_COMMAND_KEY));
	menuBar->AddItem(menu);

	// Signature

	fSignatureControl = new BTextControl(B_TRANSLATE("Signature:"), NULL,
		new BMessage(kMsgSignatureChanged));
	fSignatureControl->SetModificationMessage(
		new BMessage(kMsgSignatureChanged));

	// filter out invalid characters that can't be part of a MIME type name
	BTextView* textView = fSignatureControl->TextView();
	textView->SetMaxBytes(B_MIME_TYPE_LENGTH);
	const char* disallowedCharacters = "<>@,;:\"()[]?=";
	for (int32 i = 0; disallowedCharacters[i]; i++) {
		textView->DisallowChar(disallowedCharacters[i]);
	}

	// "Application Flags" group

	BBox* flagsBox = new BBox("flagsBox");

	fFlagsCheckBox = new BCheckBox("flags", B_TRANSLATE("Application flags"),
		new BMessage(kMsgToggleAppFlags));
	fFlagsCheckBox->SetValue(B_CONTROL_ON);

	fSingleLaunchButton = new BRadioButton("single",
		B_TRANSLATE("Single launch"), new BMessage(kMsgAppFlagsChanged));

	fMultipleLaunchButton = new BRadioButton("multiple",
		B_TRANSLATE("Multiple launch"), new BMessage(kMsgAppFlagsChanged));

	fExclusiveLaunchButton = new BRadioButton("exclusive",
		B_TRANSLATE("Exclusive launch"), new BMessage(kMsgAppFlagsChanged));

	fArgsOnlyCheckBox = new BCheckBox("args only", B_TRANSLATE("Args only"),
		new BMessage(kMsgAppFlagsChanged));

	fBackgroundAppCheckBox = new BCheckBox("background",
		B_TRANSLATE("Background app"), new BMessage(kMsgAppFlagsChanged));

	flagsBox->AddChild(BGridLayoutBuilder()
		.Add(fSingleLaunchButton, 0, 0).Add(fArgsOnlyCheckBox, 1, 0)
		.Add(fMultipleLaunchButton, 0, 1).Add(fBackgroundAppCheckBox, 1, 1)
		.Add(fExclusiveLaunchButton, 0, 2)
		.SetInsets(padding, padding, padding, padding));
	flagsBox->SetLabel(fFlagsCheckBox);

	// "Icon" group

	BBox* iconBox = new BBox("IconBox");
	iconBox->SetLabel(B_TRANSLATE("Icon"));
	fIconView = new IconView("icon");
	fIconView->SetModificationMessage(new BMessage(kMsgIconChanged));
	iconBox->AddChild(BGroupLayoutBuilder(B_HORIZONTAL)
		.Add(fIconView)
		.SetInsets(padding, padding, padding, padding));

	// "Supported Types" group

	BBox* typeBox = new BBox("typesBox");
	typeBox->SetLabel(B_TRANSLATE("Supported types"));

	fTypeListView = new SupportedTypeListView("Suppported Types",
		B_SINGLE_SELECTION_LIST);
	fTypeListView->SetSelectionMessage(new BMessage(kMsgTypeSelected));

	BScrollView* scrollView = new BScrollView("type scrollview", fTypeListView,
		B_FRAME_EVENTS | B_WILL_DRAW, false, true);

	fAddTypeButton = new BButton("add type",
		B_TRANSLATE("Add" B_UTF8_ELLIPSIS), new BMessage(kMsgAddType));

	fRemoveTypeButton = new BButton("remove type", B_TRANSLATE("Remove"),
		new BMessage(kMsgRemoveType));

	fTypeIconView = new IconView("type icon");
	BView* iconHolder = BGroupLayoutBuilder(B_HORIZONTAL).Add(fTypeIconView);
	fTypeIconView->SetModificationMessage(new BMessage(kMsgTypeIconsChanged));

	typeBox->AddChild(BGridLayoutBuilder(padding, padding)
		.Add(scrollView, 0, 0, 1, 4)
		.Add(fAddTypeButton, 1, 0, 1, 2)
		.Add(fRemoveTypeButton, 1, 2, 1, 2)
		.Add(iconHolder, 2, 1, 1, 2)
		.SetInsets(padding, padding, padding, padding)
		.SetColumnWeight(0, 3)
		.SetColumnWeight(1, 2)
		.SetColumnWeight(2, 1));
	iconHolder->SetExplicitAlignment(
		BAlignment(B_ALIGN_CENTER, B_ALIGN_MIDDLE));

	// "Version Info" group

	BBox* versionBox = new BBox("versionBox");
	versionBox->SetLabel(B_TRANSLATE("Version info"));

	fMajorVersionControl = new BTextControl(B_TRANSLATE("Version:"),
		NULL, NULL);
	_MakeNumberTextControl(fMajorVersionControl);

	fMiddleVersionControl = new BTextControl(".", NULL, NULL);
	_MakeNumberTextControl(fMiddleVersionControl);

	fMinorVersionControl = new BTextControl(".", NULL, NULL);
	_MakeNumberTextControl(fMinorVersionControl);

	fVarietyMenu = new BPopUpMenu("variety", true, true);
	fVarietyMenu->AddItem(new BMenuItem(B_TRANSLATE("Development"), NULL));
	fVarietyMenu->AddItem(new BMenuItem(B_TRANSLATE("Alpha"), NULL));
	fVarietyMenu->AddItem(new BMenuItem(B_TRANSLATE("Beta"), NULL));
	fVarietyMenu->AddItem(new BMenuItem(B_TRANSLATE("Gamma"), NULL));
	item = new BMenuItem(B_TRANSLATE("Golden master"), NULL);
	fVarietyMenu->AddItem(item);
	item->SetMarked(true);
	fVarietyMenu->AddItem(new BMenuItem(B_TRANSLATE("Final"), NULL));

	BMenuField* varietyField = new BMenuField("", fVarietyMenu);
	fInternalVersionControl = new BTextControl("/", NULL, NULL);
	fShortDescriptionControl =
		new BTextControl(B_TRANSLATE("Short description:"), NULL, NULL);

	// TODO: workaround for a GCC 4.1.0 bug? Or is that really what the standard says?
	version_info versionInfo;
	fShortDescriptionControl->TextView()->SetMaxBytes(
		sizeof(versionInfo.short_info));

	BStringView* longLabel = new BStringView(NULL,
		B_TRANSLATE("Long description:"));
	longLabel->SetExplicitAlignment(labelAlignment);
	fLongDescriptionView = new TabFilteringTextView("long desc");
	fLongDescriptionView->SetMaxBytes(sizeof(versionInfo.long_info));

	scrollView = new BScrollView("desc scrollview", fLongDescriptionView,
		B_FRAME_EVENTS | B_WILL_DRAW, false, true);

	// TODO: remove workaround (bug #5678)
	BSize minScrollSize = scrollView->ScrollBar(B_VERTICAL)->MinSize();
	minScrollSize.width += fLongDescriptionView->MinSize().width;
	scrollView->SetExplicitMinSize(minScrollSize);

	versionBox->AddChild(BGridLayoutBuilder(padding / 2, padding)
		.Add(fMajorVersionControl->CreateLabelLayoutItem(), 0, 0)
		.Add(fMajorVersionControl->CreateTextViewLayoutItem(), 1, 0)
		.Add(fMiddleVersionControl, 2, 0, 2)
		.Add(fMinorVersionControl, 4, 0, 2)
		.Add(varietyField, 6, 0, 3)
		.Add(fInternalVersionControl, 9, 0, 2)
		.Add(fShortDescriptionControl->CreateLabelLayoutItem(), 0, 1)
		.Add(fShortDescriptionControl->CreateTextViewLayoutItem(), 1, 1, 10)
		.Add(longLabel, 0, 2)
		.Add(scrollView, 1, 2, 10, 3)
		.SetInsets(padding, padding, padding, padding)
		.SetRowWeight(3, 3));

	// put it all together
	SetLayout(new BGroupLayout(B_VERTICAL));
	AddChild(menuBar);
	AddChild(BGroupLayoutBuilder(B_VERTICAL, padding)
		.Add(fSignatureControl)
		.Add(BGroupLayoutBuilder(B_HORIZONTAL, padding)
			.Add(flagsBox, 3)
			.Add(iconBox, 1))
		.Add(typeBox)
		.Add(versionBox)
		.SetInsets(padding, padding, padding, padding));

	SetKeyMenuBar(menuBar);

	fSignatureControl->MakeFocus(true);
	BMimeType::StartWatching(this);
	_SetTo(entry);
}