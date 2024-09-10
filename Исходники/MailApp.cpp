status_t
TMailApp::SaveSettings()
{
	BMailSettings accountSettings;

	if (fDefaultAccount != ~0L) {
		accountSettings.SetDefaultOutboundAccount(fDefaultAccount);
		accountSettings.Save();
	}

	BPath path;
	status_t status = GetSettingsPath(path);
	if (status != B_OK)
		return status;

	path.Append("BeMail Settings~");

	BFile file;
	status = file.SetTo(path.Path(), B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);
	if (status != B_OK)
		return status;

	BMessage settings('BeMl');
	settings.AddRect("MailWindowSize", fMailWindowFrame);
//	settings.AddInt32("ExperienceLevel", level);

	font_family fontFamily;
	font_style fontStyle;
	fContentFont.GetFamilyAndStyle(&fontFamily, &fontStyle);

	settings.AddString("FontFamily", fontFamily);
	settings.AddString("FontStyle", fontStyle);
	settings.AddFloat("FontSize", fContentFont.Size());

	settings.AddRect("SignatureWindowSize", fSignatureWindowFrame);
	settings.AddBool("WordWrapMode", fWrapMode);
	settings.AddPoint("PreferencesWindowLocation", fPrefsWindowPos);
	settings.AddBool("AutoMarkRead", fAutoMarkRead);
	settings.AddString("SignatureText", fSignature);
	settings.AddInt32("CharacterSet", fMailCharacterSet);
	settings.AddString("FindString", FindWindow::GetFindString());
	settings.AddInt8("ShowButtonBar", fShowToolBar);
	settings.AddInt32("UseAccountFrom", fUseAccountFrom);
	settings.AddBool("ColoredQuotes", fColoredQuotes);
	settings.AddString("ReplyPreamble", fReplyPreamble);
	settings.AddBool("AttachAttributes", fAttachAttributes);
	settings.AddBool("WarnAboutUnencodableCharacters", fWarnAboutUnencodableCharacters);
	settings.AddBool("StartWithSpellCheck", fStartWithSpellCheckOn);

	BEntry entry;
	status = entry.SetTo(path.Path());
	if (status != B_OK)
		return status;

	status = settings.Flatten(&file);
	if (status == B_OK) {
		// replace original settings file
		status = entry.Rename("BeMail Settings", true);
	} else
		entry.Remove();

	return status;
}