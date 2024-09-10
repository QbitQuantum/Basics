PAccountDialog::PAccountDialog(const char *title, const char *protocol,
                               const char *account, BMessage settingsTemplate,
                               BMessage settings, BMessenger *target,
                               BMessage save, BMessage cancel)
	: BWindow(WINDOW_RECT, title, B_TITLED_WINDOW,
		B_NOT_ZOOMABLE | B_NOT_RESIZABLE | B_ASYNCHRONOUS_CONTROLS |
                B_AUTO_UPDATE_SIZE_LIMITS | B_CLOSE_ON_ESCAPE),
	fOriginalAccount(account),
	fTemplate(settingsTemplate),
	fSettings(settings),
	fTarget(target),
	fSave(save),
	fCancel(cancel)
{
	BRect frame(0, 0, 1, 1);
#ifndef __HAIKU__
	frame = Bounds();
#endif

	BView *view = ViewFactory::Create<BView>(frame, "top", B_FOLLOW_ALL_SIDES,
		B_WILL_DRAW | B_FRAME_EVENTS);

	// Account name
	fAccountName = ViewFactory::Create<BTextControl>(frame, "account_name", _T("Account name:"),
		fOriginalAccount.String(), NULL, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FRAME_EVENTS);
	fAccountName->SetFont(be_bold_font);
	fAccountName->MakeFocus();

	// Account name divider
	fAccountNameDivider = new Divider(frame, "AccountNameDivider", B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FRAME_EVENTS);
	fAccountNameDivider->ResizeToPreferred();

	fProtocolControl = new PClientView(frame, "ProtocolControls", NULL, fTemplate, fSettings);

	fCancelButton = ViewFactory::Create<BButton>(frame, "cancel", _T("Cancel"), new BMessage(kAddAccountCancel));
	fOKButton = ViewFactory::Create<BButton>(frame, "ok", _T("OK"), new BMessage(kAddAccountOk));

#ifdef __HAIKU__
	float inset = ceilf(be_plain_font->Size() * 0.7f);

	fAccountNameDivider->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, 1));
	//fProtocolControl->SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, B_SIZE_UNLIMITED));

	view->SetLayout(new BGroupLayout(B_VERTICAL));
	view->AddChild(BGroupLayoutBuilder(B_VERTICAL, inset)
		.AddGroup(B_VERTICAL, inset)
			.Add(fAccountName)
			.Add(fAccountNameDivider)
			.Add(fProtocolControl)
		.End()
		.SetInsets(inset, inset, inset, inset)
	);
	view->AddChild(BGroupLayoutBuilder(B_VERTICAL, inset)
		.AddGroup(B_HORIZONTAL, inset)
			.AddGlue()
			.Add(fCancelButton)
			.Add(fOKButton)
		.End()
		.SetInsets(inset, inset, inset, inset)
	);

	SetLayout(new BGroupLayout(B_HORIZONTAL));
	GetLayout()->AddView(view);
#else
	view->AddChild(fAccountName);
	view->AddChild(fAccountNameDivider);
	
	view->AddChild(fProtocolControl);
	
	view->AddChild(fCancelButton);
	view->AddChild(fOKButton);
	AddChild(view);
	
	LayoutGUI();
#endif

	CenterWindowOnScreen(this);
};