void
CreateParamsPanel::_CreateViewControls(BPartition* parent, off_t offset,
	off_t size)
{
	// Setup the controls
	fSizeSlider = new SizeSlider("Slider", TR("Partition size"), NULL, offset,
		offset + size);
	fSizeSlider->SetPosition(1.0);

	fNameTextControl = new BTextControl("Name Control", TR("Partition name:"),
		"", NULL);
	if (!parent->SupportsChildName())
		fNameTextControl->SetEnabled(false);

	fTypePopUpMenu = new BPopUpMenu("Partition Type");

	int32 cookie = 0;
	BString supportedType;
	while (parent->GetNextSupportedChildType(&cookie, &supportedType)
			== B_OK) {
		BMessage* message = new BMessage(MSG_PARTITION_TYPE);
		message->AddString("type", supportedType);
		BMenuItem* item = new BMenuItem(supportedType, message);
		fTypePopUpMenu->AddItem(item);

		if (strcmp(supportedType, kPartitionTypeBFS) == 0)
			item->SetMarked(true);
	}

	fTypeMenuField = new BMenuField(TR("Partition type:"), fTypePopUpMenu,
		NULL);

	const float spacing = be_control_look->DefaultItemSpacing();
	BGroupLayout* layout = new BGroupLayout(B_VERTICAL, spacing);
	layout->SetInsets(spacing, spacing, spacing, spacing);

	SetLayout(layout);

	AddChild(BGroupLayoutBuilder(B_VERTICAL, spacing)
		.Add(fSizeSlider)
		.Add(BGridLayoutBuilder(0.0, 5.0)
			.Add(fNameTextControl->CreateLabelLayoutItem(), 0, 0)
			.Add(fNameTextControl->CreateTextViewLayoutItem(), 1, 0)
			.Add(fTypeMenuField->CreateLabelLayoutItem(), 0, 1)
			.Add(fTypeMenuField->CreateMenuBarLayoutItem(), 1, 1)
		)
	);

	parent->GetChildCreationParameterEditor(NULL, &fEditor);
	if (fEditor)
		AddChild(fEditor->View());

	BButton* okButton = new BButton(TR("Create"), new BMessage(MSG_OK));
	AddChild(BGroupLayoutBuilder(B_HORIZONTAL, spacing)
		.AddGlue()
		.Add(new BButton(TR("Cancel"), new BMessage(MSG_CANCEL)))
		.Add(okButton)
	);
	SetDefaultButton(okButton);

	AddToSubset(fWindow);
	layout->View()->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}