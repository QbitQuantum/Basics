bool
ScreenWindow::QuitRequested()
{
	fSettings->SetWindowFrame(Frame());

	// Write mode of workspace 0 (the boot workspace) to the vesa settings file
	screen_mode vesaMode;
	if (fBootWorkspaceApplied && fScreenMode.Get(vesaMode, 0) == B_OK) {
		status_t status = _WriteVesaModeFile(vesaMode);
		if (status < B_OK) {
			BString warning = B_TRANSLATE("Could not write VESA mode settings"
				" file:\n\t");
			warning << strerror(status);
			BAlert* alert = new BAlert(B_TRANSLATE("Warning"),
				warning.String(), B_TRANSLATE("OK"), NULL,
				NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT);
			alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
			alert->Go();
		}
	}

	be_app->PostMessage(B_QUIT_REQUESTED);

	return BWindow::QuitRequested();
}