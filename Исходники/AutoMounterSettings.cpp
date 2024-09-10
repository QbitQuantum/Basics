AutomountSettingsPanel::AutomountSettingsPanel(BMessage* settings,
		const BMessenger& target)
	:
	BBox("", B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE_JUMP, B_NO_BORDER),
	fTarget(target)
{
	const float spacing = be_control_look->DefaultItemSpacing();

	// "Automatic Disk Mounting" group

	BBox* autoMountBox = new BBox("autoMountBox", B_WILL_DRAW | B_FRAME_EVENTS
		| B_PULSE_NEEDED | B_NAVIGABLE_JUMP);
	autoMountBox->SetLabel(B_TRANSLATE("Automatic disk mounting"));
	BGroupLayout* autoMountLayout = new BGroupLayout(B_VERTICAL, 0);
	autoMountBox->SetLayout(autoMountLayout);
	autoMountLayout->SetInsets(spacing,
		autoMountBox->InnerFrame().top + spacing / 2, spacing, spacing);

	fScanningDisabledCheck = new BRadioButton("scanningOff",
		B_TRANSLATE("Don't automount"),
		new BMessage(kAutomountSettingsChanged));

	fAutoMountAllBFSCheck = new BRadioButton("autoBFS",
		B_TRANSLATE("All BeOS disks"), new BMessage(kAutomountSettingsChanged));

	fAutoMountAllCheck = new BRadioButton("autoAll",
		B_TRANSLATE("All disks"), new BMessage(kAutomountSettingsChanged));

	// "Disk Mounting During Boot" group

	BBox* bootMountBox = new BBox("", B_WILL_DRAW | B_FRAME_EVENTS
		| B_PULSE_NEEDED | B_NAVIGABLE_JUMP);
	bootMountBox->SetLabel(B_TRANSLATE("Disk mounting during boot"));
	BGroupLayout* bootMountLayout = new BGroupLayout(B_VERTICAL, 0);
	bootMountBox->SetLayout(bootMountLayout);
	bootMountLayout->SetInsets(spacing,
		bootMountBox->InnerFrame().top + spacing / 2, spacing, spacing);

	fInitialDontMountCheck = new BRadioButton("initialNone",
		B_TRANSLATE("Only the boot disk"),
		new BMessage(kBootMountSettingsChanged));

	fInitialMountRestoreCheck = new BRadioButton("initialRestore",
		B_TRANSLATE("Previously mounted disks"),
		new BMessage(kBootMountSettingsChanged));

	fInitialMountAllBFSCheck = new BRadioButton("initialBFS",
		B_TRANSLATE("All BeOS disks"),
		new BMessage(kBootMountSettingsChanged));

	fInitialMountAllCheck = new BRadioButton("initialAll",
		B_TRANSLATE("All disks"), new BMessage(kBootMountSettingsChanged));

	fEjectWhenUnmountingCheckBox = new BCheckBox("ejectWhenUnmounting",
		B_TRANSLATE("Eject when unmounting"),
		new BMessage(kEjectWhenUnmountingChanged));

	// Buttons

	fDone = new BButton(B_TRANSLATE("Done"), new BMessage(B_QUIT_REQUESTED));

	fMountAllNow = new BButton("mountAll", B_TRANSLATE("Mount all disks now"),
		new BMessage(kMountAllNow));

	fDone->MakeDefault(true);

	// Layout the controls
	BGroupView* contentView = new BGroupView(B_VERTICAL, 0);
	AddChild(contentView);
	BLayoutBuilder::Group<>(contentView)
		.AddGroup(B_VERTICAL, spacing)
			.SetInsets(spacing, spacing, spacing, spacing)
			.AddGroup(autoMountLayout)
				.Add(fScanningDisabledCheck)
				.Add(fAutoMountAllBFSCheck)
				.Add(fAutoMountAllCheck)
				.End()
			.AddGroup(bootMountLayout)
				.Add(fInitialDontMountCheck)
				.Add(fInitialMountRestoreCheck)
				.Add(fInitialMountAllBFSCheck)
				.Add(fInitialMountAllCheck)
				.End()
			.AddGroup(B_HORIZONTAL)
				.AddStrut(spacing - 1)
				.Add(fEjectWhenUnmountingCheckBox)
				.End()
			.End()
		.Add(new BSeparatorView(B_HORIZONTAL/*, B_FANCY_BORDER*/))
		.AddGroup(B_HORIZONTAL, spacing)
			.SetInsets(0, spacing, spacing, spacing)
			.AddGlue()
			.Add(fMountAllNow)
			.Add(fDone);

	// Apply the settings

	bool result;
	if (settings->FindBool("autoMountAll", &result) == B_OK && result)
		fAutoMountAllCheck->SetValue(B_CONTROL_ON);
	else if (settings->FindBool("autoMountAllBFS", &result) == B_OK && result)
		fAutoMountAllBFSCheck->SetValue(B_CONTROL_ON);
	else
		fScanningDisabledCheck->SetValue(B_CONTROL_ON);

	if (settings->FindBool("suspended", &result) == B_OK && result)
		fScanningDisabledCheck->SetValue(B_CONTROL_ON);

	if (settings->FindBool("initialMountAll", &result) == B_OK && result)
		fInitialMountAllCheck->SetValue(B_CONTROL_ON);
	else if (settings->FindBool("initialMountRestore", &result) == B_OK
		&& result) {
		fInitialMountRestoreCheck->SetValue(B_CONTROL_ON);
	} else if (settings->FindBool("initialMountAllBFS", &result) == B_OK
		&& result) {
		fInitialMountAllBFSCheck->SetValue(B_CONTROL_ON);
	} else
		fInitialDontMountCheck->SetValue(B_CONTROL_ON);

	if (settings->FindBool("ejectWhenUnmounting", &result) == B_OK && result)
		fEjectWhenUnmountingCheckBox->SetValue(B_CONTROL_ON);
}