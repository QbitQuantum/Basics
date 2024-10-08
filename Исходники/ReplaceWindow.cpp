ReplaceWindow::ReplaceWindow(BRect frame, BHandler* _handler,
	BString* searchString, 	BString *replaceString,
	bool caseState, bool wrapState, bool backState)
	: BWindow(frame, "ReplaceWindow", B_MODAL_WINDOW,
		B_NOT_RESIZABLE | B_ASYNCHRONOUS_CONTROLS | B_AUTO_UPDATE_SIZE_LIMITS,
		B_CURRENT_WORKSPACE)
{
	AddShortcut('W', B_COMMAND_KEY, new BMessage(B_QUIT_REQUESTED));

	fSearchString = new BTextControl("", B_TRANSLATE("Find:"), NULL, NULL);
	fReplaceString = new BTextControl("", B_TRANSLATE("Replace with:"),
		NULL, NULL);
	fCaseSensBox = new BCheckBox("", B_TRANSLATE("Case-sensitive"), NULL);
	fWrapBox = new BCheckBox("", B_TRANSLATE("Wrap-around search"), NULL);
	fBackSearchBox = new BCheckBox("", B_TRANSLATE("Search backwards"), NULL);
	fAllWindowsBox = new BCheckBox("", B_TRANSLATE("Replace in all windows"),
		new BMessage(CHANGE_WINDOW));
	fUIchange = false;

	fReplaceAllButton = new BButton("", B_TRANSLATE("Replace all"),
		new BMessage(MSG_REPLACE_ALL));
	fCancelButton = new BButton("", B_TRANSLATE("Cancel"),
		new BMessage(B_QUIT_REQUESTED));
	fReplaceButton = new BButton("", B_TRANSLATE("Replace"),
		new BMessage(MSG_REPLACE));

	SetLayout(new BGroupLayout(B_HORIZONTAL));
	AddChild(BGroupLayoutBuilder(B_VERTICAL, 4)
		.Add(BGridLayoutBuilder(6, 2)
				.Add(fSearchString->CreateLabelLayoutItem(), 0, 0)
				.Add(fSearchString->CreateTextViewLayoutItem(), 1, 0)
				.Add(fReplaceString->CreateLabelLayoutItem(), 0, 1)
				.Add(fReplaceString->CreateTextViewLayoutItem(), 1, 1)
				.Add(fCaseSensBox, 1, 2)
				.Add(fWrapBox, 1, 3)
				.Add(fBackSearchBox, 1, 4)
				.Add(fAllWindowsBox, 1, 5)
				)
		.AddGroup(B_HORIZONTAL, 10)
			.Add(fReplaceAllButton)
			.AddGlue()
			.Add(fCancelButton)
			.Add(fReplaceButton)
		.End()
		.SetInsets(10, 10, 10, 10)
	);

	fReplaceButton->MakeDefault(true);

	fHandler = _handler;

	const char* searchtext = searchString->String();
	const char* replacetext = replaceString->String();

	fSearchString->SetText(searchtext);
	fReplaceString->SetText(replacetext);
	fSearchString->MakeFocus(true);

	fCaseSensBox->SetValue(caseState ? B_CONTROL_ON : B_CONTROL_OFF);
	fWrapBox->SetValue(wrapState ? B_CONTROL_ON : B_CONTROL_OFF);
	fBackSearchBox->SetValue(backState ? B_CONTROL_ON : B_CONTROL_OFF);
}