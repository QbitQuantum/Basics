CDPlayer::CDPlayer(BRect frame, const char *name, uint32 resizeMask,
		uint32 flags)
	: BView(frame, name, resizeMask, flags | B_FRAME_EVENTS),
 	fCDQuery("freedb.freedb.org")
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	fVolume = 255;

	BuildGUI();

	if (fCDDrive.CountDrives() < 1) {
		BAlert *alert = new BAlert("CDPlayer", B_TRANSLATE(
			"It appears that there are no CD"
			" drives on your computer or there is no system software to "
			"support one. Sorry."), B_TRANSLATE("OK"));
		alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
		alert->Go();
	}

	fWindowState = fCDDrive.GetState();
	fVolumeSlider->SetValue(fCDDrive.GetVolume());
	if (fVolumeSlider->Value() <= 2) {
		fCDDrive.SetVolume(255);
		fVolumeSlider->SetValue(255);
	}
	_WatchCDState();
}