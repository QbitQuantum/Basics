KeymapWindow::KeymapWindow()
	:
	BWindow(BRect(80, 50, 880, 380), TR("Keymap"), B_TITLED_WINDOW,
		B_ASYNCHRONOUS_CONTROLS | B_AUTO_UPDATE_SIZE_LIMITS)
{
	SetLayout(new BGroupLayout(B_VERTICAL));

	fKeyboardLayoutView = new KeyboardLayoutView("layout");
	fKeyboardLayoutView->SetKeymap(&fCurrentMap);

	fTextControl = new BTextControl(TR("Sample and clipboard:"), "", NULL);

	fSwitchShortcutsButton = new BButton("switch", "",
		new BMessage(kMsgSwitchShortcuts));

	fRevertButton = new BButton("revertButton", TR("Revert"),
		new BMessage(kMsgRevertKeymap));

	// controls pane
	AddChild(BGroupLayoutBuilder(B_VERTICAL)
		.Add(_CreateMenu())
		.Add(BGroupLayoutBuilder(B_HORIZONTAL, 10)
			.Add(_CreateMapLists(), 0.25)
			.Add(BGroupLayoutBuilder(B_VERTICAL, 10)
				.Add(fKeyboardLayoutView)
				//.Add(new BStringView("text label", "Sample and clipboard:"))
				.Add(BGroupLayoutBuilder(B_HORIZONTAL, 10)
					.Add(_CreateDeadKeyMenuField(), 0.0)
					.AddGlue()
					.Add(fSwitchShortcutsButton))
				.Add(fTextControl)
				.AddGlue(0.0)
				.Add(BGroupLayoutBuilder(B_HORIZONTAL, 10)
					.AddGlue(0.0)
					.Add(fRevertButton)))
			.SetInsets(10, 10, 10, 10)));

	fKeyboardLayoutView->SetTarget(fTextControl->TextView());
	fTextControl->MakeFocus();

	// Make sure the user keymap directory exists
	BPath path;
	find_directory(B_USER_SETTINGS_DIRECTORY, &path);
	path.Append("Keymap");

	entry_ref ref;
	get_ref_for_path(path.Path(), &ref);

	BDirectory userKeymapsDir(&ref);
	if (userKeymapsDir.InitCheck() != B_OK)
		create_directory(path.Path(), S_IRWXU | S_IRWXG | S_IRWXO);

	BMessenger messenger(this);
	fOpenPanel = new BFilePanel(B_OPEN_PANEL, &messenger, &ref,
		B_FILE_NODE, false, NULL);
	fSavePanel = new BFilePanel(B_SAVE_PANEL, &messenger, &ref,
		B_FILE_NODE, false, NULL);

	BRect windowFrame;
	BString keyboardLayout;
	_LoadSettings(windowFrame, keyboardLayout);
	_SetKeyboardLayout(keyboardLayout.String());

	ResizeTo(windowFrame.Width(), windowFrame.Height());
	MoveTo(windowFrame.LeftTop());

	// TODO: this might be a bug in the interface kit, but scrolling to
	// selection does not correctly work unless the window is shown.
	Show();
	Lock();

	// Try and find the current map name in the two list views (if the name
	// was read at all)
	_SelectCurrentMap();

	KeymapListItem* current
		= static_cast<KeymapListItem*>(fUserListView->FirstItem());

	fCurrentMap.Load(current->EntryRef());
	fPreviousMap = fCurrentMap;
	fAppliedMap = fCurrentMap;
	fCurrentMap.SetTarget(this, new BMessage(kMsgKeymapUpdated));

	_UpdateButtons();

	_UpdateDeadKeyMenu();
	_UpdateSwitchShortcutButton();

	Unlock();
}