void
HWindow::AboutRequested()
{
	const char* aboutText = AboutText();
	if (aboutText == NULL)
		return;

	BAlert *about = new BAlert("About", aboutText, "Cool");
	BTextView *v = about->TextView();
	if (v) {
		rgb_color red = {255, 0, 51, 255};
		rgb_color blue = {0, 102, 255, 255};

		v->SetStylable(true);
		char *text = (char*)v->Text();
		char *s = text;
		// set all Be in blue and red
		while ((s = strstr(s, "Be")) != NULL) {
			int32 i = s - text;
			v->SetFontAndColor(i, i+1, NULL, 0, &blue);
			v->SetFontAndColor(i+1, i+2, NULL, 0, &red);
			s += 2;
		}
		// first text line 
		s = strchr(text, '\n');
		BFont font;
		v->GetFontAndColor(0, &font);
		font.SetSize(12); // font.SetFace(B_OUTLINED_FACE);
		v->SetFontAndColor(0, s-text+1, &font, B_FONT_SIZE);
	};
	about->SetFlags(about->Flags() | B_CLOSE_ON_ESCAPE);
	about->Go();
}