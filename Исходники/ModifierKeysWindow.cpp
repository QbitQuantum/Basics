ModifierKeysWindow::ModifierKeysWindow()
	:
	BWindow(BRect(0, 0, 360, 220), B_TRANSLATE("Modifier keys"),
		B_FLOATING_WINDOW, B_NOT_RESIZABLE | B_NOT_ZOOMABLE
			| B_AUTO_UPDATE_SIZE_LIMITS)
{
	get_key_map(&fCurrentMap, &fCurrentBuffer);
	get_key_map(&fSavedMap, &fSavedBuffer);

	BStringView* keyRole = new BStringView("key role",
		B_TRANSLATE_COMMENT("Role", "As in the role of a modifier key"));
	keyRole->SetAlignment(B_ALIGN_RIGHT);
	keyRole->SetFont(be_bold_font);

	BStringView* keyLabel = new BStringView("key label",
		B_TRANSLATE_COMMENT("Key", "As in a computer keyboard key"));
	keyLabel->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, B_SIZE_UNSET));
	keyLabel->SetFont(be_bold_font);

	BMenuField* shiftMenuField = _CreateShiftMenuField();
	shiftMenuField->SetAlignment(B_ALIGN_RIGHT);

	BMenuField* controlMenuField = _CreateControlMenuField();
	controlMenuField->SetAlignment(B_ALIGN_RIGHT);

	BMenuField* optionMenuField = _CreateOptionMenuField();
	optionMenuField->SetAlignment(B_ALIGN_RIGHT);

	BMenuField* commandMenuField = _CreateCommandMenuField();
	commandMenuField->SetAlignment(B_ALIGN_RIGHT);

	fShiftConflictView = new ConflictView("shift warning view");
	fShiftConflictView->SetExplicitMaxSize(BSize(15, 15));

	fControlConflictView = new ConflictView("control warning view");
	fControlConflictView->SetExplicitMaxSize(BSize(15, 15));

	fOptionConflictView = new ConflictView("option warning view");
	fOptionConflictView->SetExplicitMaxSize(BSize(15, 15));

	fCommandConflictView = new ConflictView("command warning view");
	fCommandConflictView->SetExplicitMaxSize(BSize(15, 15));

	fCancelButton = new BButton("cancelButton", B_TRANSLATE("Cancel"),
		new BMessage(B_QUIT_REQUESTED));

	fRevertButton = new BButton("revertButton", B_TRANSLATE("Revert"),
		new BMessage(kMsgRevertModifiers));
	fRevertButton->SetEnabled(false);

	fOkButton = new BButton("okButton", B_TRANSLATE("Set modifier keys"),
		new BMessage(kMsgApplyModifiers));
	fOkButton->MakeDefault(true);

	// Build the layout
	SetLayout(new BGroupLayout(B_VERTICAL));

	float forcedMinWidth = be_plain_font->StringWidth("XXX") * 4;
	keyRole->SetExplicitMinSize(BSize(forcedMinWidth, B_SIZE_UNSET));

	BLayoutItem* shiftLabel = shiftMenuField->CreateLabelLayoutItem();
	shiftLabel->SetExplicitMinSize(BSize(forcedMinWidth, B_SIZE_UNSET));
	BLayoutItem* controlLabel = controlMenuField->CreateLabelLayoutItem();
	controlLabel->SetExplicitMinSize(BSize(forcedMinWidth, B_SIZE_UNSET));
	BLayoutItem* optionLabel = optionMenuField->CreateLabelLayoutItem();
	optionLabel->SetExplicitMinSize(BSize(forcedMinWidth, B_SIZE_UNSET));
	BLayoutItem* commandLabel = commandMenuField->CreateLabelLayoutItem();
	commandLabel->SetExplicitMinSize(BSize(forcedMinWidth, B_SIZE_UNSET));

	AddChild(BLayoutBuilder::Group<>(B_VERTICAL, B_USE_SMALL_SPACING)
		.AddGroup(B_HORIZONTAL)
			.Add(keyRole)
			.Add(keyLabel)
			.End()
		.AddGroup(B_HORIZONTAL)
			.Add(shiftLabel)
			.Add(shiftMenuField->CreateMenuBarLayoutItem())
			.Add(fShiftConflictView)
			.End()
		.AddGroup(B_HORIZONTAL)
			.Add(controlLabel)
			.Add(controlMenuField->CreateMenuBarLayoutItem())
			.Add(fControlConflictView)
			.End()
		.AddGroup(B_HORIZONTAL)
			.Add(optionLabel)
			.Add(optionMenuField->CreateMenuBarLayoutItem())
			.Add(fOptionConflictView)
			.End()
		.AddGroup(B_HORIZONTAL)
			.Add(commandLabel)
			.Add(commandMenuField->CreateMenuBarLayoutItem())
			.Add(fCommandConflictView)
			.End()
		.AddGlue()
		.AddGroup(B_HORIZONTAL)
			.Add(fCancelButton)
			.AddGlue()
			.Add(fRevertButton)
			.Add(fOkButton)
			.End()
		.SetInsets(B_USE_DEFAULT_SPACING)
	);

	_MarkMenuItems();
	_ValidateDuplicateKeys();

	PostMessage(kMsgHideShowIcons);
}