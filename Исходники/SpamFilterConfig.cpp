void
AGMSBayesianSpamFilterConfig::ShowSpamServerConfigurationWindow () {
	status_t    errorCode = B_OK;
	BMessage    maximizeCommand;
	BMessenger	messengerToServer;
	BMessage    replyMessage;

	// Make sure the server is running.
	if (!be_roster->IsRunning (kServerSignature)) {
			errorCode = be_roster->Launch (kServerSignature);
			if (errorCode != B_OK) {
				BPath path;
				entry_ref ref;
				directory_which places[] = {
					B_SYSTEM_NONPACKAGED_BIN_DIRECTORY,
					B_SYSTEM_BIN_DIRECTORY
				};
				for (int32 i = 0; i < 2; i++) {
					find_directory(places[i],&path);
					path.Append("spamdbm");
					if (!BEntry(path.Path()).Exists())
						continue;
					get_ref_for_path(path.Path(),&ref);
					if ((errorCode =  be_roster->Launch (&ref)) == B_OK)
						break;
				}
				if (errorCode != B_OK)
					goto ErrorExit;
			}
		}
	
	// Set up the messenger to the database server.
	messengerToServer =
		BMessenger (kServerSignature);
	if (!messengerToServer.IsValid ())
		goto ErrorExit;

	// Wait for the server to finish starting up, and for it to create the window.
	snooze (2000000);

	// Tell it to show its main window, in case it is hidden in server mode.
	maximizeCommand.what = B_SET_PROPERTY;
	maximizeCommand.AddBool ("data", false);
	maximizeCommand.AddSpecifier ("Minimize");
	maximizeCommand.AddSpecifier ("Window", (int32)0);
	errorCode = messengerToServer.SendMessage (&maximizeCommand, &replyMessage);
	if (errorCode != B_OK)
		goto ErrorExit;
	return; // Successful.

ErrorExit:
	BAlert* alert = new BAlert ("SpamFilterConfig Error", B_TRANSLATE("Sorry, "
		"unable to launch the spamdbm program to let you edit the server "
		"settings."), B_TRANSLATE("Close"));
	alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
	alert->Go ();
	return;
}