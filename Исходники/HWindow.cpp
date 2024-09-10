void
HWindow::InitGUI()
{
	fEventList = new HEventList();
	fEventList->SetType(BMediaFiles::B_SOUNDS);
	fEventList->SetSelectionMode(B_SINGLE_SELECTION_LIST);

	BGroupView* view = new BGroupView();
	BBox* box = new BBox("", B_WILL_DRAW | B_FRAME_EVENTS
		| B_NAVIGABLE_JUMP | B_PULSE_NEEDED);

	BMenu* menu = new BMenu("file");
	menu->SetRadioMode(true);
	menu->SetLabelFromMarked(true);
	menu->AddSeparatorItem();
	menu->AddItem(new BMenuItem(B_TRANSLATE("<none>"),
		new BMessage(M_NONE_MESSAGE)));
	menu->AddItem(new BMenuItem(B_TRANSLATE("Other" B_UTF8_ELLIPSIS),
		new BMessage(M_OTHER_MESSAGE)));

	BString label(B_TRANSLATE("Sound file:"));
	BMenuField* menuField = new BMenuField("filemenu", label, menu);
	menuField->SetDivider(menuField->StringWidth(label) + 10);

	BButton* stopbutton = new BButton("stop", B_TRANSLATE("Stop"),
		new BMessage(M_STOP_MESSAGE));
	stopbutton->SetEnabled(false);

	BButton* playbutton = new BButton("play", B_TRANSLATE("Play"),
		new BMessage(M_PLAY_MESSAGE));
	playbutton->SetEnabled(false);

	const float kInset = be_control_look->DefaultItemSpacing();
	view->SetLayout(new BGroupLayout(B_HORIZONTAL));
	view->AddChild(BGroupLayoutBuilder(B_VERTICAL, kInset)
		.AddGroup(B_HORIZONTAL)
			.Add(menuField)
			.AddGlue()
		.End()
		.AddGroup(B_HORIZONTAL, kInset)
			.AddGlue()
			.Add(playbutton)
			.Add(stopbutton)
		.End()
		.SetInsets(kInset, kInset, kInset, kInset)
	);

	box->AddChild(view);

	SetLayout(new BGroupLayout(B_HORIZONTAL));
	AddChild(BGroupLayoutBuilder(B_VERTICAL)
		.AddGroup(B_VERTICAL, kInset)
			.Add(fEventList)
			.Add(box)
		.End()
		.SetInsets(kInset, kInset, kInset, kInset)
	);

	// setup file menu
	SetupMenuField();
	BMenuItem* noneItem = menu->FindItem(B_TRANSLATE("<none>"));
	if (noneItem != NULL)
		noneItem->SetMarked(true);
}