void TextinputTestScreen::CreateHeader()
{
	UIStaticText * header = new UIStaticText(Rect(5.f, 5.f, 300.f, 50.f));
	AddControl(header);
	header->Release();
	header->SetFont(font);
	header->SetTextColor(Color::White());
	header->SetText(headerText);
}