void
LoginApp::MessageReceived(BMessage *message)
{
	bool reboot = false;

	switch (message->what) {
		case kAttemptLogin:
			message->PrintToStream();
			TryLogin(message);
			// TODO
			break;
#ifdef __HAIKU__
		case kHaltAction:
			reboot = false;
			// FALLTHROUGH
		case kRebootAction:
		{
			BRoster roster;
			BRoster::Private rosterPrivate(roster);
			status_t error = rosterPrivate.ShutDown(reboot, false, false);
			if (error < B_OK) {
				BString msg(B_TRANSLATE("Error: %1"));
				msg.ReplaceFirst("%1", strerror(error));
				BAlert* alert = new BAlert(("Error"), msg.String(),
					B_TRANSLATE("OK"));
				alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
				alert->Go();
			}
			break;
		}
		case kSuspendAction:
		{
			BAlert* alert = new BAlert(B_TRANSLATE("Error"),
				B_TRANSLATE("Unimplemented"), B_TRANSLATE("OK"));
			alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
			alert->Go();
			break;
		}
#endif
	default:
		BApplication::MessageReceived(message);
	}
}