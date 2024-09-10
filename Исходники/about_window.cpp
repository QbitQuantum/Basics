void ShowAboutWindow(void)
{
	char str[512];
	sprintf(str,
		"Basilisk II\nVersion %d.%d\n\n"
		"Copyright " B_UTF8_COPYRIGHT " 1997-2008 Christian Bauer et al.\n"
		"E-mail: [email protected]\n"
		"http://www.uni-mainz.de/~bauec002/B2Main.html\n\n"
		"Basilisk II comes with ABSOLUTELY NO\n"
		"WARRANTY. This is free software, and\n"
		"you are welcome to redistribute it\n"
		"under the terms of the GNU General\n"
		"Public License.\n",
		VERSION_MAJOR, VERSION_MINOR
	);
	BAlert *about = new BAlert("", str, GetString(STR_OK_BUTTON), NULL, NULL, B_WIDTH_FROM_LABEL);
	BTextView *theText = about->TextView();
	if (theText) {
		theText->SetStylable(true);
		theText->Select(0, 11);
		BFont ourFont;
		theText->SetFontAndColor(be_bold_font);
		theText->GetFontAndColor(2, &ourFont, NULL);
		ourFont.SetSize(24);
		theText->SetFontAndColor(&ourFont);
	}
	about->Go();
}