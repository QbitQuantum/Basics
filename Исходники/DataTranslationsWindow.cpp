void
DataTranslationsWindow::_ShowInfoAlert(int32 id)
{
	const char* name = NULL;
	const char* info = NULL;
	BPath path;
	int32 version = 0;
	_GetTranslatorInfo(id, name, info, version, path);

	const char* labels[] = { B_TRANSLATE("Name:"), B_TRANSLATE("Version:"),
		B_TRANSLATE("Info:"), B_TRANSLATE("Path:"), NULL };
	int offsets[4];

	BString message;
	BString temp;

	offsets[0] = 0;
	temp.SetToFormat("%s %s\n", labels[0], name);

	message.Append(temp);

	offsets[1] = message.Length();
	// Convert the version number into a readable format
	temp.SetToFormat("%s %" B_PRId32 ".%" B_PRId32 ".%" B_PRId32 "\n\n", labels[1],
		B_TRANSLATION_MAJOR_VERSION(version),
		B_TRANSLATION_MINOR_VERSION(version),
		B_TRANSLATION_REVISION_VERSION(version));

	message.Append(temp);

	offsets[2] = message.Length();
	temp.SetToFormat("%s\n%s\n\n", labels[2], info);

	message.Append(temp);

	offsets[3] = message.Length();
	temp.SetToFormat("%s %s\n", labels[3], path.Path());

	message.Append(temp);

	BAlert* alert = new BAlert(B_TRANSLATE("Info"), message.String(),
		B_TRANSLATE("OK"));
	BTextView* view = alert->TextView();
	BFont font;

	view->SetStylable(true);

	view->GetFont(&font);
	font.SetFace(B_BOLD_FACE);

	for (int32 i = 0; labels[i]; i++) {
		view->SetFontAndColor(offsets[i], offsets[i] + strlen(labels[i]), &font);
	}

	alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
	alert->Go();
}