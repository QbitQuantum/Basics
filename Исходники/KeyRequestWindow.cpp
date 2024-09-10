	KeyRequestView()
		:
		BView("KeyRequestView", B_WILL_DRAW),
		fPassword(NULL)
	{
		SetViewUIColor(B_PANEL_BACKGROUND_COLOR);

		BGroupLayout* rootLayout = new(std::nothrow) BGroupLayout(B_VERTICAL);
		if (rootLayout == NULL)
			return;

		SetLayout(rootLayout);

		BGridView* controls = new(std::nothrow) BGridView();
		if (controls == NULL)
			return;

		BGridLayout* layout = controls->GridLayout();

		float inset = ceilf(be_plain_font->Size() * 0.7);
		rootLayout->SetInsets(inset, inset, inset, inset);
		rootLayout->SetSpacing(inset);
		layout->SetSpacing(inset, inset);

		BStringView* label = new(std::nothrow) BStringView("keyringLabel",
			B_TRANSLATE("Keyring:"));
		if (label == NULL)
			return;

		int32 row = 0;
		layout->AddView(label, 0, row);

		fKeyringName = new(std::nothrow) BStringView("keyringName", "");
		if (fKeyringName == NULL)
			return;

		layout->AddView(fKeyringName, 1, row++);

		fPassword = new(std::nothrow) BTextControl(B_TRANSLATE("Password:"******"", NULL);
		if (fPassword == NULL)
			return;

		BLayoutItem* layoutItem = fPassword->CreateTextViewLayoutItem();
		layoutItem->SetExplicitMinSize(BSize(fPassword->StringWidth(
				"0123456789012345678901234567890123456789") + inset,
			B_SIZE_UNSET));

		layout->AddItem(fPassword->CreateLabelLayoutItem(), 0, row);
		layout->AddItem(layoutItem, 1, row++);

		BGroupView* buttons = new(std::nothrow) BGroupView(B_HORIZONTAL);
		if (buttons == NULL)
			return;

		fCancelButton = new(std::nothrow) BButton(B_TRANSLATE("Cancel"),
			new BMessage(kMessageCancel));
		buttons->GroupLayout()->AddView(fCancelButton);

		buttons->GroupLayout()->AddItem(BSpaceLayoutItem::CreateGlue());

		fUnlockButton = new(std::nothrow) BButton(B_TRANSLATE("Unlock"),
			new BMessage(kMessageUnlock));
		buttons->GroupLayout()->AddView(fUnlockButton);

		BTextView* message = new(std::nothrow) BTextView("message");
		message->SetText(B_TRANSLATE("An application wants to access the "
			"keyring below, but it is locked with a passphrase. Please enter "
			"the passphrase to unlock the keyring.\n"
			"If you unlock the keyring, it stays unlocked until the system is "
			"shut down or the keyring is manually locked again.\n"
			"If you cancel this dialog the keyring will remain locked."));
		message->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		message->SetFontAndColor(be_plain_font, B_FONT_ALL, &textColor);
		message->MakeEditable(false);
		message->MakeSelectable(false);
		message->SetWordWrap(true);

		rootLayout->AddView(message);
		rootLayout->AddView(controls);
		rootLayout->AddView(buttons);
	}