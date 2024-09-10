void
PoorManWindow::DefaultSettings()
{
	BAlert* serverAlert = new BAlert(B_TRANSLATE("Error Server"),
		STR_ERR_CANT_START, B_TRANSLATE("OK"));
	serverAlert->SetFlags(serverAlert->Flags() | B_CLOSE_ON_ESCAPE);
	BAlert* dirAlert = new BAlert(B_TRANSLATE("Error Dir"),
		STR_ERR_WEB_DIR, B_TRANSLATE("Cancel"), B_TRANSLATE("Select"),
		B_TRANSLATE("Create public_html"), B_WIDTH_AS_USUAL, B_OFFSET_SPACING);
	dirAlert->SetShortcut(0, B_ESCAPE);
	int32 buttonIndex = dirAlert->Go();

	switch (buttonIndex) {
		case 0:
			if (Lock())
				Quit();
			be_app_messenger.SendMessage(B_QUIT_REQUESTED);
			break;

		case 1:
			fPrefWindow = new PoorManPreferencesWindow(
					fSetwindowFrame,
					STR_WIN_NAME_PREF);
			fPrefWindow->ShowWebDirFilePanel();
			break;

		case 2:
			if (create_directory(STR_DEFAULT_WEB_DIRECTORY, 0755) != B_OK) {
				serverAlert->Go();
				if (Lock())
					Quit();
				be_app_messenger.SendMessage(B_QUIT_REQUESTED);
				break;
			}
			BAlert* dirCreatedAlert =
				new BAlert(B_TRANSLATE("Dir Created"), STR_DIR_CREATED, 
					B_TRANSLATE("OK"));
			dirCreatedAlert->SetFlags(dirCreatedAlert->Flags() | B_CLOSE_ON_ESCAPE);
			dirCreatedAlert->Go();
			SetWebDir(STR_DEFAULT_WEB_DIRECTORY);	
			be_app->PostMessage(kStartServer);
			break;
	}
}