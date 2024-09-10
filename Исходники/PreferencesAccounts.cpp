PreferencesAccounts::PreferencesAccounts()
	: BView("Accounts", B_WILL_DRAW)
{
	fListView = new BListView("accountsListView");
	fListView->SetInvocationMessage(new BMessage(kEditAccount));
	fListView->SetSelectionMessage(new BMessage(kSelect));

	BScrollView* scrollView = new BScrollView("scrollView", fListView,
		B_WILL_DRAW, false, true);

	ProtocolManager* pm = ProtocolManager::Get();

	fProtosMenu = new BPopUpMenu(NULL, true);
	for (uint32 i = 0; i < pm->CountProtocolAddOns(); i++) {
		CayaProtocolAddOn* addOn = pm->ProtocolAddOnAt(i);
		ProtocolSettings* settings = new ProtocolSettings(addOn);

		// Add accounts to list view
		_LoadListView(settings);

		// Add menu items
		BMessage* msg = new BMessage(kAddAccount);
		msg->AddPointer("settings", settings);

		BitmapMenuItem* item = new BitmapMenuItem(
			addOn->FriendlySignature(), msg, addOn->Icon());
		fProtosMenu->AddItem(item);
	}

	ToolButton* proto = new ToolButton("+", NULL);
	proto->SetMenu(fProtosMenu);
	fDelButton = new ToolButton("-", new BMessage(kDelAccount));
	fEditButton = new ToolButton("Edit...", new BMessage(kEditAccount));
	fDelButton->SetEnabled(false);
	fEditButton->SetEnabled(false);

	const float spacing = be_control_look->DefaultItemSpacing();

	SetLayout(new BGroupLayout(B_HORIZONTAL, spacing));
	AddChild(BGroupLayoutBuilder(B_VERTICAL)
		.Add(scrollView)
		.AddGroup(B_HORIZONTAL, spacing)
			.Add(proto)
			.Add(fDelButton)
			.AddGlue()
			.Add(fEditButton)
		.End()
		.SetInsets(spacing, spacing, spacing, spacing)
	);
}