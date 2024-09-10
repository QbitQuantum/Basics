void
PackageView::AttachedToWindow()
{
	status_t ret = fInfo.InitCheck();
	if (ret != B_OK && ret != B_NO_INIT) {
		BAlert* warning = new BAlert("parsing_failed",
				B_TRANSLATE("The package file is not readable.\nOne of the "
				"possible reasons for this might be that the requested file "
				"is not a valid BeOS .pkg package."), B_TRANSLATE("OK"),
				NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT);
		warning->SetFlags(warning->Flags() | B_CLOSE_ON_ESCAPE);
		warning->Go();

		Window()->PostMessage(B_QUIT_REQUESTED);
		return;
	}

	// Set the window title
	BWindow* parent = Window();
	BString title;
	BString name = fInfo.GetName();
	if (name.CountChars() == 0) {
		title = B_TRANSLATE("Package installer");
	} else {
		title = B_TRANSLATE("Install %name%");
		title.ReplaceAll("%name%", name);
	}
	parent->SetTitle(title.String());
	fBeginButton->SetTarget(this);

	fOpenPanel->SetTarget(BMessenger(this));
	fInstallTypes->SetTargetForItems(this);

	if (ret != B_OK)
		return;

	// If the package is valid, we can set up the default group and all
	// other things. If not, then the application will close just after
	// attaching the view to the window
	_InstallTypeChanged(0);

	fStatusWindow = new PackageStatus(B_TRANSLATE("Installation progress"),
		NULL, NULL, this);

	// Show the splash screen, if present
	BMallocIO* image = fInfo.GetSplashScreen();
	if (image != NULL) {
		PackageImageViewer* imageViewer = new PackageImageViewer(image);
		imageViewer->Go();
	}

	// Show the disclaimer/info text popup, if present
	BString disclaimer = fInfo.GetDisclaimer();
	if (disclaimer.Length() != 0) {
		PackageTextViewer* text = new PackageTextViewer(
			disclaimer.String());
		int32 selection = text->Go();
		// The user didn't accept our disclaimer, this means we cannot
		// continue.
		if (selection == 0)
			parent->Quit();
	}
}