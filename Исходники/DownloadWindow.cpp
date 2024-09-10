DownloadWindow::DownloadWindow(BRect frame, bool visible,
		SettingsMessage* settings)
	: BWindow(frame, B_TRANSLATE("Downloads"),
		B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
		B_AUTO_UPDATE_SIZE_LIMITS | B_ASYNCHRONOUS_CONTROLS | B_NOT_ZOOMABLE),
	fMinimizeOnClose(false)
{
	SetPulseRate(1000000);

	settings->AddListener(BMessenger(this));
	BPath downloadPath;
	if (find_directory(B_DESKTOP_DIRECTORY, &downloadPath) != B_OK)
		downloadPath.SetTo("/boot/home/Desktop");
	fDownloadPath = settings->GetValue(kSettingsKeyDownloadPath,
		downloadPath.Path());
	settings->SetValue(kSettingsKeyDownloadPath, fDownloadPath);

	SetLayout(new BGroupLayout(B_VERTICAL, 0.0));

	DownloadsContainerView* downloadsGroupView = new DownloadsContainerView();
	fDownloadViewsLayout = downloadsGroupView->GroupLayout();

	BMenuBar* menuBar = new BMenuBar("Menu bar");
	BMenu* menu = new BMenu(B_TRANSLATE("Downloads"));
	menu->AddItem(new BMenuItem(B_TRANSLATE("Open downloads folder"),
		new BMessage(OPEN_DOWNLOADS_FOLDER)));
	BMessage* newWindowMessage = new BMessage(NEW_WINDOW);
	newWindowMessage->AddString("url", "");
	BMenuItem* newWindowItem = new BMenuItem(B_TRANSLATE("New browser window"),
		newWindowMessage, 'N');
	menu->AddItem(newWindowItem);
	newWindowItem->SetTarget(be_app);
	menu->AddSeparatorItem();
	menu->AddItem(new BMenuItem(B_TRANSLATE("Hide"),
		new BMessage(B_QUIT_REQUESTED), 'D'));
	menuBar->AddItem(menu);

	fDownloadsScrollView = new DownloadContainerScrollView(downloadsGroupView);

	fRemoveFinishedButton = new BButton(B_TRANSLATE("Remove finished"),
		new BMessage(REMOVE_FINISHED_DOWNLOADS));
	fRemoveFinishedButton->SetEnabled(false);

	fRemoveMissingButton = new BButton(B_TRANSLATE("Remove missing"),
		new BMessage(REMOVE_MISSING_DOWNLOADS));
	fRemoveMissingButton->SetEnabled(false);

	const float spacing = be_control_look->DefaultItemSpacing();

	AddChild(BGroupLayoutBuilder(B_VERTICAL, 0.0)
		.Add(menuBar)
		.Add(fDownloadsScrollView)
		.Add(new BSeparatorView(B_HORIZONTAL, B_PLAIN_BORDER))
		.Add(BGroupLayoutBuilder(B_HORIZONTAL, spacing)
			.AddGlue()
			.Add(fRemoveMissingButton)
			.Add(fRemoveFinishedButton)
			.SetInsets(12, 5, 12, 5)
		)
	);

	PostMessage(INIT);

	if (!visible)
		Hide();
	Show();
}