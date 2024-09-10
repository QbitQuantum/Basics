void
MainWin::SelectInterface(int i)
{
	printf("MainWin::SelectInterface %d\n", i);
	printf("  CurrentInterface %d\n", fController->CurrentInterface());
	printf("  CurrentChannel %d\n", fController->CurrentChannel());

	// i = -1 means "None"

	if (i < 0) {
		fController->DisconnectInterface();
		goto done;
	}

	if (!fController->IsInterfaceAvailable(i)) {
		BString s;
		s << B_TRANSLATE("Error, interface is busy:\n\n");
		s << gDeviceRoster->DeviceName(i);
		BAlert* alert = new BAlert("error", s.String(), B_TRANSLATE("OK"));
		alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
		alert->Go();
		return;
	}

	fController->DisconnectInterface();
	if (fController->ConnectInterface(i) != B_OK) {
		BString s;
		s << B_TRANSLATE("Error, connecting to interface failed:\n\n");
		s << gDeviceRoster->DeviceName(i);
		BAlert* alert = new BAlert("error", s.String(), B_TRANSLATE("OK"));
		alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
		alert->Go();
	}

done:
	printf("MainWin::SelectInterface done:\n");
	printf("  CurrentInterface %d\n", fController->CurrentInterface());
	printf("  CurrentChannel %d\n", fController->CurrentChannel());

	SetInterfaceMenuMarker();
	SetupChannelMenu();
	SetChannelMenuMarker();
}