void
PulseApp::ShowAbout(bool asApplication)
{
	// static version to be used in replicant mode
	BString name;
	if (asApplication)
		name = B_TRANSLATE_SYSTEM_NAME("Pulse");
	else
		name = B_TRANSLATE("Pulse");

	BString message = B_TRANSLATE(
		"%s\n\nBy David Ramsey and Arve Hjønnevåg\n"
		"Revised by Daniel Switkin\n");
	message.ReplaceFirst("%s", name);
	BAlert *alert = new BAlert(B_TRANSLATE("Info"),
		message.String(), B_TRANSLATE("OK"));

	BTextView* view = alert->TextView();
	BFont font;
				
	view->SetStylable(true);			
	view->GetFont(&font);
	
	font.SetSize(18);
	font.SetFace(B_BOLD_FACE);
	view->SetFontAndColor(0, name.Length(), &font);
	alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
	// Use the asynchronous version so we don't block the window's thread
	alert->Go(NULL);
}