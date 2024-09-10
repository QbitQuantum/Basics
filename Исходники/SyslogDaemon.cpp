void
SyslogDaemon::AboutRequested()
{
	BPath path;
	find_directory(B_SYSTEM_LOG_DIRECTORY, &path);
	path.Append("syslog");

	BString name(B_TRANSLATE("Syslog Daemon"));
	BString message;
	snprintf(message.LockBuffer(512), 512,
		B_TRANSLATE("%s\n\nThis daemon is responsible for collecting "
			"all system messages and write them to the system-wide log "
			"at \"%s\".\n\n"), name.String(), path.Path());
	message.UnlockBuffer();

	BAlert *alert = new BAlert(name.String(), message.String(), B_TRANSLATE("OK"));
	BTextView *view = alert->TextView();
	BFont font;

	view->SetStylable(true);

	view->GetFont(&font);
	font.SetSize(21);
	font.SetFace(B_BOLD_FACE); 			
	view->SetFontAndColor(0, name.Length(), &font);

	alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
	alert->Go(NULL);
}